#ifndef SERVER_ABSTRACTSUBSCRIBEDCALLDATA_H
#define SERVER_ABSTRACTSUBSCRIBEDCALLDATA_H

#include <fstream>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "shaeredImport.h"
#include "CallData.h"

class AbstractSubscribedCallData : public CallData {
public:

    void Proceed(bool ok) override {}

    virtual void
    HandleSubscribedCall(std::map<std::string, std::vector<AbstractSubscribedCallData *>> &subscribedClientMap,
                         bool ok) = 0;

    std::string getClass() override {
        return "SubscribedCallData";
    }

};

#endif //SERVER_ABSTRACTSUBSCRIBEDCALLDATA_H
