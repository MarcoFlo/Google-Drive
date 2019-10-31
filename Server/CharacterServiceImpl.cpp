//
// Created by flori on 23/10/2019.
//
#include <algorithm>
#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "CharacterServiceImpl.h"
#include "GetSymbolsCallData.h"
#include "ConnectCallData.h"


CharacterServiceImpl::~CharacterServiceImpl() {
    server_->Shutdown();
    // Always shutdown the completion queue after the server.
    cq_->Shutdown();
}

void CharacterServiceImpl::Run() {
    std::string server_address("0.0.0.0:50051");

    grpc::ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service_" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *asynchronous* service.
    builder.RegisterService(&service_);
    // Get hold of the completion queue used for the asynchronous communication
    // with the gRPC runtime.
    cq_ = builder.AddCompletionQueue();
    // Finally assemble the server.
    server_ = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;

    // Proceed to the server's main loop.
    HandleRpcs();
}


void CharacterServiceImpl::HandleRpcs() {
    new ConnectCallData(&service_, cq_.get());
    new GetSymbolsCallData(&service_, cq_.get());
    void *tag;  // uniquely identifies a request.
    bool ok;
    while (true) {
        GPR_ASSERT(cq_->Next(&tag, &ok));
        GPR_ASSERT(ok);
        static_cast<CallData *>(tag)->Proceed();
    }
}




