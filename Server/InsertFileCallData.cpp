#include <string>
#include <iostream>
#include <chrono>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "InsertFileCallData.h"

protobuf::FileInfo MakeFileInfo(const std::string &owner, const std::string &filename) {
    protobuf::FileInfo fileInfo;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
    fileInfo.set_fileidentifier(std::to_string(ns.count()) + filename);
    fileInfo.set_usernameo(owner);
    fileInfo.set_filename(filename);
    return fileInfo;
}

InsertFileCallData::InsertFileCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq) : service_(service), cq_(cq),
                                                                          responder_(&ctx_) {
    status_ = PROCESS;
    service_->RequestInsertFile(&ctx_, &request_, &responder_, cq_, cq_,
                                this);
}

void InsertFileCallData::HandleFileCall(protobuf::FileClientMap &fileClientMap, bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (status_ == PROCESS) {
        new InsertFileCallData(service_, cq_);
        status_ = FINISH;

        std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::string filename = request_.filename();
        std::cout << "Received a InsertFile request -> " << filename << std::endl;

        if (fileClientMap.mutable_fileclientmap()->find(principal) != fileClientMap.mutable_fileclientmap()->end()) {
            //controllo per il nome file duplicato
            auto fileGet = std::find_if(fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->begin(),
                                        fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end(),
                                        [&filename](protobuf::FileInfo &file) {
                                            return filename == file.filename();
                                        });
            if (fileGet == fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end()) {
                responder_.Finish(reply_, grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "File duplicato"), this);

            }
        }

        protobuf::FileInfo fileInfo = MakeFileInfo(principal, filename);
        reply_ = fileInfo;
        (*fileClientMap.mutable_fileclientmap())[principal].mutable_fileil()->Add(std::move(fileInfo));

        //aggiorna la la mappa su file
        UpdateFileClientMap(fileClientMap);

        //crea il nuovo file
        std::ofstream output("fileContainer/" + reply_.fileidentifier());

        responder_.Finish(reply_, grpc::Status::OK, this);
    }
}



/*
 *
 *
 *     if (status_ == PROCESS) {
        new InsertFileCallData(service_, cq_);
        status_ = FINISH;

        std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::string filename = request_.filename();
        std::cout << "Received a InsertFile request -> " << filename << std::endl;

        try {
            fileClientMap.mutable_fileclientmap()->at(principal);
            //controllo per il nome file duplicato
            auto fileGet = std::find_if(fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->begin(),
                                        fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end(),
                                        [&filename](protobuf::FileInfo &file) {
                                            return filename == file.filename();
                                        });
            if (fileGet == fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end()) {
                responder_.Finish(reply_, grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "File duplicato"), this);

            }
        }
        catch (...) {
            std::cout << "exc";
        }
        protobuf::FileInfo fileInfo = MakeFileInfo(principal, filename);
        reply_ = fileInfo;
        (*fileClientMap.mutable_fileclientmap())[principal].mutable_fileil()->Add(std::move(fileInfo));

        //aggiorna la la mappa su file
        UpdateFileClientMap(fileClientMap);

        //crea il nuovo file
        std::ofstream output("fileContainer/" + reply_.fileidentifier());

        responder_.Finish(reply_, grpc::Status::OK, this);
    }
}

 */