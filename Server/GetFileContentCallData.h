#ifndef SERVER_GETFILECONTENTCALLDATA_H
#define SERVER_GETFILECONTENTCALLDATA_H

#include "AbstractFileCallData.h"


class GetFileContentCallData final : public AbstractFileCallData {
public:
    GetFileContentCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq);

    void HandleFileCall(protobuf::FileClientMap &fileClientMap, bool ok = true);

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
// What we send back to the client (as a protobuf::Chunk).
    protobuf::SymbolVector symbolVector;

    int index = 0;
    int chunkSize = 0;

// The means to get back to the client.
    grpc::ServerAsyncWriter<protobuf::Chunk> responder_;

};


#endif //SERVER_GETFILECONTENTCALLDATA_H
