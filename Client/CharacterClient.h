//
// Created by flori on 23/10/2019.
//

#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H

#include <grpcpp/channel.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "messageP.grpc.pb.h"


class CharacterClient {
public:
    CharacterClient(std::shared_ptr<grpc::Channel> channel, const std::string &db);
    void ExchangeSymbol();

private:
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

};

#endif //CLIENT_CHARACTERCLIENT_H
