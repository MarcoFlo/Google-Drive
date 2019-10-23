//
// Created by flori on 23/10/2019.
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "messageP.grpc.pb.h"
#include "CharacterClient.h"

protobuf::Message MakeMessage(int idEditor, protobuf::Symbol symbol, bool isErase) {
    protobuf::Message msg;
    msg.set_ideditor(idEditor);
    msg.mutable_symbol()->CopyFrom(symbol);
    msg.set_iserasebool(isErase);
    return msg;
}


protobuf::Symbol MakeSymbol(std::string character, int uniqueId, std::vector<int> pos) {
    protobuf::Symbol symbol;
    symbol.set_character(character);
    symbol.set_uniqueid(uniqueId);
    *symbol.mutable_pos() = {pos.begin(), pos.end()};
    return symbol;
}

CharacterClient::CharacterClient(std::shared_ptr<grpc::Channel> channel, const std::string &db) : stub_(
        protobuf::CharacterService::NewStub(channel)) {}

void CharacterClient::ExchangeSymbol() {
    {
        grpc::ClientContext context;

        std::shared_ptr<grpc::ClientReaderWriter<protobuf::Message, protobuf::Message>> stream(
                stub_->ExchangeSymbol(&context));

        std::vector<protobuf::Message> messages{
                MakeMessage(0, MakeSymbol("a", 0, {0}), false),
                MakeMessage(1, MakeSymbol("b", 1, {0, 1}), false),
                MakeMessage(2, MakeSymbol("c", 2, {0, 5}), false),
                MakeMessage(3, MakeSymbol("d", 3, {2}), false),
                MakeMessage(4, MakeSymbol("e", 4, {3}), false),
                MakeMessage(5, MakeSymbol("f", 5, {4}), false)};


        std::thread writer([stream, messages]() {
            for (const protobuf::Message &msg : messages) {
                std::cout << "Sending message " << msg.symbol().character() << std::endl;
                if (!stream->Write(msg)) {
                    std::cout << " write failed";
                }
            }
            stream->WritesDone();
        });

        protobuf::Message server_msg;
        while (stream->Read(&server_msg)) {
            std::cout << "Got message " << server_msg.symbol().character() << std::endl;
        }
        writer.join();
        grpc::Status status = stream->Finish();

        if (!status.ok()) {
            std::cout << "ExchangeSymbol rpc failed." << std::endl;
        }
    }

}


