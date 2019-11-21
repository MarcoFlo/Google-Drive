#ifndef CLIENT_ASYNCCLIENTGETSYMBOLS_H
#define CLIENT_ASYNCCLIENTGETSYMBOLS_H

#include "AsyncClientCall.h"

class AsyncClientGetSymbols final : public AsyncClientCall {
public:

    void HandleAsync(bool ok = true) override;

    void CloseRpc() override;

    AsyncClientGetSymbols(const protobuf::FileName &request, const std::string &token, grpc::CompletionQueue &cq_,
                          std::unique_ptr<protobuf::CharacterService::Stub> &stub_);


    std::unique_ptr<grpc::ClientAsyncReader<protobuf::Message>> responder;

    // Container for the data we expect from the server.
    protobuf::Message reply_;
    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
//    grpc::ClientContext context;

    // Storage for the status of the RPC upon completion.
//    grpc::Status status;


};


#endif //CLIENT_ASYNCCLIENTGETSYMBOLS_H
