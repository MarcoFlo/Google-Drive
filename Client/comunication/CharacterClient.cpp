//
// Created by flori on 23/10/2019.
//

#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "CharacterClient.h"


CharacterClient::CharacterClient(std::shared_ptr<grpc::Channel> channel) : stub_(
        protobuf::CharacterService::NewStub(channel)) {}

int CharacterClient::Connect(protobuf::User user) {

    protobuf::Identifier reply;
    grpc::ClientContext context;
    grpc::CompletionQueue cq;
    grpc::Status status;

    std::unique_ptr<grpc::ClientAsyncResponseReader<protobuf::Identifier>> rpc(
            stub_->PrepareAsyncConnect(&context, user, &cq));

    rpc->StartCall();
    rpc->Finish(&reply, &status, this);
    void* got_tag;
    bool ok = false;
    // Block until the next result is available in the completion queue "cq".
    // The return value of Next should always be checked. This return value
    // tells us whether there is any kind of event or the cq_ is shutting down.
    GPR_ASSERT(cq.Next(&got_tag, &ok));

    // Verify that the result from "cq" corresponds, by its tag, our previous
    // request.
    GPR_ASSERT(got_tag == this);

    GPR_ASSERT(ok);


    if (status.ok()) {
        return reply.editorid();
    } else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
        return -1;
    }
}

void CharacterClient::GetSymbols() {
    protobuf::User request;
    request.set_username("prova@test.it");

    grpc::ClientContext context;
    std::unique_ptr<grpc::ClientReader<protobuf::Message>> reader(stub_->GetSymbols(&context, request));

    protobuf::Message reply;
    while (reader->Read(&reply)) {
        std::cout << "Got reply: " << reply.symbol().uniqueid() << std::endl;
    }

    grpc::Status status = reader->Finish();
    if (status.ok()) {
        std::cout << "GetSymbols rpc succeeded." << std::endl;
    } else {
        std::cout << "GetSymbols rpc failed." << std::endl;
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }

}




