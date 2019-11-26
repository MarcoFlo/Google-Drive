#ifndef SERVER_CHARACTERSERVICEIMPL_H
#define SERVER_CHARACTERSERVICEIMPL_H

#include "GetSymbolsCallData.h"

class CharacterServiceImpl final : public protobuf::CharacterService::Service {
public:
    ~CharacterServiceImpl();

    void Run();

private:
    void HandleRpcs();

    std::unique_ptr<grpc::ServerCompletionQueue> cq_;
    protobuf::CharacterService::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
    std::map<std::string, std::vector<GetSymbolsCallData *>> subscribedClientMap;
};


#endif //SERVER_CHARACTERSERVICEIMPL_H
