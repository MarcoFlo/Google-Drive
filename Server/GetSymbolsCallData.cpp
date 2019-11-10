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
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE), times_(0) {
    // Invoke the serving logic right away.
    Proceed();
}

void GetSymbolsCallData::Proceed() {
    if (status_ == CREATE) {
        // Make this instance progress to the PROCESS state.
        status_ = PROCESS;

        // As part of the initial CREATE state, we *request* that the system
        // start processing SayHello requests. In this request, "this" acts are
        // the tag uniquely identifying the request (so that different CallData
        // instances can serve different requests concurrently), in this case
        // the memory address of this CallData instance.
        service_->RequestGetSymbols(&ctx_, &request_, &responder_, cq_, cq_,
                                    this);
    } else if (status_ == PROCESS) {
        std::cout << ctx_.auth_context()->GetPeerIdentityPropertyName() << std::endl;
        std::for_each(ctx_.auth_context()->begin(),
                      ctx_.auth_context()->end(),
                      [](const grpc::AuthProperty &elem) {
                          std::cout << elem.first << "    " << elem.second << std::endl;
                      });
        std::for_each(ctx_.client_metadata().begin(), ctx_.client_metadata().end(),
                      [](auto &elem) {
                          std::cout << elem.first << "     " << elem.second << std::endl;
                      });

        std::cout << "Received a GetSymbol request for: " << request_.filename() << std::endl;

        if (times_ == 0)
            new GetSymbolsCallData(service_, cq_);

        if (times_++ <= 3) {
            reply_ = MakeMessage(MakeSymbol("a", std::to_string(times_), {0}), false);
            responder_.Write(reply_, this);
            std::this_thread::sleep_for(std::chrono::seconds(5));
        } else {
            status_ = FINISH;
            responder_.Finish(grpc::Status::OK, this);
        }
    } else {
        GPR_ASSERT(status_ == FINISH);
        // Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}