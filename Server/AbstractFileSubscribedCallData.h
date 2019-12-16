#ifndef SERVER_ABSTRACTFILESUBSCRIBEDCALLDATA_H
#define SERVER_ABSTRACTFILESUBSCRIBEDCALLDATA_H

#include <fstream>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "shaeredImport.h"
#include "CallData.h"
#include "AbstractSubscribedCallData.h"

class AbstractFileSubscribedCallData : public CallData {
public:
    void Proceed(bool ok) override {}

    virtual void HandleFileSubscribedCall(protobuf::FileClientMap &fileClientMap,
                                          std::map<std::string, std::vector<AbstractSubscribedCallData *>> &subscribedClientMap,
                                          bool ok) = 0;

    std::string getClass() override {
        return "FileSubscribedCallData";
    }

};

#endif //SERVER_ABSTRACTFILESUBSCRIBEDCALLDATA_H
