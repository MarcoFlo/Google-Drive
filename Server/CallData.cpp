//
// Created by flori on 28/10/2019.
//

#include <thread>
#include <chrono>

#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "CallData.h"


protobuf::Message MakeMessage(int idEditor, protobuf::Symbol symbol, bool isErase) {
    protobuf::Message msg;
    msg.set_ideditor(idEditor);
    msg.mutable_symbol()->CopyFrom(symbol);
    msg.set_iserasebool(isErase);
    return msg;
}


protobuf::Symbol MakeSymbol(std::string character, int uniqueId, std::vector<int> pos) {
    protobuf::Symbol symbol;
    symbol.set_character(character);
    symbol.set_uniqueid(uniqueId);
    *symbol.mutable_pos() = {pos.begin(), pos.end()};
    return symbol;
}

// Take in the "service" instance (in this case representing an asynchronous
// server) and the completion queue "cq" used for asynchronous communication
// with the gRPC runtime.
CallData::CallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
    // Invoke the serving logic right away.
    Proceed();
}


void CallData::Proceed() {
    if (status_ == CREATE) {
        // Make this instance progress to the PROCESS state.
        status_ = PROCESS;

        // As part of the initial CREATE state, we *request* that the system
        // start processing SayHello requests. In this request, "this" acts are
        // the tag uniquely identifying the request (so that different CallData
        // instances can serve different requests concurrently), in this case
        // the memory address of this CallData instance.
        service_->RequestGetSymbols(&ctx_, &request_, &responder_, cq_, cq_,
                                    this);
    } else if (status_ == PROCESS) {
        std::cout << "Received a request from: " << request_.username() << std::endl;

        // Spawn a new CallData instance to serve new clients while we process
        // the one for this CallData. The instance will deallocate itself as
        // part of its FINISH state.
        new CallData(service_, cq_);

        reply_ = MakeMessage(0, MakeSymbol("a", 0, {0}), false);
        std::this_thread::sleep_for(std::chrono::seconds(5));

        // And we are done! Let the gRPC runtime know we've finished, using the
        // memory address of this instance as the uniquely identifying tag for
        // the event.
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);
    } else {
        GPR_ASSERT(status_ == FINISH);
        // Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}

