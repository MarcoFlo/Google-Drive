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

std::string CharacterClient::GetSymbols(const std::string &user) {
    {
        // Data we are sending to the server.
        protobuf::User request;
        request.set_username(user);

        // Container for the data we expect from the server.
        protobuf::Message reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // The producer-consumer queue we use to communicate asynchronously with the
        // gRPC runtime.
        grpc::CompletionQueue cq;

        // Storage for the status of the RPC upon completion.
        grpc::Status status;

        // stub_->PrepareAsyncSayHello() creates an RPC object, returning
        // an instance to store in "call" but does not actually start the RPC
        // Because we are using the asynchronous API, we need to hold on to
        // the "call" instance in order to get updates on the ongoing RPC.
        std::unique_ptr<grpc::ClientAsyncResponseReader<protobuf::Message>> rpc(
                stub_->PrepareAsyncGetSymbols(&context, request, &cq));

        // StartCall initiates the RPC call
        rpc->StartCall();

        // Request that, upon completion of the RPC, "reply" be updated with the
        // server's response; "status" with the indication of whether the operation
        // was successful. Tag the request with the integer 1.
        rpc->Finish(&reply, &status, (void *) 1);

        void *got_tag;
        bool ok = false;
        // Block until the next result is available in the completion queue "cq".
        // The return value of Next should always be checked. This return value
        // tells us whether there is any kind of event or the cq_ is shutting down.
        GPR_ASSERT(cq.Next(&got_tag, &ok));

        // Verify that the result from "cq" corresponds, by its tag, our previous
        // request.
        GPR_ASSERT(got_tag == (void *) 1);
        // ... and that the request was completed successfully. Note that "ok"
        // corresponds solely to the request for updates introduced by Finish().
        GPR_ASSERT(ok);

        // Act upon the status of the actual RPC.
        if (status.ok()) {
            return reply.symbol().character();
        } else {
            return "RPC failed";
        }
    }

}


