#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "SetProfileCallData.h"



SetProfileCallData::SetProfileCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    Proceed();
}

void SetProfileCallData::Proceed(bool ok) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestSetProfile(&ctx_, &request_, &responder_, cq_, cq_,
                                    this);
    } else if (status_ == PROCESS) {
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();
        std::cout << "Received a SetProfile request from " << principal << std::endl;

        new SetProfileCallData(service_, cq_);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);
    } else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
    }
}