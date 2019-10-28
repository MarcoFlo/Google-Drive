#include <iostream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "CharacterServiceImpl.h"


int main(int argc, char** argv) {
    CharacterServiceImpl server;
    server.Run();

    return 0;
}