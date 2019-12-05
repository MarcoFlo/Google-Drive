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
            auto fileGet = std::find_if(fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->begin(),
                                        fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end(),
                                        [&messageReceived](protobuf::FileInfo &file) {
                                            return messageReceived.identifier() == file.identifier();
                                        });
            if (fileGet != fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end()) {
                status_ = WRITE;
                fileIdentifier = (*fileGet).identifier();
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
//        std::unique_ptr<char[]> str(new char[4]);
        protobuf::SymbolVector symbolVector;
        std::ifstream input("fileContainer/" + fileIdentifier, std::ios_base::in | std::ios_base::binary);
        symbolVector.ParseFromIstream(&input);



    }
}

std::string GetFileContentCallData::getClass() {
    return "GetFileContentCallData";
}