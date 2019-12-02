#ifndef SERVER_GETFILECONTENTCALLDATA_H
#define SERVER_GETFILECONTENTCALLDATA_H
#include "CallData.h"


class GetFileContentCallData final : public CallData {
public:
    GetFileContentCallData(protobuf::CharacterService::AsyncService *service, grpc::ServerCompletionQueue *cq);

    void Proceed(bool ok = true);



    std::string getClass();

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
    protobuf::Chunk reply_;

// The means to get back to the client.
    grpc::ServerAsyncWriter<protobuf::Chunk> responder_;

};


#endif //SERVER_GETFILECONTENTCALLDATA_H
