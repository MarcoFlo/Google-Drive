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


void DeleteFileCallData::HandleFileCall(protobuf::FileClientMap &fileClientMap, bool ok) {
    //ok non viene controllato perchè la connessione viene Finish solo dal server
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (status_ == READ_CALLED) {
        std::cout << "Delete request" << std::endl;
        new DeleteFileCallData(service_, cq_);
        status_ = FINISH;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::string fileIdentifier = request_.identifier();
        protobuf::FilesInfoList *fileList = &fileClientMap.mutable_fileclientmap()->at(principal);
        auto fileToBeDeleted = std::find_if(fileList->mutable_fileil()->begin(), fileList->mutable_fileil()->end(),
                                            [&fileIdentifier](protobuf::FileInfo &file) {
                                                return file.identifier() == fileIdentifier;
                                            });
        if (fileToBeDeleted != fileList->mutable_fileil()->end()) {
            //se è tra i suoi file
            if ((*fileToBeDeleted).usernameo() == request_.usernameo()) {
                //se ha l'autorizzazione
                if (remove(request_.identifier().c_str()) == 0) {
                    //cancello da tutti le filesInfoList il file
                    std::for_each(fileClientMap.mutable_fileclientmap()->begin(),
                                  fileClientMap.mutable_fileclientmap()->end(), [&fileIdentifier](auto &pair) {
                                auto fileToBeDeleted = std::find_if(pair.second.mutable_fileil()->begin(),
                                                                    pair.second.mutable_fileil()->end(),
                                                                    [&fileIdentifier](protobuf::FileInfo &file) {
                                                                        return file.identifier() == fileIdentifier;
                                                                    });
                                pair.second.mutable_fileil()->erase(fileToBeDeleted);

                            });
                    UpdateFileClientMap(fileClientMap);

                    responder_.Finish(reply_, grpc::Status::OK, this);
                } else {
                    std::cout << "It wasn't possible to delete the file" << std::endl; //probably not closed correctly
                    responder_.Finish(reply_, grpc::Status(grpc::StatusCode::INTERNAL, "Internal error"), this);
                }
            } else {
                responder_.Finish(reply_, grpc::Status(grpc::StatusCode::PERMISSION_DENIED,
                                                       "Un file può essere cancellato solo dal proprietario"), this);
            }
        } else {
            responder_.Finish(reply_, grpc::Status(grpc::StatusCode::NOT_FOUND, "File non presente"), this);
        }
    }
}
