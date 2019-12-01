//
// Created by flori on 23/10/2019.
//

#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H
#include "AsyncClientGetSymbols.h"


class CharacterClient {
public:
    explicit CharacterClient(std::shared_ptr<grpc::Channel> channel);

    void AsyncCompleteRpc();

    void Register(protobuf::User user);

    std::string Login(protobuf::User user);

    void Logout(std::string token);

    AsyncClientGetSymbols *GetSymbols(const std::string &fileUniqueId, const std::string &token);


private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

    grpc::CompletionQueue cq_;


};

#endif //CLIENT_CHARACTERCLIENT_H
