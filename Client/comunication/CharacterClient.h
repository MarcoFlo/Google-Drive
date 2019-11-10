//
// Created by flori on 23/10/2019.
//

#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H


class CharacterClient {
public:
    explicit CharacterClient(std::shared_ptr<grpc::Channel> channel);
    void Register(protobuf::UserR userR);
    std::string Login(protobuf::UserL userL);
    void Logout(std::string token);

    void GetSymbols(std::string token);



private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

};

#endif //CLIENT_CHARACTERCLIENT_H
