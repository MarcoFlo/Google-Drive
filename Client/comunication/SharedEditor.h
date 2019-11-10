//
// Created by flori on 11/10/2019.
//

#ifndef CLIENT_SHAREDEDITOR_H
#define CLIENT_SHAREDEDITOR_H

#include "Message.h"


class SharedEditor {
    CharacterClient &_client;
    std::string _siteId;                               //indice univoco per singolo editor
    std::vector<Symbol> _symbols;
    int _counter;                               //indice che insieme al siteId crea un indice univoco a livello globale per ogni simbolo

public:
    explicit SharedEditor(CharacterClient &client, protobuf::UserL userL);

    virtual ~SharedEditor();

    void localInsert(unsigned int index, char value);

    void localErase(unsigned int index);

    void process(const Message &m);

    std::string getSiteId();

    std::string to_string();
};


#endif //CLIENT_SHAREDEDITOR_H
