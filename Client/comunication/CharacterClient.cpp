#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "AsyncClientGetSymbols.h"
#include "CharacterClient.h"


CharacterClient::CharacterClient(std::shared_ptr<grpc::Channel> channel) : stub_(
        protobuf::CharacterService::NewStub(channel)) {}

void CharacterClient::Register(protobuf::UserR userR) {
    grpc::ClientContext context;
    context.AddMetadata("username", userR.username());
    context.AddMetadata("password", userR.password());
    context.AddMetadata("passwordr", userR.passwordr());
    protobuf::Empty reply;
    grpc::CompletionQueue cq;
    grpc::Status status;

    status = stub_->Register(&context, userR, &reply);

    if (status.ok())
        std::cout << "Register rpc was successful" << std::endl;
    else
        std::cout << "Register rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
}

std::string CharacterClient::Login(protobuf::UserL userL) {
    grpc::ClientContext context;
    context.AddMetadata("username", userL.username());
    context.AddMetadata("password", userL.password());

    protobuf::Identifier reply;
    grpc::CompletionQueue cq;
    grpc::Status status;

    status = stub_->Login(&context, userL, &reply);

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


AsyncClientGetSymbols * CharacterClient::GetSymbols(const std::string& fileUniqueId,const std::string& token) {
    protobuf::FileUniqueId request;
    request.set_fileuniqueid(fileUniqueId);
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






