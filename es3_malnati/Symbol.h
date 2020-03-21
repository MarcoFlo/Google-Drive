//
// Created by flori on 11/10/2019.
//

#ifndef ES3_SYMBOL_H
#define ES3_SYMBOL_H

#include <vector>
#include <string>

class Symbol {
    char character;
    int uniqueId;
    std::vector<int> pos;
public:
    Symbol(char character, int uniqueId, std::vector<int> &pos);

    bool operator==(const Symbol &symbol);

    bool operator<(const Symbol &symbol) const;


    char getCharacter() const;

    int getUniqueId() const;

    const std::vector<int> &getPos() const;
};


#endif //ES3_SYMBOL_H
