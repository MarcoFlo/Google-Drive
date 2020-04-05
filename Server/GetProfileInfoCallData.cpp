#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetProfileInfoCallData.h"

GetProfileInfoCallData::GetProfileInfoCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    Proceed();

}

void GetProfileInfoCallData::Proceed(bool ok) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestGetProfile(&ctx_, &request_, &responder_, cq_, cq_,
                                  this);
    } else if (status_ == PROCESS) {
        std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();
        std::cout << "Received a GetProfile request from: " << principal << std::endl;
        new GetProfileInfoCallData(service_, cq_);
        status_ = FINISH;




        responder_.Finish(reply_, grpc::Status::OK, this);

    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}

