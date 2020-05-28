#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "LoginCallData.h"


LoginCallData::LoginCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    Proceed();

}

void LoginCallData::Proceed(bool ok) {
    if (status_ == CREATE) {
        status_ = PROCESS;
        service_->RequestLogin(&ctx_, &request_, &responder_, cq_, cq_,
                               this);
    } else if (status_ == PROCESS) {
        std::cout << "Received a Login request from: " << request_.email() << std::endl;
        status_ = FINISH;
        new LoginCallData(service_, cq_);

//        std::for_each(ctx_.auth_context()->begin(),
//                      ctx_.auth_context()->end(),
//                      [](const grpc::AuthProperty &elem) {
//                          std::cout << elem.first << "    " << elem.second << std::endl;
//                      });
//        std::for_each(ctx_.client_metadata().begin(), ctx_.client_metadata().end(),
//                      [](auto &elem) {
//                          std::cout << elem.first << "     " << elem.second << std::endl;
//                      });
//      Se vogliamo restituire un Empty e lasciare il token nei metadati
//      ctx_.AddInitialMetadata("identifier", {token.begin(), token.end()});
        const std::vector<grpc::string_ref> tokenV = ctx_.auth_context()->FindPropertyValues("token");
        const grpc::string_ref &tokenR = tokenV.back();
        std::string tokenS = {tokenR.begin(), tokenR.end()};


        const std::vector<grpc::string_ref> usernameV = ctx_.auth_context()->FindPropertyValues("username");
        const grpc::string_ref &usernameR = usernameV.back();
        std::string usernameS = {usernameR.begin(), usernameR.end()};

        const std::vector<grpc::string_ref> nameV = ctx_.auth_context()->FindPropertyValues("name");
        const grpc::string_ref &nameR = nameV.back();
        std::string nameS = {nameR.begin(), nameR.end()};

        const std::vector<grpc::string_ref> surnameV = ctx_.auth_context()->FindPropertyValues("surname");
        const grpc::string_ref &surnameR = surnameV.back();
        std::string surnameS = {surnameR.begin(), surnameR.end()};

        const std::vector<grpc::string_ref> emailV = ctx_.auth_context()->FindPropertyValues("email");
        const grpc::string_ref &emailR = emailV.back();
        std::string emailS = {emailR.begin(), emailR.end()};

        reply_.set_token(tokenS);
        reply_.mutable_profileinfo()->set_username(usernameS);
        reply_.mutable_profileinfo()->set_name(nameS);
        reply_.mutable_profileinfo()->set_surname(surnameS);
        reply_.mutable_profileinfo()->mutable_user()->set_email(emailS);

        responder_.Finish(reply_, grpc::Status::OK, this);
    } else {
        GPR_ASSERT(status_ == FINISH);
// Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
    }
}
