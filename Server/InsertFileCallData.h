#ifndef SERVER_INSERTFILECALLDATA_H
#define SERVER_INSERTFILECALLDATA_H

#include "AbstractFileCallData.h"


class InsertFileCallData final : public AbstractFileCallData {
public:
    InsertFileCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq);

    void HandleFileCall(protobuf::FileClientMap &fileClientMap, bool ok) override;

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
    protobuf::FileName request_;
// What we send back to the client.
    protobuf::FileInfo reply_;

// The means to get back to the client.
    grpc::ServerAsyncResponseWriter<protobuf::FileInfo> responder_;

};

#endif //SERVER_INSERTFILECALLDATA_H
