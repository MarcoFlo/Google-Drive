//
// Created by flori on 05/11/2019.
//

#ifndef SERVER_MYSERVICEAUTHPROCESSOR_H
#define SERVER_MYSERVICEAUTHPROCESSOR_H


class MyServiceAuthProcessor : public grpc::AuthMetadataProcessor{
public:

    grpc::Status Process(const InputMetadata& auth_metadata, grpc::AuthContext* context, OutputMetadata* consumed_auth_metadata, OutputMetadata* response_metadata) override;


    std::map<std::string, std::string> tokens = {
            {"abcd","abcd"},
            {"abcde","abcde"}
    };
};


#endif //SERVER_MYSERVICEAUTHPROCESSOR_H
