#include <filesystem>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "CharacterServiceImpl.h"

int main(int argc, char **argv) {
    std::filesystem::create_directories("db/fileContainer");
    CharacterServiceImpl server;
    server.Run();

    return 0;
}