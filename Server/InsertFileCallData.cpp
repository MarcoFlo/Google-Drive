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
        std::cout << "Received a InsertFile request" << std::endl;
        new InsertFileCallData(service_, cq_);
        status_ = FINISH;

        std::string username = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        protobuf::FileInfo fileInfo = MakeFileInfo(username, request_.filename());
        reply_ = fileInfo;
        (*fileClientMap.mutable_fileclientmap())[username].mutable_fileil()->Add(std::move(fileInfo));
        UpdateFileClientMap(fileClientMap);

        std::ofstream output("fileContainer/" + reply_.fileidentifier());

        responder_.Finish(reply_, grpc::Status::OK, this);

    }
}

