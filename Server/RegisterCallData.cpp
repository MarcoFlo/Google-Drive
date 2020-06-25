#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "RegisterCallData.h"

RegisterCallData::RegisterCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    Proceed();

}

void RegisterCallData::Proceed(bool ok) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestRegister(&ctx_, &request_, &responder_, cq_, cq_,
                                  this);
    } else if (status_ == PROCESS) {
        std::cout << "Received a Register request from: " << request_.user().email() << std::endl;

        std::cout << request_.username() << "\t" << request_.name() << "\t" << request_.surname() << std::endl;

        new RegisterCallData(service_, cq_);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);

    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}

