#include <string>
#include <iostream>
#include <fstream>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "MyServiceAuthProcessor.h"

MyServiceAuthProcessor::MyServiceAuthProcessor() {
    idCounter = 0;
    LoadUserMap();
}

grpc::Status MyServiceAuthProcessor::Process(const grpc_impl::AuthMetadataProcessor::InputMetadata &auth_metadata,
                                             grpc::AuthContext *context,
                                             grpc_impl::AuthMetadataProcessor::OutputMetadata *consumed_auth_metadata,
                                             grpc_impl::AuthMetadataProcessor::OutputMetadata *response_metadata) {
// determine intercepted method
    std::string dispatch_keyname = ":path";
    auto dispatch_kv = auth_metadata.find(dispatch_keyname);
    auto dispatch_value = std::string(dispatch_kv->second.data(), (dispatch_kv->second).length());

    if (dispatch_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INTERNAL, "Internal Error");

    // if token metadata not necessary, return early, avoid token checking
    std::cout << "Processor got call for: " << dispatch_value << std::endl << std::endl;
    if (dispatch_value == "/protobuf.CharacterService/Register") {
        return ProcessRegister(auth_metadata);
    }
    if (dispatch_value == "/protobuf.CharacterService/Login") {
        return ProcessLogin(auth_metadata, context);
    }

    // determine availability of token metadata
    auto token_kv = auth_metadata.find(Const::TokenKeyName());
    if (token_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Missing Token");

    // determine validity of token metadata
    auto token_value = std::string(token_kv->second.data(), (token_kv->second).length());
//    std::cout << "Processor got token: " << token_value << std::endl << std::endl;
    if (tokenMap.count(token_value) == 0)
        return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid Token");

    // once verified, mark as consumed and store user for later retrieval
    consumed_auth_metadata->insert(std::make_pair(Const::TokenKeyName(), token_value));     // required
    context->AddProperty(Const::PeerIdentityPropertyName(), tokenMap[token_value]);           // optional
    context->SetPeerIdentityPropertyName(Const::PeerIdentityPropertyName());                // optional

    if (dispatch_value == "/protobuf.CharacterService/Logout") {
        return ProcessLogout(token_value);
    }

    if (dispatch_value == "/protobuf.CharacterService/ShareFile") {
        return ProcessShareFile(auth_metadata, context);
    }

    return grpc::Status::OK;
}

grpc::Status
MyServiceAuthProcessor::ProcessRegister(const grpc_impl::AuthMetadataProcessor::InputMetadata &auth_metadata) {

    auto email_kv = auth_metadata.find("email");
    if (email_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Username mancante");

    auto pw_kv = auth_metadata.find("password");
    if (pw_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Password mancante");

    auto pwR_kv = auth_metadata.find("passwordr");
    if (pwR_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Password ripetuta mancante");

    std::string email = std::string(email_kv->second.data(), (email_kv->second).length());
    std::string pw = std::string(pw_kv->second.data(), (pw_kv->second).length());
    std::string pwR = std::string(pwR_kv->second.data(), (pwR_kv->second).length());

    if (userMap.usermap().contains(email))
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Username già in uso");

    if (pw != pwR)
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Le due password non coincidono");
    google::protobuf::MapPair<std::basic_string<char>, std::basic_string<char>> mapPair(email, pw);
    UpdateUserMap(mapPair);
    return grpc::Status::OK;
}

grpc::Status
MyServiceAuthProcessor::ProcessLogin(const InputMetadata &auth_metadata,
                                     grpc::AuthContext *context) {
    auto email_kv = auth_metadata.find("email");
    if (email_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Username mancante");

    auto pw_kv = auth_metadata.find("password");
    if (pw_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Password mancante");

    std::string email = std::string(email_kv->second.data(), (email_kv->second).length());
    std::string pw = std::string(pw_kv->second.data(), (pw_kv->second).length());

    auto user_kv = userMap.usermap().find(email);
    if (user_kv == userMap.usermap().end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Utente non registrato");

    if (user_kv->second != pw)
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Password sbagliata");

    context->AddProperty("token", std::to_string(idCounter));
    tokenMap.insert(std::make_pair(std::to_string(idCounter), email));
    idCounter++;


    return grpc::Status::OK;
}

grpc::Status MyServiceAuthProcessor::ProcessLogout(std::string token) {
    tokenMap.erase(token);
    return grpc::Status::OK;
}

grpc::Status MyServiceAuthProcessor::ProcessShareFile(const InputMetadata &auth_metadata,
                                                      grpc::AuthContext *context) {
    auto emailShare_kv = auth_metadata.find("emailshare");
    if (emailShare_kv != auth_metadata.end()) {
        auto emailShare_value = std::string(emailShare_kv->second.data(), (emailShare_kv->second).length());
        if (userMap.usermap().contains(emailShare_value)) {
            context->AddProperty("emailshare", emailShare_value);
            return grpc::Status::OK;
        } else {
            return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                                "Utente con cui si vuole condividere il file non registrato");
        }
    }
    else {
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT,
                            "Specificare il metadata emailshare");
    }
}

void MyServiceAuthProcessor::LoadUserMap() {
    std::ifstream ifs("userMap.data", std::ios_base::in | std::ios_base::binary);
    if (ifs.peek() != EOF) {
        if (!userMap.ParseFromIstream(&ifs)) {
            std::cerr << "La lettura di userMap.data è fallita" << std::endl;
            exit(1);
        }
        std::cout << "Sono stati caricati i seguenti utenti: " << std::endl;
        std::for_each(userMap.usermap().begin(), userMap.usermap().end(), [](auto &pair) {
            std::cout << pair.first << std::endl;
        });
        std::cout << std::endl;
    }
}

void MyServiceAuthProcessor::UpdateUserMap(
        google::protobuf::MapPair<std::basic_string<char>, std::basic_string<char>> &pair) {
    userMap.mutable_usermap()->insert(pair);

    std::cout << "Verranno salvati i seguenti utenti: " << std::endl;
    std::for_each(userMap.usermap().begin(), userMap.usermap().end(), [](auto &pair) {
        std::cout << pair.first << std::endl;
    });
    std::cout << std::endl;

    std::ofstream ofs("userMap.data", std::ios_base::out | std::ios_base::binary);
    if (!userMap.SerializeToOstream(&ofs)) {
        std::cerr << "La scrittura di userMap.data è fallita";
        exit(1);
    }
}



