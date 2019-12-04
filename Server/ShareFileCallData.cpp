#include <string>
#include <iostream>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "ShareFileCallData.h"


ShareFileCallData::ShareFileCallData(protobuf::CharacterService::AsyncService *service,
                                     grpc::ServerCompletionQueue *cq) : service_(service), cq_(cq),
                                                                        responder_(&ctx_) {
    status_ = READ_CALLED;
    service_->RequestShareFile(&ctx_, &request_, &responder_, cq_, cq_,
                               this);
}


void ShareFileCallData::HandleShare(protobuf::FileClientMap &fileClientMap, bool ok) {
    if (status_ == READ_CALLED) {
        std::cout << "Share file request" << std::endl;
        new ShareFileCallData(service_, cq_);
        status_ = FINISH;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::string filename = request_.filename();
        protobuf::FileList *fileList = &fileClientMap.mutable_fileclientmap()->at(principal);
        auto fileToBeShared = std::find_if(fileList->mutable_file()->begin(), fileList->mutable_file()->end(),
                                           [&filename](protobuf::File &file) {
                                               return file.fileinfo().filename() == filename;
                                           });

        if (fileToBeShared != fileList->mutable_file()->end()) {
            //se è tra i suoi file
            if (fileToBeShared->fileinfo().usernameo() == request_.filename()) {
                //se ha l'autorizzazione
                const std::string usernameShare = ctx_.auth_context()->FindPropertyValues(
                        "usernameshare").front().data();
                fileToBeShared->mutable_fileinfo()->add_usernamesal(usernameShare);
                UpdateFileClientMap(fileClientMap);

                responder_.Finish(reply_, grpc::Status::OK, this);
            }
        } else {
            //todo
            responder_.Finish(reply_, grpc::Status::OK, this);
        }

    } else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
    }
}

std::string ShareFileCallData::getClass() {
    return "ShareFileCallData";
}
