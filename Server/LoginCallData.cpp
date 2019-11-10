#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "LoginCallData.h"


LoginCallData::LoginCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
    Proceed();

}

void LoginCallData::Proceed() {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestLogin(&ctx_, &request_, &responder_, cq_, cq_,
                               this);
    } else if (status_ == PROCESS) {
        std::cout << "Received a Login request from: " << request_.username() << std::endl;
        new LoginCallData(service_, cq_);

        const grpc::string_ref identifier = ctx_.auth_context()->FindPropertyValues("identifier")[0];
//      ctx_.AddInitialMetadata("identifier", {identifier.begin(), identifier.end()});
        std::string s = {identifier.begin(), identifier.end()};
        reply_.set_id(s);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);

    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}
