#ifndef SERVER_CALLDATA_H
#define SERVER_CALLDATA_H

#include <fstream>
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

    void UpdateFileClientMap(protobuf::FileClientMap &fileClientMap) {
        std::ofstream ofs("fileClientMap.data", std::ios_base::out | std::ios_base::binary);
        if (!fileClientMap.SerializeToOstream(&ofs)) {
            std::cerr << "La scrittura di fileClientMap.data è fallita";
            exit(1);
        }
    }

    CallStatus status_;  // The current serving state.

};


#endif //SERVER_CALLDATA_H
