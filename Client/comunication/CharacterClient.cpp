#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <thread>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "AsyncClientGetSymbols.h"
#include "Symbol.h"
#include "Message.h"
#include "CharacterClient.h"


void read(const std::string &filename, std::string &data) {
    std::ifstream file(filename.c_str(), std::ios::in);

    if (file.is_open()) {
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        data = ss.str();
    }
}

CharacterClient::CharacterClient() {
    std::string serverCert;
    read("../../certs/server.cert", serverCert);
    grpc::SslCredentialsOptions opts;
    opts.pem_root_certs = serverCert;
    auto channel_creds = grpc::SslCredentials(opts);

    stub_ = protobuf::CharacterService::NewStub(grpc::CreateChannel("localhost:50051", channel_creds));

    //per gestire i simboli che ci arrivano dal server
    thread_ = std::thread([this] { this->AsyncCompleteRpc(this); });

}

CharacterClient::~CharacterClient() {
    if (thread_.joinable())
        thread_.join();
}

void CharacterClient::AsyncCompleteRpc(CharacterClient *pClient) {
    void *got_tag;
    bool ok = false;

    // Block until the next result is available in the completion queue "cq".
    while (pClient->cq_.Next(&got_tag, &ok)) {
        auto *call = static_cast<AsyncClientCall *>(got_tag);
        call->HandleAsync(ok);

    }
}


std::string CharacterClient::Register(protobuf::ProfileInfo &profileInfo) {
    grpc::ClientContext context;
    context.AddMetadata("email", profileInfo.user().email());
    context.AddMetadata("password", profileInfo.user().password());
    context.AddMetadata("passwordr", profileInfo.user().passwordr());
    context.AddMetadata("username", profileInfo.username());
    context.AddMetadata("name", profileInfo.name());
    context.AddMetadata("surname", profileInfo.surname());


    protobuf::Empty reply;
    grpc::Status status;
    status = stub_->Register(&context, profileInfo, &reply);

    if (status.ok()) {
        std::cout << "Register rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Register rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }

}

std::string CharacterClient::Login(const protobuf::User &user) {
    grpc::ClientContext context;
    context.AddMetadata("email", user.email());
    context.AddMetadata("password", user.password());
    email_ = user.email();

    protobuf::UserLogged reply;
    grpc::Status status;

    status = stub_->Login(&context, user, &reply);

    if (status.ok()) {
        std::cout << "Login rpc was successful" << std::endl;
        userLogged_ = reply;
        return "";
    } else {
        std::cout << "Login rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}


std::string CharacterClient::Logout() {
    grpc::ClientContext context;
    context.AddMetadata("token", userLogged_.token());

    protobuf::Empty request;

    protobuf::Empty reply;
    grpc::Status status;

    status = stub_->Logout(&context, request, &reply);

    if (status.ok()) {
        std::cout << "Logout rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Logout rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}

std::string CharacterClient::InsertFile(const protobuf::FileName &request) {
    grpc::ClientContext context;
    context.AddMetadata("token", userLogged_.token());


    protobuf::FileInfo reply;
    grpc::Status status;

    status = stub_->InsertFile(&context, request, &reply);

    if (status.ok()) {
        std::cout << "Insert file rpc was successful -> " << reply.filename() << std::endl;
        currentFileIdentifier_ = reply.fileidentifier();
        // todo capire se rimuovere
//        GetSymbols(reply);
        return reply.fileidentifier();
    } else {
        std::cout << "Insert file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}

std::string CharacterClient::RemoveFile(const protobuf::FileInfo &fileInfo) {
    grpc::ClientContext context;
    context.AddMetadata("token", userLogged_.token());

    protobuf::Empty reply;
    grpc::Status status;

    status = stub_->RemoveFile(&context, fileInfo, &reply);

    if (status.ok()) {
        std::cout << "Remove file rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Remove file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}

//Il risultato viene depositato in lastFileInfoList per poter restituire il messaggio d'errore
std::string CharacterClient::GetFiles() {
    grpc::ClientContext context;
    context.AddMetadata("token", userLogged_.token());

    protobuf::Empty request;
    grpc::Status status;

    status = stub_->GetFiles(&context, request, &lastFileInfoList_);

    if (status.ok()) {
        std::cout << "Get files rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Get files rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}

std::string CharacterClient::ShareFile(const std::string &fileIdentifier, const std::string &emailShare) {
    grpc::ClientContext context;
    context.AddMetadata("token", userLogged_.token());
    context.AddMetadata("emailshare", emailShare);

    protobuf::FileInfo request;
    request.set_fileidentifier(fileIdentifier);

    protobuf::Empty reply;
    grpc::Status status;

    status = stub_->ShareFile(&context, request, &reply);


    if (status.ok()) {
        std::cout << "Share file rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Share file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}

std::string CharacterClient::ImportFile(const std::string &fileIdentifier) {
    grpc::ClientContext context;
    context.AddMetadata("token", userLogged_.token());

    protobuf::FileInfo request;
    request.set_fileidentifier(fileIdentifier);

    protobuf::Empty reply;
    grpc::Status status;

    status = stub_->ImportFile(&context, request, &reply);


    if (status.ok()) {
        std::cout << "Import file rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Import file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}

std::string CharacterClient::GetFileContent(const protobuf::FileInfo &fileInfo) {
    grpc::ClientContext context;
    context.AddMetadata("token", userLogged_.token());

    protobuf::Chunk reply;
    grpc::Status status;

    std::shared_ptr<grpc::ClientReader<protobuf::Chunk>> stream(stub_->GetFileContent(&context, fileInfo));

    protobuf::SymbolVector symbolVectorPartial;
    while (stream->Read(&reply)) {
        std::cout << "Get file content" << std::endl;

        std::istringstream istream(*reply.mutable_chunk());
        symbolVectorPartial.ParseFromIstream(&istream);
        symbolVector_.mutable_symbolvector()->MergeFrom(symbolVectorPartial.symbolvector());
    }
    status = stream->Finish();
    //todo chiamare getSymbols

    if (status.ok()) {
        std::cout << "Get file content rpc was successful" << std::endl;
        currentFileIdentifier_ = fileInfo.fileidentifier();
        GetSymbols(fileInfo);
        return "";

    } else {
        std::cout << "Get file content rpc failed: " << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return status.error_message();
    }
}


void CharacterClient::GetSymbols(const protobuf::FileInfo &fileInfo) {
    new AsyncClientGetSymbols(fileInfo, userLogged_.token(), cq_, stub_);
}


std::string CharacterClient::InsertSymbols(Symbol &symbol, bool isErase) {
    // si sta provando a inserire prima che il file sia aperto correttamente
    if (currentFileIdentifier_.empty())
        return "";

    grpc::ClientContext context;
    context.AddMetadata("token", userLogged_.token());

    protobuf::Empty reply;
    grpc::Status status;

    Message message(currentFileIdentifier_, symbol, isErase);

    status = stub_->InsertSymbols(&context, message.makeProtobufMessage(), &reply);


    if (status.ok()) {
        std::cout << "Insert symbols rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Insert symbols rpc failed: " << status.error_code() << ": " << status.error_message()
                  << std::endl;
        return status.error_message();
    }
}

protobuf::FilesInfoList CharacterClient::getFileInfoList() {
    return lastFileInfoList_;
}

protobuf::SymbolVector CharacterClient::getSymbolVector() {
    return symbolVector_;
}

std::list<int> CharacterClient::searchFileInfo(const std::string& name) {
    int i = 0;
    std::list<int> *searchList = new std::list<int>;

    for (i = 0; i < lastFileInfoList_.fileil_size(); i++) {
        if (lastFileInfoList_.fileil(i).filename().find(name) != std::string::npos) {
            searchList->push_back(i);
        }
    }
    return *searchList;
}

protobuf::FileInfo CharacterClient::getFileInfo(const std::string& id) {
    int i = 0;

    for (i = 0; i < lastFileInfoList_.fileil_size(); i++) {
        if (lastFileInfoList_.fileil(i).fileidentifier() == id) {
            return lastFileInfoList_.fileil(i);
        }
    }
    return protobuf::FileInfo();
}

void CharacterClient::closeFile(){
    symbolVector_.Clear();
}

protobuf::ProfileInfo CharacterClient::getProfileInfoLogged() {
    return userLogged_.profileinfo();
}

