//
// Created by flori on 11/10/2019.
//

#ifndef CLIENT_SYMBOL_H
#define CLIENT_SYMBOL_H



class Symbol {

    char character_;
    std::string uniqueId_;
    std::vector<int> pos_;
    bool bold_;
    bool underline_;
    bool italic_;
    int dimension_;
    std::string color_;
    std::string font_;
public:
    Symbol();

    Symbol(char character, std::string uniqueId, std::vector<int> &pos, bool bold, bool underline, bool italic, int dimension, std::string color, std::string font);

    Symbol(protobuf::Symbol);

    bool operator==(const Symbol &symbol);

    bool operator<(const Symbol &symbol) const;


    char getCharacter() const;

    std::string getUniqueId() const;

    const std::vector<int> &getPos() const;

    const bool getBold() const;

    const bool getUnderline() const;

    const bool getItalic() const;

    int getDimension() const;

    std::string getColor() const;

    std::string getFont() const;

    protobuf::Symbol makeProtobufSymbol();
};


#endif //CLIENT_SYMBOL_H
