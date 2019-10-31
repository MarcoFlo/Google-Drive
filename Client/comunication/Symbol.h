//
// Created by flori on 11/10/2019.
//

#ifndef CLIENT_SYMBOL_H
#define CLIENT_SYMBOL_H



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

    protobuf::Symbol makeProtobufSymbol();
};


#endif //CLIENT_SYMBOL_H
