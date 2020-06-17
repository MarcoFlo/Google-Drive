#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetProfileCallData.h"


GetProfileCallData::GetProfileCallData(protobuf::CharacterService::AsyncService *service,
                                       grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    Proceed();
}

void GetProfileCallData::Proceed(bool ok) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestGetProfile(&ctx_, &request_, &responder_, cq_, cq_,
                                    this);
    } else if (status_ == PROCESS) {
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();
        std::cout << "Received a GetProfile request from " << principal << std::endl;

        std::string email = (ctx_.auth_context()->FindPropertyValues("email").end() - 1)->data();
        std::string pw = (ctx_.auth_context()->FindPropertyValues("password").end() - 1)->data();
        std::string username = (ctx_.auth_context()->FindPropertyValues("username").end() - 1)->data();
        std::string name = (ctx_.auth_context()->FindPropertyValues("name").end() - 1)->data();
        std::string surname = (ctx_.auth_context()->FindPropertyValues("surname").end() - 1)->data();

        reply_.set_username(username);
        reply_.set_name(name);
        reply_.set_surname(surname);
        reply_.mutable_user()->set_email(email);
        reply_.mutable_user()->set_password(pw);

        new GetProfileCallData(service_, cq_);
        status_ = FINISH;
        responder_.Finish(reply_, grpc::Status::OK, this);

    } else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
    }
}
