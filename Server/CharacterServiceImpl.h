//
// Created by flori on 23/10/2019.
//

#ifndef SERVER_CHARACTERSERVICEIMPL_H
#define SERVER_CHARACTERSERVICEIMPL_H


class CharacterServiceImpl final : public protobuf::CharacterService::Service {
public:
    grpc::Status Connect(grpc::ServerContext *context, const protobuf::User *user, protobuf::Identifier *identifier) override;

    ~CharacterServiceImpl();

    void Run();

private:
    void HandleRpcs();

    std::unique_ptr<grpc::ServerCompletionQueue> cq_;

    protobuf::CharacterService::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
};


#endif //SERVER_CHARACTERSERVICEIMPL_H
