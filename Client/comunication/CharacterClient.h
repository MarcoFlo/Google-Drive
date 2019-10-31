//
// Created by flori on 23/10/2019.
//

#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H


class CharacterClient {
public:
    CharacterClient(std::shared_ptr<grpc::Channel> channel);
    int Connect(protobuf::User user);

    void GetSymbols();


private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

};

#endif //CLIENT_CHARACTERCLIENT_H
