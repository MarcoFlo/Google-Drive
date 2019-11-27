#ifndef SERVER_GETFILESCALLDATA_H
#define SERVER_GETFILESCALLDATA_H

#include "CallData.h"

class GetFilesCallData final: public CallData {
public:
    GetFilesCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq);
    void Proceed(bool ok = true);

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
    protobuf::FilesInfoList reply_;

// The means to get back to the client.
    grpc::ServerAsyncResponseWriter<protobuf::FilesInfoList> responder_;

};


#endif //SERVER_GETFILESCALLDATA_H
