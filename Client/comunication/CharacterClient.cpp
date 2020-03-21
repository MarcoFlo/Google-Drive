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
        AsyncClientCall *call = static_cast<AsyncClientCall *>(got_tag);
        call->HandleAsync(ok);

    }
}


std::string CharacterClient::Register(protobuf::User &user) {
    grpc::ClientContext context;
    context.AddMetadata("username", user.username());
    context.AddMetadata("password", user.password());
    context.AddMetadata("passwordr", user.passwordr());
    protobuf::Empty reply;
    grpc::Status status;

    status = stub_->Register(&context, user, &reply);

    if (status.ok()) {
        std::cout << "Register rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Register rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }

}

std::string CharacterClient::Login(protobuf::User &user) {
    grpc::ClientContext context;
    context.AddMetadata("username", user.username());
    context.AddMetadata("password", user.password());

    protobuf::Identifier reply;
    grpc::Status status;

    status = stub_->Login(&context, user, &reply);

    if (status.ok()) {
        std::cout << "Login rpc was successful" << std::endl;
        token_ = reply.token();
        return "";
    } else {
        std::cout << "Login rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}


std::string CharacterClient::Logout() {
    grpc::ClientContext context;
    context.AddMetadata("token", token_);

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
    context.AddMetadata("token", token_);


    protobuf::FileInfo reply;
    grpc::Status status;

    status = stub_->InsertFile(&context, request, &reply);

    if (status.ok()) {
        std::cout << "Insert file rpc was successful -> " << reply.filename() << std::endl;
        fileidentifier_ = reply.fileidentifier();
        GetSymbols(reply);
        return reply.fileidentifier();
    } else {
        std::cout << "Insert file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}

std::string CharacterClient::RemoveFile(const protobuf::FileInfo &fileInfo) {
    grpc::ClientContext context;
    context.AddMetadata("token", token_);

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


std::string CharacterClient::ShareFile(std::string &fileIdentifier, std::string &usernameShare) {
    grpc::ClientContext context;
    context.AddMetadata("token", token_);
    context.AddMetadata("usernameshare", usernameShare);

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

std::string CharacterClient::GetFileContent(const protobuf::FileInfo &fileInfo) {
    grpc::ClientContext context;
    context.AddMetadata("token", token_);

    protobuf::Chunk reply;
    grpc::Status status;

    std::shared_ptr<grpc::ClientReader<protobuf::Chunk>> stream(stub_->GetFileContent(&context, fileInfo));

    protobuf::SymbolVector symbolVectorPartial;
    while (stream->Read(&reply)) {
        std::istringstream istream(*reply.mutable_chunk());
        symbolVectorPartial.ParseFromIstream(&istream);
        symbolVector_.mutable_symbolvector()->MergeFrom(symbolVectorPartial.symbolvector());
    }
    status = stream->Finish();
    //todo chiamare getSymbols

    if (status.ok()) {
        std::cout << "Get file rpc was successful" << std::endl;
        fileidentifier_ = fileInfo.fileidentifier();
        GetSymbols(fileInfo);
        return "";

    } else {
        std::cout << "Get file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}


AsyncClientGetSymbols *CharacterClient::GetSymbols(const protobuf::FileInfo &fileInfo) {
    return new AsyncClientGetSymbols(fileInfo, token_, cq_, stub_);
}


std::string CharacterClient::InsertSymbols(Symbol &symbol, bool isErase) {
    // si sta provando a inserire prima che il file sia aperto correttamente
    if(fileidentifier_.empty())
        return "";

    grpc::ClientContext context;
    context.AddMetadata("token", token_);

    protobuf::Empty reply;
    grpc::Status status;

    Message message(fileidentifier_,symbol, isErase);

    status = stub_->InsertSymbols(&context, message.makeProtobufMessage(), &reply);


    if (status.ok()) {
        std::cout << "Insert symbols rpc was successful" << std::endl;
        return "";
    } else {
        std::cout << "Insert symbols rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}

std::string CharacterClient::getToken() {
    return token_;
}







