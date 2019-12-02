#include <string>
#include <map>
#include <vector>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetSymbolsCallData.h"
#include "InsertSymbolsCallData.h"

InsertSymbolsCallData::InsertSymbolsCallData(protobuf::CharacterService::AsyncService *service,
                                             grpc::ServerCompletionQueue *cq) : service_(service), cq_(cq),
                                                                                responder_(&ctx_) {
    status_ = PROCESS;
    service_->RequestInsertSymbols(&ctx_, &responder_, cq_, cq_,
                                   this);
}

void InsertSymbolsCallData::HandleInsert(std::map<std::string, std::vector<GetSymbolsCallData *>> &subscribedClientMap,
                                         std::map<std::string, std::vector<protobuf::FileInfo>> &fileClientMap,
                                         bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (!ok) {
        std::cout << "finish" << std::endl;
//        responder_.Finish(&reply_, grpc::Status::OK, this);
        status_ = FINISH;
        return;
    }
    if (status_ == PROCESS) {
        status_ = READ;

        new InsertSymbolsCallData(service_, cq_);

    } else if (status_ == READ) {
        status_ = READ_CALLED;
        responder_.Read(&request_, this);


    } else if (status_ == READ_CALLED) {
        status_ = READ;
        protobuf::Message messageReceived = request_;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        auto fileInsert = std::find_if(fileClientMap.at(principal).begin(), fileClientMap.at(principal).end(),
                                       [&messageReceived](protobuf::FileInfo &fileInfo) {
                                           return messageReceived.fileinfo().filename() == fileInfo.filename();
                                       });

        if (fileInsert != fileClientMap.at(principal).end()) {
            std::for_each(
                    subscribedClientMap.at(request_.fileinfo().filename() + request_.fileinfo().usernameo()).begin(),
                    subscribedClientMap.at(request_.fileinfo().filename() + request_.fileinfo().usernameo()).end(),
                    [&messageReceived](GetSymbolsCallData *getSymbolsCallData) {
                        getSymbolsCallData->HandleSymbol(messageReceived);
                    });
        }
    }
}
