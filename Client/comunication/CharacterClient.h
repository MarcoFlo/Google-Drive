//
// Created by flori on 23/10/2019.
//

#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H


class CharacterClient {
public:
    CharacterClient(std::shared_ptr<grpc::Channel> channel);
    void GetSymbols(const std::string &user);
    void AsyncCompleteRpc();

private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

    // The producer-consumer queue we use to communicate asynchronously with the
    // gRPC runtime.
    grpc::CompletionQueue cq_;

    struct AsyncClientCall {
        // Container for the data we expect from the server.
        protobuf::Message reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // Storage for the status of the RPC upon completion.
        grpc::Status status;


        std::unique_ptr<grpc::ClientAsyncResponseReader<protobuf::Message>> response_reader;
    };

};

#endif //CLIENT_CHARACTERCLIENT_H
