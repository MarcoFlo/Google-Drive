#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "AsyncClientGetSymbols.h"
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
}

void CharacterClient::Register(protobuf::User &user) {
    grpc::ClientContext context;
    context.AddMetadata("username", user.username());
    context.AddMetadata("password", user.password());
    context.AddMetadata("passwordr", user.passwordr());
    protobuf::Empty reply;
    grpc::CompletionQueue cq;
    grpc::Status status;

    status = stub_->Register(&context, user, &reply);

    if (status.ok())
        std::cout << "Register rpc was successful" << std::endl;
    else
        std::cout << "Register rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
}

std::string CharacterClient::Login(protobuf::User &user) {
    grpc::ClientContext context;
    context.AddMetadata("username", user.username());
    context.AddMetadata("password", user.password());

    protobuf::Identifier reply;
    grpc::CompletionQueue cq;
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
    grpc::CompletionQueue cq;
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

std::string CharacterClient::ShareFile(std::string &fileIdentifier, std::string &usernameShare) {
    grpc::ClientContext context;
    context.AddMetadata("token", token_);
    context.AddMetadata("usernameshare", usernameShare);

    protobuf::FileInfo request;
    request.set_identifier(fileIdentifier);

    protobuf::Empty reply;
    grpc::CompletionQueue cq;
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

std::string CharacterClient::GetFileContent(protobuf::FileInfo fileInfo) {
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
        return "";

    } else {
        std::cout << "Get file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return status.error_message();
    }
}


AsyncClientGetSymbols *CharacterClient::GetSymbols(const std::string &fileUniqueId) {
    protobuf::FileInfo request;
    request.set_filename(fileUniqueId);
    return new AsyncClientGetSymbols(request, token_, cq_, stub_);
}


void CharacterClient::AsyncCompleteRpc() {
    void *got_tag;
    bool ok = false;

    // Block until the next result is available in the completion queue "cq".
    while (cq_.Next(&got_tag, &ok)) {
        AsyncClientCall *call = static_cast<AsyncClientCall *>(got_tag);
        call->HandleAsync(ok);
    }


}

std::string CharacterClient::getToken() {
    return token_;
}








