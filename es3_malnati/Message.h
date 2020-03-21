//
// Created by flori on 11/10/2019.
//

#ifndef ES3_MESSAGE_H
#define ES3_MESSAGE_H


#include "Symbol.h"

class Message {
    int idEditor;
    Symbol symbol;
    bool isEraseBool;
public:
    Message(Symbol &symbol, int idEditor, bool isErase);

    int getIdEditor() const;

    const Symbol &getSymbol() const;

    bool isErase() const;

};


#endif //ES3_MESSAGE_H
