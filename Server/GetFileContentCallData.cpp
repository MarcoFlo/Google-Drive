#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetFileContentCallData.h"


GetFileContentCallData::GetFileContentCallData(protobuf::CharacterService::AsyncService *service,
                                               grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    status_ = READ_CALLED;
    service_->RequestGetFileContent(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void
GetFileContentCallData::Proceed(bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (!ok) {
        std::cout << "finish" << std::endl;
        responder_.Finish(grpc::Status::OK, this);
        status_ = FINISH;
        return;
    }



   if (status_ == READ_CALLED) {
        new GetFileContentCallData(service_, cq_);

        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::cout << "Get file requested ->" << request_.filename() << std::endl;


        //not authorized
        responder_.Finish(grpc::Status::OK, this);
        status_ = FINISH;
        return;


    }
}

std::string GetFileContentCallData::getClass() {
    return "GetFileContentCallData";
}