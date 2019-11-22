#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetSymbolsCallData.h"

protobuf::Message MakeMessage(protobuf::Symbol symbol, bool isErase) {
    protobuf::Message msg;
    msg.mutable_symbol()->CopyFrom(symbol);
    msg.set_iserasebool(isErase);
    return msg;
}


protobuf::Symbol MakeSymbol(std::string character, std::string uniqueId, std::vector<int> pos) {
    protobuf::Symbol symbol;
    symbol.set_character(character);
    symbol.set_uniqueid(uniqueId);
    *symbol.mutable_pos() = {pos.begin(), pos.end()};
    return symbol;
}

// Take in the "service" instance (in this case representing an asynchronous
// server) and the completion queue "cq" used for asynchronous communication
// with the gRPC runtime.
GetSymbolsCallData::GetSymbolsCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_), times_(0) {
    // Invoke the serving logic right away.
    Proceed();
}

void GetSymbolsCallData::Proceed(bool ok) {
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
    if (status_ == CREATE) {
        std::cout << "create" << std::endl;

        // Make this instance progress to the PROCESS state.
        status_ = READ;

        // As part of the initial CREATE state, we *request* that the system
        // start processing SayHello requests. In this request, "this" acts are
        // the tag uniquely identifying the request (so that different CallData
        // instances can serve different requests concurrently), in this case
        // the memory address of this CallData instance.
        service_->RequestGetSymbols(&ctx_, &responder_, cq_, cq_, this);
    } else if (status_ == READ) {
        new GetSymbolsCallData(service_, cq_);
        std::cout << "Read status" << std::endl;

        responder_.Read(&request_, this);
        status_ = READ_CALLED;

    } else if (status_ == READ_CALLED) {


//            std::cout << "Received a GetSymbol request for: " << request_.filename() << std::endl;
//        std::for_each(ctx_.auth_context()->begin(),
//                      ctx_.auth_context()->end(),
//                      [](const grpc::AuthProperty &elem) {
//                          std::cout << elem.first << "    " << elem.second << std::endl;
//                      });
//        std::for_each(ctx_.client_metadata().begin(), ctx_.client_metadata().end(),
//                      [](auto &elem) {
//                          std::cout << elem.first << "     " << elem.second << std::endl;
//                      });
        reply_ = MakeMessage(MakeSymbol("a", std::to_string(times_), {0}), false);
        responder_.Write(reply_, this);
        status_ = READ;
    }
}

std::string GetSymbolsCallData::getClass() {
    return "GetSymbolsCallData";
}


protobuf::FileName GetSymbolsCallData::getFileName() {
    return request_;
}
