#ifndef CLIENT_ASYNCCLIENTCALL_H
#define CLIENT_ASYNCCLIENTCALL_H


class AsyncClientCall {
public:
    virtual void HandleAsync(bool = true) = 0;

    virtual void CloseRpc() = 0;

    enum CallStatus {
        CREATE, PROCESS, FINISH, DESTROY
    };

    explicit AsyncClientCall() : callStatus(CREATE) {}

    grpc::ClientContext context;
    grpc::Status status;
    CallStatus callStatus;
};


#endif //CLIENT_ASYNCCLIENTCALL_H
