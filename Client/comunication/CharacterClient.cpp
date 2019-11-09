#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
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

void CharacterClient::Login(protobuf::UserL userL) {
    grpc::ClientContext context;
    context.AddMetadata("username", userL.username());
    context.AddMetadata("password", userL.password());

    protobuf::Identifier reply;
    grpc::CompletionQueue cq;
    grpc::Status status;

    status = stub_->Login(&context, userL, &reply);

    if (status.ok())
        std::cout << "Login rpc was successful, we got identifier: " << reply.id() << std::endl;
    else
        std::cout << "Login rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;
}

void CharacterClient::GetSymbols() {
    protobuf::FileName request;
    request.set_filename("file1");

    grpc::ClientContext context;
    context.AddMetadata("token", "abcd");
    std::unique_ptr<grpc::ClientReader<protobuf::Message>> reader(stub_->GetSymbols(&context, request));

    protobuf::Message reply;
    while (reader->Read(&reply)) {
        std::cout << "Get Symbols received: " << reply.symbol().uniqueid() << std::endl;
    }

    grpc::Status status = reader->Finish();
    if (status.ok()) {
        std::cout << "GetSymbols rpc ended." << std::endl;
    } else {
        std::cout << "GetSymbols rpc failed." << std::endl;
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }

}






