//
// Created by flori on 11/10/2019.
//

#ifndef CLIENT_MESSAGE_H
#define CLIENT_MESSAGE_H


#include "Symbol.h"

class Message {
    int idEditor;
    Symbol symbol;
    bool isEraseBool;
public:
    Message(Symbol &symbol, int idEditor, bool isErase);
    protobuf::Message makeProtobufMessage();

    int getIdEditor() const;

    const Symbol &getSymbol() const;

    bool isErase() const;

};


#endif //CLIENT_MESSAGE_H
