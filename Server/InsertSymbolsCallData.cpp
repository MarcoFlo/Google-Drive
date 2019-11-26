#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "InsertSymbolsCallData.h"

InsertSymbolsCallData::InsertSymbolsCallData(protobuf::CharacterService::AsyncService *service,
                                             grpc::ServerCompletionQueue *cq): service_(service), cq_(cq), responder_(&ctx_) {
    Proceed();

}

void InsertSymbolsCallData::Proceed(bool ok) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestInsertSymbols(&ctx_, &request_, &responder_, cq_, cq_,
                               this);
    } else if (status_ == PROCESS) {
        new InsertSymbolsCallData(service_, cq_);

        //        std::cout << "Received a Login request from: " << request_.username() << std::endl;




        const std::vector<grpc::string_ref> tokenV = ctx_.auth_context()->FindPropertyValues("token");
        const grpc::string_ref token = tokenV.back();
//      Se vogliamo restituire un Empty e lasciare il token nei metadati
//      ctx_.AddInitialMetadata("identifier", {token.begin(), token.end()});
        std::string s = {token.begin(), token.end()};
        reply_.set_token(s);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);

    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }

}
