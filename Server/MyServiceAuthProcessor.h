#ifndef SERVER_MYSERVICEAUTHPROCESSOR_H
#define SERVER_MYSERVICEAUTHPROCESSOR_H


class MyServiceAuthProcessor : public grpc::AuthMetadataProcessor {
public:

    MyServiceAuthProcessor();

    grpc::Status
    Process(const InputMetadata &auth_metadata, grpc::AuthContext *context, OutputMetadata *consumed_auth_metadata,
            OutputMetadata *response_metadata) override;


private:
    grpc::Status ProcessRegister(const InputMetadata &auth_metadata);

    grpc::Status ProcessLogin(const InputMetadata &auth_metadata, grpc::AuthContext *context);

    grpc::Status ProcessLogout(std::basic_string<char> basicString);

    grpc::Status ProcessShareFile(const InputMetadata &auth_metadata, grpc::AuthContext *context);

    void LoadUserMap();

    void UpdateUserMap(google::protobuf::MapPair<std::basic_string<char>, protobuf::ProfileInfo> &pair);

    struct Const {
        static const std::string &TokenKeyName() {
            static std::string _("token");
            return _;
        }

        static const std::string &PeerIdentityPropertyName() {
            static std::string _("email");
            return _;
        }
    };

    //key=email, value=protobuf:User da salvare su db
    protobuf::UserMap userMap;

    //key=identifier, value=email da tenere a runtime
    std::map<std::string, std::string> tokenMap;

    int idCounter;

};


#endif //SERVER_MYSERVICEAUTHPROCESSOR_H
