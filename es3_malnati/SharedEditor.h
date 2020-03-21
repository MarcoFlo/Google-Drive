//
// Created by flori on 11/10/2019.
//

#ifndef ES3_SHAREDEDITOR_H
#define ES3_SHAREDEDITOR_H

//#include <vector>
//#include <string>
//#include "NetworkServer.h"
//#include "Symbol.h"
//
//class SharedEditor {
//    NetworkServer& _server;
//    int _siteId;
//    std::vector<Symbol> _symbols;
//    int _counter;
//
//public:
//    void localInsert(int index, char value);
//
//    void localErase(int index);
//
//    void process(const Message &m);
//
//    std::string to_string();
//
//};

#include <vector>
#include <iostream>
#include <string>
#include "NetworkServer.h"
#include "Symbol.h"
#include "Message.h"


class SharedEditor {
    NetworkServer &_server;
    int _siteId;                               //indice univoco per singolo editor
    std::vector<Symbol> _symbols;
    int _counter;                               //indice che insieme al siteId crea un indice univoco a livello globale per ogni simbolo

public:
    explicit SharedEditor(NetworkServer &server);

    virtual ~SharedEditor();

    void localInsert(int index, char value);

    void localErase(int index);

    void process(const Message &m);

    int getSiteId();

    std::string to_string();
};


#endif //ES3_SHAREDEDITOR_H
