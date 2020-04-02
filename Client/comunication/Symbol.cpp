#include <vector>
#include <string>
#include "messageP.grpc.pb.h"
#include "Symbol.h"

Symbol::Symbol() {}

Symbol::Symbol(char character, std::string uniqueId, std::vector<int>& pos) : character_(character), uniqueId_(uniqueId), pos_(pos) {}

protobuf::Symbol Symbol::makeProtobufSymbol() {
    protobuf::Symbol symbol;
    symbol.set_character(std::to_string(character_));
    symbol.set_uniqueid(uniqueId_);
    *symbol.mutable_pos() = {pos_.begin(), pos_.end()};
    return symbol;
}

bool Symbol::operator==(const Symbol &symbol) {
    return this->getUniqueId()==symbol.getUniqueId();
}

bool Symbol::operator<(const Symbol &symbol) const {
    return this->getPos() < symbol.getPos();
}

char Symbol::getCharacter() const {
    return character_;
}

std::string Symbol::getUniqueId() const {
    return uniqueId_;
}

const std::vector<int> &Symbol::getPos() const {
    return pos_;
}




