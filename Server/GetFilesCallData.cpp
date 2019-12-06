#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"

#include "GetFilesCallData.h"

GetFilesCallData::GetFilesCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    status_ = PROCESS;
    service_->RequestGetFiles(&ctx_, &request_, &responder_, cq_, cq_,
                              this);
}

void GetFilesCallData::HandleGet(protobuf::FileClientMap &fileClientMap, bool ok) {
    if (status_ == PROCESS) {
        new GetFilesCallData(service_, cq_);
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::cout << "Received a GetFiles request from" << principal << std::endl;

        if (fileClientMap.fileclientmap().contains(principal)) {
            reply_ = fileClientMap.fileclientmap().at(principal);
            status_ = FINISH;
            responder_.Finish(reply_, grpc::Status::OK, this);
        } else {
            status_ = FINISH;
            responder_.Finish(reply_, grpc::Status::OK, this);
        }
    }

    if (status_ == FINISH) {
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}

std::string GetFilesCallData::getClass() {
    return "GetFilesCallData";
}
