//
// Created by flori on 11/10/2019.
//
#include "SharedEditor.h"
#include "definitions.h"
#include <iostream>
#include <algorithm>
#include <vector>

SharedEditor::SharedEditor(NetworkServer &server) : _server(server), _counter(0) {
    _siteId = server.connect(this);
}

SharedEditor::~SharedEditor() {
    _server.disconnect(this);
}

/**
 * Questo metodo costruisce un symbol che incapsula il carattere value, gli associa un identificativo
 * univoco ed una posizione frazionaria tale da risultare compresa tra le posizioni frazionarie degli
 * elementi di _symbols all’indice index-1 e index (se esistenti). A seguito dell’inserimento,
 * nell’indice index verrà a trovarsi il nuovo simbolo, e tutti quelli successivi scaleranno di una unità.
 * Le loro posizioni frazionarie, tuttavia, non verranno modificate e si manterrà sempre l’invariante
 * tale per cui tutti gli elementi adiacenti nel vettore _symbols hanno posizione frazionaria
 * strettamente minore l’una dell’altra. A seguito dell’inserimento, prepara un oggetto di tipo
 * Message, all’interno del quale descrive l’azione compiuta: inserimento da parte di _siteId del
 * carattere value, con identificativo univoco e posizione frazionaria corrispondente. Tale
 * messaggio verrà inviato all’oggetto _server che provvederà ad accodarlo, in attesa di inviarlo a
 * tutte le altre istanze della classe SharedEditor.
 *
 * @param index
 * @param value
 */
void SharedEditor::localInsert(int index, char value) {
    std::vector<int> posPre = {0};
    std::vector<int> posPost = {2};

    if (_symbols.size() < index)
        //se cerco di inserire a un indice oltre la fine, inserisco alla fine
        index = _symbols.size();

    if (_symbols.size() == index) {
        if (index != 0) {
            posPre = _symbols.at(index - 1).getPos();
            posPost = {(posPre.at(posPre.size() - 1) + 2)};
        }
    } else {
        if (index != 0)
            posPre = _symbols.at(index - 1).getPos();

        posPost = _symbols.at(index).getPos();
    }

#if debug == 1
    //stampa il range in cui deve essere contenuto l'indice frazionario di @value, ad es 0<c<2
    for (int i = 0; i < posPre.size(); i++) {
        std::cout << posPre.at(i);
        if (i == 0 && i != posPre.size() - 1)
            std::cout << ",";
    }
    std::cout << "<" << value << "<";
    for (int i = 0; i < posPost.size(); i++) {
        std::cout << posPost.at(i);
        if (i == 0 && i != posPost.size() - 1)
            std::cout << ",";
    }
#endif

    int newVal;
    bool isPreBigger = posPre.size() >= posPost.size();
    std::vector<int> posNew = isPreBigger ? posPre : posPost;
    unsigned int maxI = posNew.size() - 1;

    if (posPre.size() == posPost.size()) {
        newVal = (posPre.at(maxI) + posPost.at(maxI)) / 2;
        if (newVal != posPre.at(maxI)) {
            //stiamo inserendo tra 1 e 3
            posNew.at(maxI) = newVal;
        } else {
            //stiamo inserendo tra 3,4 e 3,5
            posNew.push_back(5);
        }
    } else {
        if (posNew.at(maxI) == 1) {
            //stiamo inserendo tra 4 e 4,1
            posNew.at(maxI) = 0;
            posNew.push_back(5);
        } else if (posNew.at(maxI) == 9) {
            //stiamo inserendo tra 3,9 e 4
            posNew.push_back(5);
        } else {
            //stiamo inserendo tra 3,477777 e 3,5
            newVal = isPreBigger ? (posNew.at(maxI) + 10) / 2 : posNew.at(maxI) / 2;
            posNew.at(maxI) = newVal;
        }
    }

#if debug == 1
    // stampa l'indice frazionario scelto
    std::cout << "  -->  ";
    for (int j = 0; j < posNew.size(); ++j) {
        std::cout << posNew[j];
        if (j == 0 && j != posNew.size() - 1)
            std::cout << ",";
    }
    std::cout << std::endl;
#endif

    int uniqueId = std::stoi(std::to_string(_siteId) + std::to_string(_counter++));
    Symbol symbol(value, uniqueId, posNew);
    _symbols.insert(_symbols.begin() + index, 1, symbol);
    Message msg(symbol, _siteId, false);
    _server.send(msg);

}

/**
 * Questo metodo elimina dal vettore _symbols l’elemento all’indice indicato, prepara un oggetto
 * di tipo Message in cui descrive l’azione compiuta e lo affida all’oggetto _server affinché lo
 * consegni agli altri SharedEditor.
 *
 * @param index
 */
void SharedEditor::localErase(int index) {
    if (_symbols.size() == 0)
        return;

    if (index >= _symbols.size())
        index = _symbols.size() - 1;

    Message msg(_symbols.at(index), _siteId, true);
    _symbols.erase(_symbols.begin() + index);
    _server.send(msg);

}

/**
 * Questo metodo esamina il contenuto del messaggio m e provvede a eseguirne le relative azioni
 * se si tratta di un messaggio di inserimento provvede ad identificare, a partire dalla posizione
 * frazionaria contenuta nel messaggio, l’indice nel vettore _symbols in cui inserire il nuovo simbolo;
 * se, invece, si tratta di una cancellazione, cerca nel vettore _symbols se è presente alla posizione
 * frazionaria contenuta nel messaggio un simbolo con l’identificatore univoco corrispondente e, nel
 * caso, lo elimina.
 *
 * @param m
 */
void SharedEditor::process(const Message &m) {
    const Symbol sNew = m.getSymbol();
    if (m.isErase()) {
        _symbols.erase(std::find(_symbols.begin(), _symbols.end(), sNew));
    } else {
        // nel progetto finale considerare se è possibile che entrambi inseriscano allo stesso tempo un carattere diverso nella stessa posizione frazionaria
        _symbols.push_back(sNew);
        std::sort(_symbols.begin(), _symbols.end());
    }

}

int SharedEditor::getSiteId() {
    return _siteId;
}

/**
 * ricostruisce la sequenza dei caratteri contenuta nell’editor
 *
 * @return
 */
std::string SharedEditor::to_string() {
    std::string res;
    std::for_each(_symbols.begin(), _symbols.end(), [&res](auto &symb) { res += symb.getCharacter(); });
    return res;
}






