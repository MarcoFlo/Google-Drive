#include <string>
#include <iostream>
#include <algorithm>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "DeleteFileCallData.h"


DeleteFileCallData::DeleteFileCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq) : service_(service), cq_(cq),
                                                                          responder_(&ctx_) {
    status_ = READ_CALLED;
    service_->RequestDeleteFile(&ctx_, &request_, &responder_, cq_, cq_,
                                this);
}


void DeleteFileCallData::HandleDelete(protobuf::FileClientMap &fileClientMap, bool ok) {
    if (status_ == READ_CALLED) {
        std::cout << "Delete request" << std::endl;
        new DeleteFileCallData(service_, cq_);
        status_ = FINISH;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::string filename = request_.filename();
        protobuf::FileList *fileList = &fileClientMap.mutable_fileclientmap()->at(principal);
        auto fileToBeDeleted = std::find_if(fileList->mutable_file()->begin(), fileList->mutable_file()->end(),
                                            [&filename](protobuf::File &file) {
                                                return file.fileinfo().filename() == filename;
                                            });
        if (fileToBeDeleted != fileList->mutable_file()->end()) {
            //se è tra i suoi file
            if ((*fileToBeDeleted).fileinfo().usernameo() == request_.filename()) {
                //se ha l'autorizzazione
                fileList->mutable_file()->erase(fileToBeDeleted);
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

std::string DeleteFileCallData::getClass() {
    return "DeleteFileCallData";
}
