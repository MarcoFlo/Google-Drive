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
    status_ = PROCESS;
    service_->RequestGetSymbols(&ctx_, &responder_, cq_, cq_, this);
}

void
GetSymbolsCallData::HandleSubscribedCall(
        std::map<std::string, std::vector<AbstractSubscribedCallData *>> &subscribedClientMap, bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (!ok) {
        std::cout << "finish getSymbols" << std::endl;
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
    std::cout << "Write message back to subscribed clients " << std::endl;
    responder_.Write(message, this);
}




