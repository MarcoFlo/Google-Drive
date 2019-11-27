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
    std::map<std::string, std::vector<GetSymbolsCallData *>> subscribedClientMap; //key -> uniqueFileId, value-> vector of client with a pending GetSymbols
    std::map<std::string, std::vector<protobuf::FileInfo>> fileClientMap; // key -> username, value -> vector of fileInfo (size is empty)


};


#endif //SERVER_CHARACTERSERVICEIMPL_H
