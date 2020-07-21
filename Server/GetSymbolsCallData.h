#ifndef SERVER_GETSYMBOLSCALLDATA_H
#define SERVER_GETSYMBOLSCALLDATA_H

#include "AbstractSubscribedCallData.h"
#include "InsertSymbolsCallData.h"

class GetSymbolsCallData final: public AbstractSubscribedCallData {
public:
    GetSymbolsCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq);

    void HandleSubscribedCall(std::map<std::string, std::vector<AbstractSubscribedCallData *>> &subscribedClientMap,
                              bool ok) override;

    void HandleSymbol(const protobuf::Message &message);

    friend class InsertSymbolsCallData;

private:
    // The means of communication with the gRPC runtime for an asynchronous
// server.
    protobuf::CharacterService::AsyncService *service_;
// The producer-consumer queue where for asynchronous server notifications.
    grpc::ServerCompletionQueue *cq_;
// Context for the rpc, allowing to tweak aspects of it such as the use
// of compression, authentication, as well as to send metadata back to the
// client.
    grpc::ServerContext ctx_;

// What we get from the client.
    protobuf::FileInfo request_;
// What we send back to the client.
    protobuf::Message reply_;
    std::string mailPrincipal;

// The means to get back to the client.
    grpc::ServerAsyncWriter<protobuf::Message> responder_;

};


#endif //SERVER_GETSYMBOLSCALLDATA_H
