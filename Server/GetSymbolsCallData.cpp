#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetSymbolsCallData.h"

GetSymbolsCallData::GetSymbolsCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    status_ = READ_CALLED;
    service_->RequestGetSymbols(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void
GetSymbolsCallData::HandleSubscribedCall(
        std::map<std::string, std::vector<AbstractSubscribedCallData *>> &subscribedClientMap, bool ok) {
    if (status_ == FINISH) {
        std::cout << "Finish GetSymbols" << std::endl;
        delete this;
        return;
    }

    if (!ok) {
        std::cout << "!ok getSymbols" << std::endl;
        responder_.Finish(grpc::Status::OK, this);
        status_ = FINISH;
        return;
    }

    if (status_ == READ_CALLED) {
        new GetSymbolsCallData(service_, cq_);
        status_ = WRITE;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::cout << "Get Symbols requested ->" << request_.filename() << std::endl;

        if (principal == request_.emailo() ||
            std::find(request_.emailal().begin(), request_.emailal().end(), principal) !=
            request_.emailal().end()) {
            //authorized
            mailPrincipal = principal;
            subscribedClientMap[request_.fileidentifier()].erase(
                    std::remove_if(subscribedClientMap[request_.fileidentifier()].begin(),
                                   subscribedClientMap[request_.fileidentifier()].end(),
                                   [&principal](AbstractSubscribedCallData *call) {
                                       return static_cast<GetSymbolsCallData *>(call)->mailPrincipal == principal;
                                   }), subscribedClientMap[request_.fileidentifier()].end());
            subscribedClientMap[request_.fileidentifier()].push_back(this);
        } else {
            status_ = FINISH;
            responder_.Finish(grpc::Status(grpc::StatusCode::PERMISSION_DENIED,
                                           "Non hai accesso a questo file"), this);
            return;
        }
    }
}

void GetSymbolsCallData::HandleSymbol(const protobuf::Message &message) {
    std::cout << "Write message from " << message.symbol().uniqueid() << std::endl;
    responder_.Write(message, this);
}




