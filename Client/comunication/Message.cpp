#include <messageP.pb.h>
#include "Message.h"

Message::Message(std::string &file_identifier, Symbol &symbol, bool isEraseBool) : file_identifier_(file_identifier), symbol_(symbol), isEraseBool_(isEraseBool) {}

protobuf::Message Message::makeProtobufMessage()
{
        protobuf::Message msg;
        msg.set_fileidentifier(file_identifier_);
        msg.mutable_symbol()->CopyFrom(symbol_.makeProtobufSymbol());
        msg.set_iserasebool(isEraseBool_);
        return msg;
}

const Symbol &Message::getSymbol() const {
    return symbol_;
}

bool Message::isErase() const {
    return isEraseBool_;
}
