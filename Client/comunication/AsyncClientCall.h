#ifndef CLIENT_ASYNCCLIENTCALL_H
#define CLIENT_ASYNCCLIENTCALL_H


class AsyncClientCall {
public:
    virtual void HandleAsync(bool ok) = 0;

    virtual void CloseRpc() = 0;

    enum CallStatus {
        CREATE, READ, READ_CALLED, FINISH, DESTROY
    };

    explicit AsyncClientCall() : callStatus(READ) {}

    grpc::ClientContext context;
    grpc::Status status;
    CallStatus callStatus;
};


#endif //CLIENT_ASYNCCLIENTCALL_H
