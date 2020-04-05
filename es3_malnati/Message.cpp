//
// Created by flori on 11/10/2019.
//

#include "Message.h"

Message::Message(Symbol &symbol, int idEditor, bool isEraseBool) : symbol(symbol), idEditor(idEditor), isEraseBool(isEraseBool) {}

int Message::getIdEditor() const {
    return idEditor;
}

const Symbol &Message::getSymbol() const {
    return symbol;
}

bool Message::isErase() const {
    return isEraseBool;
}
