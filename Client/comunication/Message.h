//
// Created by flori on 11/10/2019.
//

#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H


#include "Symbol.h"

class Message {
    Symbol symbol;
    bool isEraseBool;
public:
    Message(Symbol &symbol, bool isErase);
    protobuf::Message makeProtobufMessage();

    const Symbol &getSymbol() const;

    bool isErase() const;

};


#endif //CLIENT_MESSAGE_H
