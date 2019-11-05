//
// Created by flori on 05/11/2019.
//

#ifndef CLIENT_MYCUSTOMAUTHENTICATOR_H
#define CLIENT_MYCUSTOMAUTHENTICATOR_H


class MyCustomAuthenticator : public grpc::MetadataCredentialsPlugin {
public:
    MyCustomAuthenticator(const grpc::string& ticket) : ticket_(ticket) {}

    grpc::Status GetMetadata(
            grpc::string_ref service_url, grpc::string_ref method_name,
            const grpc::AuthContext& channel_auth_context,
            std::multimap<grpc::string, grpc::string>* metadata) override {
        metadata->insert(std::make_pair("x-custom-auth-ticket", ticket_));
        return grpc::Status::OK;
    }

private:
    grpc::string ticket_;
};

#endif //CLIENT_MYCUSTOMAUTHENTICATOR_H
