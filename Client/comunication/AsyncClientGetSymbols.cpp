#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "AsyncClientGetSymbols.h"

AsyncClientGetSymbols::AsyncClientGetSymbols(const protobuf::FileInfo &request, const std::string &token,
                                             grpc::CompletionQueue &cq_,
                                             std::unique_ptr<protobuf::CharacterService::Stub> &stub_)
        : callStatus(READ), request_(request) {
    context.AddMetadata("token", token);
    responder = stub_->AsyncGetSymbols(&context, request_, &cq_, this);
}

void AsyncClientGetSymbols::HandleAsync(bool ok) {
    if (!ok) {
        CloseRpc();
        return;
    }
    if (callStatus == READ) {
        callStatus = READ_CALLED;
        responder->Read(&reply_, this);
    } else if (callStatus == READ_CALLED) {
        std::cout << "Get Symbols received: " << reply_.symbol().uniqueid() << "\t" << reply_.symbol().character()
                  << std::endl;
        //todo inserire il simbolo
        responder->Read(&reply_, this);
    } else if (callStatus == FINISH) {
        std::cout << "GetSymbols rpc finished" << std::endl;
        delete this;
    }
}


void AsyncClientGetSymbols::CloseRpc() {
// non funziona correttamente in grpc
    std::cout << "CloseRpc()" << std::endl;
    responder->Finish(&status, this);
    callStatus = FINISH;

}




