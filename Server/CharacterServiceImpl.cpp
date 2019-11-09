#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "CharacterServiceImpl.h"
#include "GetSymbolsCallData.h"
#include "RegisterCallData.h"
#include "LoginCallData.h"
#include "MyServiceAuthProcessor.h"

void read(const std::string &filename, std::string &data) {
    std::ifstream file(filename.c_str(), std::ios::in);

    if (file.is_open()) {
        std::stringstream ss;
        ss << file.rdbuf();

        file.close();

        data = ss.str();
    }
}

CharacterServiceImpl::~CharacterServiceImpl() {
    server_->Shutdown();
    // Always shutdown the completion queue after the server.
    cq_->Shutdown();
}

void CharacterServiceImpl::Run() {
    std::string server_address("0.0.0.0:50051");

    grpc::ServerBuilder builder;

    std::string serverKey;
    std::string serverCert;

    read("../../certs/server.cert", serverCert);
    read("../../certs/server.key", serverKey);


    grpc::SslServerCredentialsOptions::PemKeyCertPair keycert = {serverKey, serverCert};
//    keycert.private_key = key;
//    keycert.cert_chain = cert;

    grpc::SslServerCredentialsOptions sslOps;
    sslOps.pem_root_certs = "";
    sslOps.pem_key_cert_pairs.push_back(keycert);

    std::shared_ptr<grpc::ServerCredentials> creds = grpc::SslServerCredentials(sslOps);
    creds->SetAuthMetadataProcessor(std::make_shared<MyServiceAuthProcessor>());

    builder.AddListeningPort(server_address, creds);

    // Register "service_" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *asynchronous* service.
    builder.RegisterService(&service_);
    // Get hold of the completion queue used for the asynchronous communication
    // with the gRPC runtime.
    cq_ = builder.AddCompletionQueue();
    // Finally assemble the server.
    server_ = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;

    // Proceed to the server's main loop.
    HandleRpcs();
}


void CharacterServiceImpl::HandleRpcs() {
    new RegisterCallData(&service_, cq_.get());
    new LoginCallData(&service_, cq_.get());
    new GetSymbolsCallData(&service_, cq_.get());
    void *tag;  // uniquely identifies a request.
    bool ok;
    while (true) {
        GPR_ASSERT(cq_->Next(&tag, &ok));
        GPR_ASSERT(ok);
        static_cast<CallData *>(tag)->Proceed();
    }
}




