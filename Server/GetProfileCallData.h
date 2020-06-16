#ifndef SERVER_GETPROFILECALLDATA_H
#define SERVER_GETPROFILECALLDATA_H

#include "CallData.h"

class GetProfileCallData final : public CallData {
public:
    GetProfileCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq);

    void Proceed(bool ok = true) override;

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
    protobuf::Empty request_;
// What we send back to the client.
    protobuf::ProfileInfo reply_;

// The means to get back to the client.
    grpc::ServerAsyncResponseWriter <protobuf::ProfileInfo> responder_;
};

#endif //SERVER_GETPROFILECALLDATA_H
