#include <messageP.pb.h>
#include "Message.h"

Message::Message(Symbol &symbol, bool isEraseBool) : symbol(symbol), isEraseBool(isEraseBool) {}

protobuf::Message Message::makeProtobufMessage()
{
        protobuf::Message msg;
        msg.mutable_symbol()->CopyFrom(symbol.makeProtobufSymbol());
        msg.set_iserasebool(isEraseBool);
        return msg;
}

const Symbol &Message::getSymbol() const {
    return symbol;
}

bool Message::isErase() const {
    return isEraseBool;
}
