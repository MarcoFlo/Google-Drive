#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetFileContentCallData.h"


GetFileContentCallData::GetFileContentCallData(protobuf::CharacterService::AsyncService *service,
                                               grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    status_ = READ_CALLED;
    service_->RequestGetFileContent(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void
GetFileContentCallData::HandleGet(protobuf::FileClientMap &fileClientMap, bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (!ok) {
        std::cout << "finish" << std::endl;
        responder_.Finish(grpc::Status::OK, this);
        status_ = FINISH;
        return;
    }

    if (status_ == READ_CALLED) {
        new GetFileContentCallData(service_, cq_);
        protobuf::FileInfo messageReceived = request_;


        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::cout << "Get file requested ->" << request_.filename() << std::endl;

        if (fileClientMap.fileclientmap().contains(principal)) {
            auto fileGet = std::find_if(fileClientMap.mutable_fileclientmap()->at(principal).mutable_file()->begin(),
                                        fileClientMap.mutable_fileclientmap()->at(principal).mutable_file()->end(),
                                        [&messageReceived](protobuf::File &file) {
                                            return messageReceived.filename() == file.fileinfo().filename();
                                        });
            if (fileGet != fileClientMap.mutable_fileclientmap()->at(principal).mutable_file()->end()) {
                status_ = WRITE;
                replyF_ = *fileGet;
            }
        } else {
            responder_.Finish(grpc::Status::OK, this);
            status_ = FINISH;
        }
    }
    else if(status_ == WRITE)
    {
        //todo
//        char *array = new char[5];
//        replyF_.symbols().Get(0).SerializeToArray(array+5, 5);

    }
}

std::string GetFileContentCallData::getClass() {
    return "GetFileContentCallData";
}