#ifndef SERVER_MYSERVICEAUTHPROCESSOR_H
#define SERVER_MYSERVICEAUTHPROCESSOR_H


class MyServiceAuthProcessor : public grpc::AuthMetadataProcessor {
public:

    MyServiceAuthProcessor();

    grpc::Status
    Process(const InputMetadata &auth_metadata, grpc::AuthContext *context, OutputMetadata *consumed_auth_metadata,
            OutputMetadata *response_metadata) override;

    grpc::Status ProcessRegister(const InputMetadata &auth_metadata);

    grpc::Status ProcessLogin(const InputMetadata &auth_metadata, grpc::AuthContext *context);

private:
    void LoadUserMap();

    void UpdateUserMap(google::protobuf::MapPair<std::basic_string<char>, std::basic_string<char>> &pair);

    struct Const{
            static const std::string &TokenKeyName() {
                static std::string _("token");
                return _;
            }

            static const std::string &PeerIdentityPropertyName() {
                static std::string _("username");
                return _;
            }
    };

    //key=username, value=protobuf:User da salvare su db
    protobuf::UserMap userMap;

    //key=identifier, value=username da tenere a runtime
    std::map<std::string, std::string> tokenMap;

    int idCounter;

    grpc::Status ProcessLogout(std::basic_string<char> basicString);
};


#endif //SERVER_MYSERVICEAUTHPROCESSOR_H
