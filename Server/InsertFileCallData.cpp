#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "InsertFileCallData.h"

protobuf::FileInfo MakeFileInfo(const std::string &owner, const std::string &filename) {
    protobuf::FileInfo fileInfo;
    fileInfo.set_usernameo(owner);
    fileInfo.set_filename(filename);
    return fileInfo;
}

InsertFileCallData::InsertFileCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq) : service_(service), cq_(cq),
                                                                          responder_(&ctx_) {
    status_ = READ_CALLED;
    service_->RequestInsertFile(&ctx_, &request_, &responder_, cq_, cq_,
                                this);
}


void InsertFileCallData::HandleInsert(std::map<std::string, std::vector<protobuf::FileInfo>> &fileClientMap, bool ok) {
    if (status_ == READ_CALLED) {
        std::cout << "Received a Insert request" << std::endl;
        new InsertFileCallData(service_, cq_);
        status_ = FINISH;

        std::string username = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        fileClientMap[username].push_back(MakeFileInfo(username, request_.filename()));

        responder_.Finish(reply_, grpc::Status::OK, this);

    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}

