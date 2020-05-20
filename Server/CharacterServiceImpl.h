#ifndef SERVER_CHARACTERSERVICEIMPL_H
#define SERVER_CHARACTERSERVICEIMPL_H

#include "AbstractSubscribedCallData.h"

class CharacterServiceImpl final : public protobuf::CharacterService::Service {
public:
    ~CharacterServiceImpl();

    void Run();

private:
    void HandleRpcs();

    void LoadFileClienMap();

    std::unique_ptr<grpc::ServerCompletionQueue> cq_;
    protobuf::CharacterService::AsyncService service_;
    std::unique_ptr<grpc::Server> server_;
    std::map<std::string, std::vector<AbstractSubscribedCallData *>> subscribedClientMap; //key -> uniqueFileId, value-> vector of client with a pending GetSymbols
    protobuf::FileClientMap fileClientMap; // key -> email, value -> FilesInfoList

};


#endif //SERVER_CHARACTERSERVICEIMPL_H
