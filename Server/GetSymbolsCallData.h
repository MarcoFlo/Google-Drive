//
// Created by flori on 30/10/2019.
//

#ifndef SERVER_GETSYMBOLSCALLDATA_H
#define SERVER_GETSYMBOLSCALLDATA_H

#include "CallData.h"

class GetSymbolsCallData final: public CallData {
public:
    GetSymbolsCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq);
    void Proceed();

private:

// The means of communication with the gRPC runtime for an asynchronous
// server.
    protobuf::CharacterService::AsyncService *service_;
// The producer-consumer queue where for asynchronous server notifications.
    grpc::ServerCompletionQueue *cq_;
// Context for the rpc, allowing to tweak aspects of it such as the use
// of compression, authentication, as well as to send metadata back to the
// client.
    grpc::ServerContext ctx_;

// What we get from the client.
    protobuf::User request_;
// What we send back to the client.
    protobuf::Message reply_;

// The means to get back to the client.
    grpc::ServerAsyncWriter<protobuf::Message> responder_;

// Let's implement a tiny state machine with the following states.
    enum CallStatus {
        CREATE, PROCESS, FINISH
    };
    CallStatus status_;  // The current serving state.

    int times_;

};


#endif //SERVER_GETSYMBOLSCALLDATA_H
