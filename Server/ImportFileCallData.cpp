#include <string>
#include <iostream>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "ImportFileCallData.h"


ImportFileCallData::ImportFileCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq) : service_(service), cq_(cq),
                                                                          responder_(&ctx_) {
    status_ = READ_CALLED;
    service_->RequestImportFile(&ctx_, &request_, &responder_, cq_, cq_,
                                this);
}


void ImportFileCallData::HandleFileCall(protobuf::FileClientMap &fileClientMap, bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (status_ == READ_CALLED) {
        new ImportFileCallData(service_, cq_);
        status_ = FINISH;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();
        std::cout << "Import file request from " << principal;

        std::string fileIdentifier = request_.fileidentifier();

        for (auto userFileDetails = fileClientMap.mutable_fileclientmap()->begin();
             userFileDetails != fileClientMap.mutable_fileclientmap()->end(); ++userFileDetails) {
            auto fileToBeImported = std::find_if(
                    userFileDetails->second.mutable_fileil()->begin(),
                    userFileDetails->second.mutable_fileil()->end(),
                    [&fileIdentifier](protobuf::FileInfo &file) {
                        return file.fileidentifier() == fileIdentifier;
                    });

            if (fileToBeImported != userFileDetails->second.mutable_fileil()->end()) {
                auto alreadyShared = std::find(fileToBeImported->emailal().begin(), fileToBeImported->emailal().end(),
                                               principal);
                // se non è stata già fatta la condivisione. Il controllo è fatto solo sulla lista delle condivisioni dell'owner
                if (alreadyShared == fileToBeImported->emailal().end()) {
                    //emailShare added to the list of the owner
                    fileToBeImported->add_emailal(principal);

                    //fileInfo added to the list of the sharer
                    protobuf::FileInfo file_copy(*fileToBeImported);
                    (*fileClientMap.mutable_fileclientmap())[principal].mutable_fileil()->Add(
                            (std::move(file_copy)));

                    UpdateFileClientMap(fileClientMap);
                }
                break;
            }
        }


        responder_.Finish(reply_, grpc::Status::OK, this);
    }
}

