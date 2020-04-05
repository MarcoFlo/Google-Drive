//
// Created by flori on 11/10/2019.
//

#ifndef ES3_NETWORKSERVER_H
#define ES3_NETWORKSERVER_H


#include <queue>
#include "Message.h"

class SharedEditor;

class NetworkServer {

private:
    std::vector<SharedEditor *> editors;
    std::queue<Message> messages;
    int idEditor;

public:
    NetworkServer();

    int connect(SharedEditor *sharedEditor);

    void disconnect(SharedEditor *sharedEditor);

    void send(const Message &m);

    void dispatchMessages();
};


#endif //ES3_NETWORKSERVER_H
