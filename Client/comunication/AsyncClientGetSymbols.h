#ifndef CLIENT_ASYNCCLIENTGETSYMBOLS_H
#define CLIENT_ASYNCCLIENTGETSYMBOLS_H

#include "AsyncClientCall.h"

class AsyncClientGetSymbols final : public AsyncClientCall {
public:

    void HandleAsync(bool ok) override;

    void CloseRpc() override;

    AsyncClientGetSymbols(const protobuf::FileInfo &request, const std::string &token, grpc::CompletionQueue &cq_,
                          std::unique_ptr<protobuf::CharacterService::Stub> &stub_);


    std::unique_ptr<grpc::ClientAsyncReaderWriter<protobuf::FileInfo,protobuf::Message>> responder;

    // Container for the data we expect from the server.
    protobuf::Message reply_;
    
    protobuf::FileInfo request_;
};


#endif //CLIENT_ASYNCCLIENTGETSYMBOLS_H
