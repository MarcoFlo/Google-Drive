#include <vector>
#include <string>
#include "messageP.grpc.pb.h"
#include "Symbol.h"

Symbol::Symbol() {}

Symbol::Symbol(char character, std::string uniqueId, std::vector<int>& pos, bool bold, bool underline, bool italic, int dimension, std::string color, std::string font, std::string allineamento) : character_(character), uniqueId_(uniqueId), pos_(pos), bold_(bold), underline_(underline), italic_(italic), dimension_(dimension), color_(color), font_(font), allineamento_(allineamento) {}

Symbol::Symbol(protobuf::Symbol s) {
    int i=0;
    character_ = stoi(s.character());
    uniqueId_ = s.uniqueid();
    bold_ = s.bold();
    underline_ = s.underline();
    italic_ = s.italic();
    dimension_ = s.dimension();
    color_ = s.color();
    font_ = s.font();
    allineamento_ = s.allineamento();
    for(i=0; i < s.pos_size(); i++)
    {
        pos_.push_back(s.pos(i));
    }
}

protobuf::Symbol Symbol::makeProtobufSymbol() {
    protobuf::Symbol symbol;
    symbol.set_character(std::to_string(character_));
    symbol.set_uniqueid(uniqueId_);
    symbol.set_bold(bold_);
    symbol.set_underline(underline_);
    symbol.set_italic(italic_);
    symbol.set_dimension(dimension_);
    symbol.set_color(color_);
    symbol.set_font(font_);
    symbol.set_allineamento(allineamento_);
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

const bool Symbol::getBold() const {
    return bold_;
}

const bool Symbol::getUnderline() const {
    return underline_;
}

const bool Symbol::getItalic() const {
    return italic_;
}

int Symbol::getDimension() const {
    return dimension_;
}

std::string Symbol::getColor() const {
    return color_;
}

std::string Symbol::getFont() const {
    return font_;
}

std::string Symbol::getAllineamento() const {
    return allineamento_;
}

