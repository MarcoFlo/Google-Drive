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

void CharacterClient::GetSymbols(const std::string &user) {
    {
        // Data we are sending to the server.
        protobuf::User request;
        request.set_username(user);

        // Call object to store rpc data
        auto *call = new AsyncClientCall;

        // stub_->PrepareAsyncSayHello() creates an RPC object, returning
        // an instance to store in "call" but does not actually start the RPC
        // Because we are using the asynchronous API, we need to hold on to
        // the "call" instance in order to get updates on the ongoing RPC.
        call->response_reader =
                stub_->PrepareAsyncGetSymbols(&call->context, request, &cq_);

        // StartCall initiates the RPC call
        call->response_reader->StartCall();

        // Request that, upon completion of the RPC, "reply" be updated with the
        // server's response; "status" with the indication of whether the operation
        // was successful. Tag the request with the memory address of the call object.
        call->response_reader->Finish(&call->reply, &call->status, (void *) call);

    }

}


void CharacterClient::AsyncCompleteRpc() {
    void *got_tag;
    bool ok = false;


    // Block until the next result is available in the completion queue "cq".
    while (cq_.Next(&got_tag, &ok)) {
        // The tag in this example is the memory location of the call object
        AsyncClientCall* call = static_cast<AsyncClientCall*>(got_tag);

        // Verify that the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        if (call->status.ok())
            std::cout << "Just received: " << call->reply.symbol().character() << std::endl;
        else
            std::cout << "RPC failed" << std::endl;

        // Once we're complete, deallocate the call object.
        delete call;
    }
}