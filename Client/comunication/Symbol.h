//
// Created by flori on 11/10/2019.
//

#ifndef CLIENT_SYMBOL_H
#define CLIENT_SYMBOL_H



class Symbol {
    char character_;
    std::string uniqueId_;
    std::vector<int> pos_;
public:
    Symbol();

    Symbol(char character, std::string uniqueId, std::vector<int> &pos);

    bool operator==(const Symbol &symbol);

    bool operator<(const Symbol &symbol) const;


    char getCharacter() const;

    std::string getUniqueId() const;

    const std::vector<int> &getPos() const;

    protobuf::Symbol makeProtobufSymbol();
};


#endif //CLIENT_SYMBOL_H
