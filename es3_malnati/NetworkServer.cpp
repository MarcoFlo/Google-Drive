//
// Created by flori on 11/10/2019.
//
#include <algorithm>
#include "NetworkServer.h"
#include "SharedEditor.h"

NetworkServer::NetworkServer() : idEditor(0) {

}

/**
 *  Registra, nel proprio vettore di puntatori a SharedEditor, il puntatore ricevuto e restituisce un
 *  identificatore univoco mediante il quale l’editor potrà distinguersi dalle altre istanze della stessa classe
 *
 * @param sharedEditor
 * @return
 */
int NetworkServer::connect(SharedEditor *sharedEditor) {
    editors.push_back(sharedEditor);
    return idEditor++;
}

/**
 * Elimina il puntatore dal vettore degli editor collegati.
 *
 * @param sharedEditor
 */
void NetworkServer::disconnect(SharedEditor *sharedEditor) {
    editors.erase(std::find(editors.begin(), editors.end(), sharedEditor));
}

/**
 * Aggiunge il messaggio m alla coda dei messaggi da distribuire, senza ancora mandarlo.
 */
void NetworkServer::send(const Message &m) {
    messages.push(m);
}

/**
 * Distribuisce tutti i messaggi accodati a tutti gli editor attualmente collegati, fatta eccezione, però per l’originatore del messaggio stesso.
 */
void NetworkServer::dispatchMessages() {
    while (!messages.empty()) {
        Message m = messages.front();
        std::for_each(editors.begin(), editors.end(), [&m](auto editor) {
            if (editor->getSiteId() != m.getIdEditor())
                editor->process(m);
        });
        messages.pop();
    }

}
