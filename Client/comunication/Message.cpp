//
// Created by flori on 11/10/2019.
//

#include <messageP.pb.h>
#include "Message.h"

Message::Message(Symbol &symbol, int idEditor, bool isEraseBool) : symbol(symbol), idEditor(idEditor), isEraseBool(isEraseBool) {}

protobuf::Message Message::makeProtobufMessage()
{
        protobuf::Message msg;
        msg.set_ideditor(idEditor);
        msg.mutable_symbol()->CopyFrom(symbol.makeProtobufSymbol());
        msg.set_iserasebool(isEraseBool);
        return msg;
}

int Message::getIdEditor() const {
    return idEditor;
}

const Symbol &Message::getSymbol() const {
    return symbol;
}

bool Message::isErase() const {
    return isEraseBool;
}
