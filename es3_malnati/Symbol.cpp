//
// Created by flori on 11/10/2019.
//

#include "Symbol.h"

Symbol::Symbol(char character, int uniqueId, std::vector<int>& pos) : character(character), uniqueId(uniqueId), pos(pos) {}

bool Symbol::operator==(const Symbol &symbol) {
    return this->getUniqueId()==symbol.getUniqueId();
}

bool Symbol::operator<(const Symbol &symbol) const {
    return this->getPos() < symbol.getPos();
}

char Symbol::getCharacter() const {
    return character;
}

int Symbol::getUniqueId() const {
    return uniqueId;
}

const std::vector<int> &Symbol::getPos() const {
    return pos;
}


