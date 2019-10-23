#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "messageP.grpc.pb.h"
#include "CharacterClient.h"


int main(int argc, char **argv) {
    std::string db = "path/to/route_guide_db.json";
    CharacterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()), db);

    client.ExchangeSymbol();
    return 0;
}