#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "AsyncClientGetSymbols.h"

void AsyncClientGetSymbols::HandleAsync(bool ok) {
    if (callStatus == CREATE) {
// todo capire perchè se non fai una prima read, la reply è vuota
        responder->Read(&reply_, (void *) this);
        callStatus = PROCESS;
    } else if (callStatus == PROCESS) {
        if (!ok) {
            responder->Finish(&status, (void *) this);
            callStatus = FINISH;
            return;
        }
        responder->Read(&reply_, (void *) this);
        std::cout << "Get Symbols received: " << reply_.symbol().uniqueid() << std::endl;

    } else if (callStatus == FINISH) {
        std::cout << "Server finished rpc" << std::endl;
        delete this;
    }
}

AsyncClientGetSymbols::AsyncClientGetSymbols(const protobuf::FileName &request, const std::string &token,
                                             grpc::CompletionQueue &cq_,
                                             std::unique_ptr<protobuf::CharacterService::Stub> &stub_) {
    context.AddMetadata("token", token);
    responder = stub_->AsyncGetSymbols(&context, request, &cq_, (void *) this);
}

void AsyncClientGetSymbols::CloseRpc() {
    responder->Finish(&status, (void *) this);
    //todo controllare questo delete
    delete this;

}




