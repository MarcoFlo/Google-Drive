#ifndef SERVER_ABSTRACTFILECALLDATA_H
#define SERVER_ABSTRACTFILECALLDATA_H

#include <fstream>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "shaeredImport.h"
#include "CallData.h"

class AbstractFileCallData : public CallData {
public:
    void Proceed(bool ok) override {}

    virtual void HandleFileCall(protobuf::FileClientMap &fileClientMap, bool ok) = 0;

    std::string getClass() override {
        return "FileCallData";
    }

};

#endif //SERVER_ABSTRACTFILECALLDATA_H
