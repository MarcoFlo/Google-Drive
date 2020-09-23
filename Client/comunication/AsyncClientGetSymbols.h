#ifndef CLIENT_ASYNCCLIENTGETSYMBOLS_H
#define CLIENT_ASYNCCLIENTGETSYMBOLS_H

class AsyncClientGetSymbols {
public:

    void HandleAsync(bool ok);

    void CloseRpc();

    AsyncClientGetSymbols(const protobuf::FileInfo &request, const std::string &token, grpc::CompletionQueue &cq_,
                          std::unique_ptr<protobuf::CharacterService::Stub> &stub_);


    std::unique_ptr<grpc::ClientAsyncReader<protobuf::Message>> responder;

    // Container for the data we expect from the server.
    protobuf::Message reply_;

    protobuf::FileInfo request_;

    protobuf::Symbol GetSymbol();

    enum CallStatus {
        CREATE, READ, READ_CALLED, FINISH, DESTROY
    };

    grpc::ClientContext context;
    grpc::Status status;
    CallStatus callStatus;
    bool flag = false;
private:
    protobuf::Symbol symbol;
};


#endif //CLIENT_ASYNCCLIENTGETSYMBOLS_H
