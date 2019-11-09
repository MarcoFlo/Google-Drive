#include <string>
#include <iostream>
#include <fstream>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "MyServiceAuthProcessor.h"

MyServiceAuthProcessor::MyServiceAuthProcessor() {
    LoadUserMap();
}

grpc::Status MyServiceAuthProcessor::Process(const grpc_impl::AuthMetadataProcessor::InputMetadata &auth_metadata,
                                             grpc::AuthContext *context,
                                             grpc_impl::AuthMetadataProcessor::OutputMetadata *consumed_auth_metadata,
                                             grpc_impl::AuthMetadataProcessor::OutputMetadata *response_metadata) {
// determine intercepted method
    std::string dispatch_keyname = ":path";
    auto dispatch_kv = auth_metadata.find(dispatch_keyname);
    if (dispatch_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INTERNAL, "Internal Error");

    // if token metadata not necessary, return early, avoid token checking
    auto dispatch_value = std::string(dispatch_kv->second.data(), (dispatch_kv->second).length());
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
    std::cout << "Processor got token: " << token_value << std::endl << std::endl;
    if (tokens.count(token_value) == 0)
        return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid Token");

    // once verified, mark as consumed and store user for later retrieval
    consumed_auth_metadata->insert(std::make_pair(Const::TokenKeyName(), token_value));     // required
    context->AddProperty(Const::PeerIdentityPropertyName(), tokens[token_value]);           // optional
    context->SetPeerIdentityPropertyName(Const::PeerIdentityPropertyName());                // optional

    return grpc::Status::OK;
}

grpc::Status
MyServiceAuthProcessor::ProcessRegister(const grpc_impl::AuthMetadataProcessor::InputMetadata &auth_metadata) {

    auto username_kv = auth_metadata.find("username");
    if (username_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Username mancante");

    auto pw_kv = auth_metadata.find("password");
    if (pw_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Password mancante");

    auto pwR_kv = auth_metadata.find("passwordr");
    if (pwR_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Password ripetuta mancante");

    std::string username = std::string(username_kv->second.data(), (username_kv->second).length());
    std::string pw = std::string(pw_kv->second.data(), (pw_kv->second).length());
    std::string pwR = std::string(pwR_kv->second.data(), (pwR_kv->second).length());

    if (pw != pwR)
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Le due password non coincidono");

    UpdateUserMap(std::make_pair(username, pw));
    return grpc::Status::OK;
}

grpc::Status
MyServiceAuthProcessor::ProcessLogin(const grpc_impl::AuthMetadataProcessor::InputMetadata &auth_metadata,
                                     grpc::AuthContext *context) {
    auto username_kv = auth_metadata.find("username");
    if (username_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Username mancante");

    auto pw_kv = auth_metadata.find("password");
    if (pw_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Password mancante");

    std::string username = std::string(username_kv->second.data(), (username_kv->second).length());
    std::string pw = std::string(pw_kv->second.data(), (pw_kv->second).length());

    auto user_kv = userMap.find(username);
    if (user_kv == userMap.end())
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Utente non registrato");

    if (user_kv->second != pw)
        return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "Password sbagliata");


    context->AddProperty("identifier", "55");
    return grpc::Status::OK;
}

void MyServiceAuthProcessor::LoadUserMap() {
    protobuf::UserMap userMapProto;

    std::ifstream ifs("userMap.data", std::ios_base::in | std::ios_base::binary);
    if (ifs.peek() != EOF) {
        if (!userMapProto.ParseFromIstream(&ifs)) {
            std::cerr << "La lettura di userMap.data è fallita" << std::endl;
            exit(1);
        }
        userMap = {userMapProto.usermap().begin(), userMapProto.usermap().end()};
        std::cout << "Sono stati caricati i seguenti utenti: " << std::endl;
        std::for_each(userMap.begin(), userMap.end(), [](auto &pair) {
            std::cout << pair.first << std::endl;
        });
        std::cout << std::endl;
    }
}

void MyServiceAuthProcessor::UpdateUserMap(std::pair<std::string, std::string> pair) {
    userMap.insert(pair);
    protobuf::UserMap userMapProto;

    userMapProto.mutable_usermap()->insert(userMap.begin(), userMap.end());

    std::cout << "Verranno salvati i seguenti utenti: " << std::endl;
    std::for_each(userMapProto.usermap().begin(), userMapProto.usermap().end(), [](auto &pair) {
        std::cout << pair.first << std::endl;
    });
    std::cout << std::endl;

    std::ofstream ofs("userMap.data", std::ios_base::out | std::ios_base::binary);
    if (!userMapProto.SerializeToOstream(&ofs)) {
        std::cerr << "La scrittura di userMap.data è fallita";
        exit(1);
    }
}
