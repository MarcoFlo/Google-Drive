#include <string>
#include <map>
#include <vector>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetSymbolsCallData.h"

protobuf::Message MakeMessage(const std::string &uniqueFileId, const protobuf::Symbol &symbol, bool isErase) {
    protobuf::Message msg;
    msg.set_uniquefileid(uniqueFileId);
    msg.mutable_symbol()->CopyFrom(symbol);
    msg.set_iserasebool(isErase);
    return msg;
}


protobuf::Symbol MakeSymbol(const std::string &character, const std::string &uniqueId, std::vector<int> pos) {
    protobuf::Symbol symbol;
    symbol.set_character(character);
    symbol.set_uniqueid(uniqueId);
    *symbol.mutable_pos() = {pos.begin(), pos.end()};
    return symbol;
}


GetSymbolsCallData::GetSymbolsCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    status_ = PROCESS;
    service_->RequestGetSymbols(&ctx_, &responder_, cq_, cq_, this);
}

void
GetSymbolsCallData::HandleGet(std::map<std::string, std::vector<GetSymbolsCallData *>> &subscribedClientMap, bool ok) {
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
    if (status_ == PROCESS) {
        new GetSymbolsCallData(service_, cq_);
        status_ = READ;

    } else if (status_ == READ) {
        std::cout << "Read status" << std::endl;

        responder_.Read(&request_, this);
        status_ = READ_CALLED;

    } else if (status_ == READ_CALLED) {

        std::cout << "filename available ->" << request_.fileuniqueid() << std::endl;
        subscribedClientMap[request_.fileuniqueid()].push_back(this);

        //todo delete the write here
        reply_ = MakeMessage("unqueFileId", MakeSymbol("a", std::to_string(110), {0}), false);
        responder_.Write(reply_, this);
        status_ = READ;
    }
}

std::string GetSymbolsCallData::getClass() {
    return "GetSymbolsCallData";
}

void GetSymbolsCallData::HandleSymbol(const protobuf::Message &message) {

    responder_.Write(message, this);
    //todo possibly check the write return status
}




