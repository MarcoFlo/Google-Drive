#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetSymbolsCallData.h"
#include "GetFileContentCallData.h"
#include "InsertFileCallData.h"
#include "DeleteFileCallData.h"
#include "ShareFileCallData.h"
#include "InsertSymbolsCallData.h"
#include "RegisterCallData.h"
#include "LoginCallData.h"
#include "LogoutCallData.h"
#include "GetFilesCallData.h"
#include "MyServiceAuthProcessor.h"
#include "CharacterServiceImpl.h"


void read(const std::string &filename, std::string &data) {
    std::ifstream file(filename.c_str());
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

    LoadFileClienMap();

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

// This can be run in multiple threads if needed.
void CharacterServiceImpl::HandleRpcs() {
    new DeleteFileCallData(&service_, cq_.get());
    new GetFilesCallData(&service_, cq_.get());
    new GetSymbolsCallData(&service_, cq_.get());
    new InsertSymbolsCallData(&service_, cq_.get());
    new InsertFileCallData(&service_, cq_.get());
    new LoginCallData(&service_, cq_.get());
    new LogoutCallData(&service_, cq_.get());
    new ShareFileCallData(&service_, cq_.get());
    new RegisterCallData(&service_, cq_.get());


    void *tag;  // uniquely identifies a request.
    bool ok;
    while (true) {
        GPR_ASSERT(cq_->Next(&tag, &ok));
        CallData *callData = static_cast<CallData *>(tag);

        if (callData->getClass() == "GetSymbolsCallData")
            static_cast<GetSymbolsCallData *> (tag)->HandleGet(subscribedClientMap, ok);
        else if (callData->getClass() == "InsertSymbolsCallData")
            static_cast<InsertSymbolsCallData *> (tag)->HandleInsert(subscribedClientMap, fileClientMap, ok);
        else if (callData->getClass() == "InsertFileCallData")
            static_cast<InsertFileCallData *> (tag)->HandleInsert(fileClientMap, ok);
        else if (callData->getClass() == "DeleteFileCallData")
            static_cast<DeleteFileCallData *> (tag)->HandleDelete(fileClientMap, ok);
        else if (callData->getClass() == "ShareFileCallData")
            static_cast<ShareFileCallData *> (tag)->HandleShare(fileClientMap, ok);
        else if (callData->getClass() == "GetFileContentCallData")
            static_cast<GetFileContentCallData *> (tag)->HandleGet(fileClientMap, ok);
        else if (callData->getClass() == "GetFilesCallData")
            static_cast<GetFilesCallData *> (tag)->HandleGet(fileClientMap, ok);
        else
            callData->Proceed(ok);


    }
}

void CharacterServiceImpl::LoadFileClienMap() {
    std::ifstream ifs("fileClientMap.data", std::ios_base::in | std::ios_base::binary);
    if (ifs.peek() != EOF) {
        if (!fileClientMap.ParseFromIstream(&ifs)) {
            std::cerr << "La lettura di userMap.data è fallita" << std::endl;
            exit(1);
        }
        std::cout << "Sono stati caricati i seguenti dati di accesso ai file: " << std::endl;
        std::for_each(fileClientMap.fileclientmap().begin(), fileClientMap.fileclientmap().end(), [](auto &pair) {
            std::cout << pair.first << std::endl;
            //todo
        });
        std::cout << std::endl;
    }
}






