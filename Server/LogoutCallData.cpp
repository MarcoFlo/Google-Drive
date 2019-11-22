#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "LogoutCallData.h"

LogoutCallData::LogoutCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    Proceed();

}

void LogoutCallData::Proceed(bool ok) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestLogout(&ctx_, &request_, &responder_, cq_, cq_,
                               this);
    } else if (status_ == PROCESS) {
        std::cout << "Received a Logout request" << std::endl;

        std::for_each(ctx_.auth_context()->begin(),
                      ctx_.auth_context()->end(),
                      [](const grpc::AuthProperty &elem) {
                          std::cout << elem.first << "    " << elem.second << std::endl;
                      });
        std::for_each(ctx_.client_metadata().begin(), ctx_.client_metadata().end(),
                      [](auto &elem) {
                          std::cout << elem.first << "     " << elem.second << std::endl;
                      });



        new LogoutCallData(service_, cq_);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);

    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}
