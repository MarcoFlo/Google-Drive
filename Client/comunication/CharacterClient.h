//
// Created by flori on 23/10/2019.
//

#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H


class CharacterClient {
public:
    CharacterClient(std::shared_ptr<grpc::Channel> channel);
    std::string GetSymbols(const std::string &user);

private:
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

};

#endif //CLIENT_CHARACTERCLIENT_H
