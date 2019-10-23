#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "messageP.grpc.pb.h"
#include "CharacterServiceImpl.h"


void RunServer(const std::string& db_path) {
    std::string server_address("0.0.0.0:50051");
    CharacterServiceImpl service(db_path);

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}


int main(int argc, char** argv) {
    std::string db = "path/to/route_guide_db.json";
    RunServer(db);

    return 0;
}