#ifndef SERVER_CALLDATA_H
#define SERVER_CALLDATA_H

#include "shaeredImport.h"

class CallData {
public:
    explicit CallData() : status_(CREATE) {}

    virtual void Proceed(bool ok) = 0;

    virtual std::string getClass() {
        return "";
    }

    virtual CallStatus getCallStatus() {
        return status_;
    }

    CallStatus status_;  // The current serving state.

};


#endif //SERVER_CALLDATA_H
