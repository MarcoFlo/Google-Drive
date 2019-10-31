//
// Created by flori on 23/10/2019.
//

#ifndef SERVER_CHARACTERSERVICEIMPL_H
#define SERVER_CHARACTERSERVICEIMPL_H


class CharacterServiceImpl final : public protobuf::CharacterService::Service {
public:
    ~CharacterServiceImpl();

    void Run();

private:
    void HandleRpcs();

    std::unique_ptr<grpc::ServerCompletionQueue> cq_;
    protobuf::CharacterService::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
    int num_threads_ = 2;

};


#endif //SERVER_CHARACTERSERVICEIMPL_H
