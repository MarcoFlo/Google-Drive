//
// Created by flori on 11/10/2019.
//

#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H


#include "Symbol.h"

class Message {
    std::string file_identifier_;
    Symbol symbol_;
    bool isEraseBool_;
public:
    Message(std::string &file_identifier, Symbol &symbol, bool isErase);
    protobuf::Message makeProtobufMessage();

    const Symbol &getSymbol() const;

    bool isErase() const;

};


#endif //CLIENT_MESSAGE_H
