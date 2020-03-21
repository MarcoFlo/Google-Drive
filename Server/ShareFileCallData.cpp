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


void ShareFileCallData::HandleFileCall(protobuf::FileClientMap &fileClientMap, bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (status_ == READ_CALLED) {
        std::cout << "Share file request" << std::endl;
        new ShareFileCallData(service_, cq_);
        status_ = FINISH;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::string fileIdentifier = request_.fileidentifier();
        protobuf::FilesInfoList *fileList = &fileClientMap.mutable_fileclientmap()->at(principal);
        auto fileToBeShared = std::find_if(fileList->mutable_fileil()->begin(), fileList->mutable_fileil()->end(),
                                           [&fileIdentifier](protobuf::FileInfo &file) {
                                               return file.fileidentifier() == fileIdentifier;
                                           });

        if (fileToBeShared != fileList->mutable_fileil()->end()) {
            //se è tra i suoi file
            if (fileToBeShared->usernameo() == request_.usernameo()) {
                //se ha l'autorizzazione
                const std::string usernameShare = ctx_.auth_context()->FindPropertyValues(
                        "usernameshare").front().data();
                //usernameShare added to the list of the owner
                fileToBeShared->add_usernamesal(usernameShare);

                //fileInfo added to the list of the sharer
                (*fileClientMap.mutable_fileclientmap())[usernameShare].mutable_fileil()->Add(
                        (std::move(*fileToBeShared)));

                UpdateFileClientMap(fileClientMap);

                responder_.Finish(reply_, grpc::Status::OK, this);
            } else {
                responder_.Finish(reply_, grpc::Status(grpc::StatusCode::PERMISSION_DENIED,
                                                       "Un file pu essere condiviso solo dal proprietario"), this);
            }
        } else {
            responder_.Finish(reply_, grpc::Status(grpc::StatusCode::NOT_FOUND, "File non presente"), this);
        }
    }
}

