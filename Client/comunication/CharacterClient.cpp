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

void CharacterClient::Connect(protobuf::User user) {

    grpc::ClientContext context;
    protobuf::Identifier reply;
    grpc::CompletionQueue cq;
    grpc::Status status;
    void *got_tag;
    bool ok = false;

    //sync
    status = stub_->Connect(&context, user, &reply);


    //async1 bloccante
//    std::unique_ptr<grpc::ClientAsyncResponseReader<protobuf::Identifier> > rpc(
//            stub_->AsyncConnect(&context, user, &cq));
//    rpc->Finish(&reply, &status, this);
//
//    GPR_ASSERT(cq.Next(&got_tag, &ok));
//    GPR_ASSERT(got_tag == this);
//    GPR_ASSERT(ok);


    // async 2 bloccante
//    std::unique_ptr<grpc::ClientAsyncResponseReader<protobuf::Identifier>> rpc(
//            stub_->PrepareAsyncConnect(&context, user, &cq));
//    rpc->StartCall();
//    rpc->Finish(&reply, &status, this);
//
//    GPR_ASSERT(cq.Next(&got_tag, &ok));
//    GPR_ASSERT(got_tag == this);
//    GPR_ASSERT(ok);


    //parte comune
    if (status.ok())
        std::cout << "Connect just received: " << reply.editorid() << std::endl;
    else
        std::cout << "Connect rpc failed: " << status.error_code() << ": " << status.error_message() << std::endl;

}


void CharacterClient::GetSymbols() {
    protobuf::Identifier request;
    request.set_editorid(55);

    grpc::ClientContext context;
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




