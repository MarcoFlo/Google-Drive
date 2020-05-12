#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H

#include "Symbol.h"
#include "AsyncClientGetSymbols.h"


class CharacterClient {
public:
    explicit CharacterClient();

    virtual ~CharacterClient();

    void AsyncCompleteRpc(CharacterClient *pClient);

    std::string Register(protobuf::User &user);

    std::string Login(protobuf::User &user);

    std::string Logout();

    std::string InsertFile(const protobuf::FileName &fileName);

    std::string RemoveFile(const protobuf::FileInfo &fileInfo);

    std::string GetFiles();

    std::string ShareFile(const std::string &fileIdentifier, const std::string &usernameShare);

    std::string GetFileContent(const protobuf::FileInfo &fileInfo);

    void GetSymbols(const protobuf::FileInfo &fileInfo);

    std::string InsertSymbols(Symbol &symbol, bool isErase);

    protobuf::FilesInfoList getFileInfoList();

    protobuf::SymbolVector getSymbolVector();

    std::string getUsername();

    std::list<int> searchFileInfo(const std::string&);

    protobuf::FileInfo getFileInfo(const std::string&);

    void closeFile();

private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

    grpc::CompletionQueue cq_;

    std::string token_;
    std::string currentFileIdentifier_;
    protobuf::FilesInfoList lastFileInfoList_;
    std::string username_;

    //current opened file
    protobuf::SymbolVector symbolVector_;
    std::thread thread_;

};

#endif //CLIENT_CHARACTERCLIENT_H
