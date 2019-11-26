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
    HandleInsert();

}

void InsertSymbolsCallData::HandleInsert(std::map<std::string, std::vector<GetSymbolsCallData *>> &subscribedClientMap,
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
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestInsertSymbols(&ctx_, &responder_, cq_, cq_,
                                       this);
    } else if (status_ == PROCESS) {
        status_ = READ;

        new InsertSymbolsCallData(service_, cq_);
        responder_.Read(&request_, this);

    } else if (status_ == READ) {
        status_ = READ_CALLED;


//subscribedClientMap.at(request_.)




    } else if (status_ == READ_CALLED) {

    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}
