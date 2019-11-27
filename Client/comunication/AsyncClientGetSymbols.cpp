#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "AsyncClientGetSymbols.h"

AsyncClientGetSymbols::AsyncClientGetSymbols(const protobuf::FileInfo &request, const std::string &token,
                                             grpc::CompletionQueue &cq_,
                                             std::unique_ptr<protobuf::CharacterService::Stub> &stub_) : request_(
        request) {
    context.AddMetadata("token", token);
    responder = stub_->AsyncGetSymbols(&context, &cq_, this);
}

void AsyncClientGetSymbols::HandleAsync(bool ok) {
    if (callStatus == CREATE) {
        responder->Write(request_, this);
        callStatus = READ;
    } else if (callStatus == READ) {
        if (!ok) {
            CloseRpc();
            return;
        }
        callStatus = READ_CALLED;
        responder->Read(&reply_, this);

    } else if (callStatus == READ_CALLED) {
        std::cout << "Get Symbols received: " << reply_.symbol().uniqueid() << std::endl;
        callStatus = READ;
    } else if (callStatus == FINISH) {
        std::cout << "GetSymbols rpc finished" << std::endl;
        delete this;
    }
}


void AsyncClientGetSymbols::CloseRpc() {
    responder->Finish(&status, this);
    callStatus = FINISH;

}




