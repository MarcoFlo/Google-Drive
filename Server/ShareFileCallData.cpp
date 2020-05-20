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
        new ShareFileCallData(service_, cq_);
        status_ = FINISH;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();
        std::cout << "Share file request from " << principal;

        std::string fileIdentifier = request_.fileidentifier();
        protobuf::FilesInfoList *fileList = &fileClientMap.mutable_fileclientmap()->at(principal);
        auto fileToBeShared = std::find_if(fileList->mutable_fileil()->begin(), fileList->mutable_fileil()->end(),
                                           [&fileIdentifier](protobuf::FileInfo &file) {
                                               return file.fileidentifier() == fileIdentifier;
                                           });

        if (fileToBeShared != fileList->mutable_fileil()->end()) {
            //se è tra i suoi file
            if (fileToBeShared->usernameo() == principal) {
                //se ha l'autorizzazione
                std::string emailShare = ctx_.auth_context()->FindPropertyValues(
                        "emailshare").front().data();
                std::cout << " to " << emailShare << " for " << fileToBeShared->filename() << std::endl;

                //usernameShare added to the list of the owner
                fileToBeShared->add_usernamesal(emailShare);

                //fileInfo added to the list of the sharer
                protobuf::FileInfo file_copy(*fileToBeShared);
                (*fileClientMap.mutable_fileclientmap())[emailShare].mutable_fileil()->Add(
                        (std::move(file_copy)));

                UpdateFileClientMap(fileClientMap);

                responder_.Finish(reply_, grpc::Status::OK, this);
            } else {
                responder_.Finish(reply_, grpc::Status(grpc::StatusCode::PERMISSION_DENIED,
                                                       "Un file può essere condiviso solo dal proprietario"), this);
            }
        } else {
            responder_.Finish(reply_, grpc::Status(grpc::StatusCode::NOT_FOUND, "File non presente"), this);
        }
    }
}

