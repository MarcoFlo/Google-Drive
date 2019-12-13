#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetSymbolsCallData.h"

//protobuf::Message MakeMessage(const std::string &filename, const std::string &owner, const protobuf::Symbol &symbol, bool isErase) {
//    protobuf::Message msg;
//    msg.mutable_fileinfo()->set_filename(filename);
//    msg.mutable_fileinfo()->set_usernameo(owner);
//    msg.mutable_symbol()->CopyFrom(symbol);
//    msg.set_iserasebool(isErase);
//    return msg;
//}
//
//protobuf::Symbol MakeSymbol(const std::string &character, const std::string &uniqueId, std::vector<int> pos) {
//    protobuf::Symbol symbol;
//    symbol.set_character(character);
//    symbol.set_uniqueid(uniqueId);
//    *symbol.mutable_pos() = {pos.begin(), pos.end()};
//    return symbol;
//}


GetSymbolsCallData::GetSymbolsCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    status_ = PROCESS;
    service_->RequestGetSymbols(&ctx_, &responder_, cq_, cq_, this);
}

void
GetSymbolsCallData::HandleSubscribedCall(std::map<std::string, std::vector<AbstractSubscribedCallData *>> &subscribedClientMap, bool ok) {
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
        status_ = READ_CALLED;

        new GetSymbolsCallData(service_, cq_);
        responder_.Read(&request_, this);


    } else if (status_ == READ) {
        status_ = READ_CALLED;

        std::cout << "Read status" << std::endl;

        responder_.Read(&request_, this);

    } else if (status_ == READ_CALLED) {
        status_ = READ;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::cout << "Get Symbols requested ->" << request_.filename() << std::endl;

        if (principal == request_.usernameo() ||
            std::find(request_.usernamesal().begin(), request_.usernamesal().end(), principal) !=
            request_.usernamesal().end()) {
            //authorized
            subscribedClientMap[request_.identifier()].push_back(this);
        } else {
            //not authorized
            responder_.Finish(grpc::Status::OK, this);
            status_ = FINISH;
            return;
        }

    }
}

void GetSymbolsCallData::HandleSymbol(const protobuf::Message &message) {

    responder_.Write(message, this);
    //todo possibly check the write return status
}




