#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H

#include "AsyncClientGetSymbols.h"


class CharacterClient {
public:
    explicit CharacterClient();

    void AsyncCompleteRpc();

    void Register(protobuf::User &user);

    std::string Login(protobuf::User &user);

    std::string Logout();

    std::string ShareFile(std::string &fileIdentifier, std::string &usernameShare);

    std::string GetFileContent(protobuf::FileInfo fileInfo);

    AsyncClientGetSymbols *GetSymbols(const std::string &fileUniqueId);

private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

    grpc::CompletionQueue cq_;

    std::string token_;

};

#endif //CLIENT_CHARACTERCLIENT_H
