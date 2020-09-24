#ifndef CLIENT_CHARACTERCLIENT_H
#define CLIENT_CHARACTERCLIENT_H

#include "Symbol.h"
#include "AsyncClientGetSymbols.h"

class CharacterClient {
public:
    explicit CharacterClient();

    virtual ~CharacterClient();

    //void AsyncCompleteRpc(CharacterClient *pClient);

    std::string Register(protobuf::ProfileInfo &profileInfo);

    std::string GetProfile();

    std::string SetProfile(protobuf::ProfileInfo &profileInfo);

    std::string Login(const protobuf::User &user);

    std::string Logout();

    std::string InsertFile(const protobuf::FileName &fileName);

    std::string RemoveFile(const protobuf::FileInfo &fileInfo);

    std::string GetFiles();

    std::string ShareFile(const std::string &fileIdentifier, const std::string &emailShare);

    std::string ImportFile(const std::string &fileIdentifier);

    std::string GetFileContent(const protobuf::FileInfo &fileInfo);

    void GetSymbols(const protobuf::FileInfo &fileInfo);

    std::string InsertSymbols(Symbol &symbol, bool isErase);

    protobuf::FilesInfoList getFileInfoList();

    protobuf::SymbolVector getSymbolVector();

    protobuf::ProfileInfo getProfileInfoLogged();

    std::list<int> searchFileInfo(const std::string &);

    protobuf::FileInfo getFileInfo(const std::string &);

    void closeFile();

    grpc::CompletionQueue cq_;

    void setAsyncfun();

    bool getAsyncfun();

private:
    // Out of the passed in Channel comes the stub, stored here, our view of the
    // server's exposed services.
    std::unique_ptr<protobuf::CharacterService::Stub> stub_;

    protobuf::UserLogged userLogged_;
    std::string currentFileIdentifier_;
    protobuf::FilesInfoList lastFileInfoList_;
    std::string email_;
    std::string password_;

    std::unique_ptr<AsyncClientGetSymbols> asyncClientGetSymbols;

    //current opened file
    protobuf::SymbolVector symbolVector_;
    protobuf::Symbol asyncSymbol;
    bool asyncFun= false;
};

#endif //CLIENT_CHARACTERCLIENT_H
