#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "AsyncClientGetSymbols.h"
#include "CharacterClient.h"


CharacterClient::CharacterClient(std::shared_ptr<grpc::Channel> channel) : stub_(
        protobuf::CharacterService::NewStub(channel)) {}

void CharacterClient::Register(protobuf::User user) {
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

std::string CharacterClient::Login(protobuf::User user) {
    grpc::ClientContext context;
    context.AddMetadata("username", user.username());
    context.AddMetadata("password", user.password());

    protobuf::Identifier reply;
    grpc::CompletionQueue cq;
    grpc::Status status;

    status = stub_->Login(&context, user, &reply);

    if (status.ok()) {
        std::cout << "Login rpc was successful, we got identifier: " << reply.token() << std::endl;
        return reply.token();
    } else {
        std::cout << "Login rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
        return "";
    }
}


void CharacterClient::Logout(std::string token) {
    grpc::ClientContext context;
    context.AddMetadata("token", token);

    protobuf::Empty request;

    protobuf::Empty reply;
    grpc::CompletionQueue cq;
    grpc::Status status;

    status = stub_->Logout(&context, request, &reply);

    if (status.ok())
        std::cout << "Logout rpc was successful" << std::endl;
    else
        std::cout << "Logout rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
}


void CharacterClient::ShareFile(std::string token, std::string filename, std::string usernameShare) {
    grpc::ClientContext context;
    context.AddMetadata("token", token);
    context.AddMetadata("usernameshare", usernameShare);

    protobuf::FileName request;
    request.set_filename(filename);

    protobuf::Empty reply;
    grpc::CompletionQueue cq;
    grpc::Status status;

    status = stub_->ShareFile(&context, request, &reply);

    if (status.ok())
        std::cout << "Share file rpc was successful" << std::endl;
    else
        std::cout << "Share file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
}

void CharacterClient::GetFileContent(std::string token, protobuf::FileInfo fileInfo) {
    grpc::ClientContext context;
    context.AddMetadata("token", token);

    protobuf::Chunk reply;
    grpc::Status status;

    std::shared_ptr<grpc::ClientReader<protobuf::Chunk>> stream(stub_->GetFileContent(&context, fileInfo));

    while (stream->Read(&reply)) {
        std::cout << "Got message " << reply.chunk().data() << std::endl;
    }
    status = stream->Finish();

    if (status.ok())
        std::cout << "Get file rpc was successful" << std::endl;
    else
        std::cout << "Get file rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
}


AsyncClientGetSymbols *CharacterClient::GetSymbols(const std::string &fileUniqueId, const std::string &token) {
    protobuf::FileInfo request;
    request.set_filename(fileUniqueId);
    return new AsyncClientGetSymbols(request, token, cq_, stub_);
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








