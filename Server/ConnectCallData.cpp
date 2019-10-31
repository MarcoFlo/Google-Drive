//
// Created by flori on 30/10/2019.
//

#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "ConnectCallData.h"

ConnectCallData::ConnectCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
    Proceed();

}

void ConnectCallData::Proceed() {
    if (status_ == CREATE) {
        // Make this instance progress to the PROCESS state.
        status_ = PROCESS;

        // As part of the initial CREATE state, we *request* that the system
        // start processing SayHello requests. In this request, "this" acts are
        // the tag uniquely identifying the request (so that different CallData
        // instances can serve different requests concurrently), in this case
        // the memory address of this CallData instance.
        service_->RequestConnect(&ctx_, &request_, &responder_, cq_, cq_,
                                 this);
    } else if (status_ == PROCESS) {
        std::cout << "Received a request from: " << request_.username() << std::endl;
        new ConnectCallData(service_, cq_);

        reply_.set_editorid(0);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);

    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}
