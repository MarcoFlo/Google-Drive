#include <vector>
#include <string>
#include "messageP.grpc.pb.h"
#include "Symbol.h"

Symbol::Symbol(char character, int uniqueId, std::vector<int>& pos) : character(character), uniqueId(uniqueId), pos(pos) {}

protobuf::Symbol Symbol::makeProtobufSymbol() {
    protobuf::Symbol symbol;
    symbol.set_character(reinterpret_cast<const char *>(character));
    symbol.set_uniqueid(uniqueId);
    *symbol.mutable_pos() = {pos.begin(), pos.end()};
    return symbol;
}

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




