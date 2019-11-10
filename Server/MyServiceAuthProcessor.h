#ifndef SERVER_MYSERVICEAUTHPROCESSOR_H
#define SERVER_MYSERVICEAUTHPROCESSOR_H


class MyServiceAuthProcessor : public grpc::AuthMetadataProcessor {
public:

    MyServiceAuthProcessor();

    grpc::Status
    Process(const InputMetadata &auth_metadata, grpc::AuthContext *context, OutputMetadata *consumed_auth_metadata,
            OutputMetadata *response_metadata) override;

    grpc::Status ProcessRegister(const InputMetadata &auth_metadata);

    grpc::Status ProcessLogin(const InputMetadata &auth_metadata, grpc::AuthContext *contex);

private:
    void LoadUserMap();

    void UpdateUserMap(std::string &username, std::string &password);

    struct Const {
        static const std::string &TokenKeyName() {
            static std::string _("token");
            return _;
        }

        static const std::string &PeerIdentityPropertyName() {
            static std::string _("username");
            return _;
        }
    };

    protobuf::UserMap userMap;

    std::map<std::string, std::string> tokens = {
            {"abcd",  "abcd"},
            {"abcde", "abcde"}
    };

};


#endif //SERVER_MYSERVICEAUTHPROCESSOR_H
