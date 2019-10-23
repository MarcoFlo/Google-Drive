//
// Created by flori on 23/10/2019.
//
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include "messageP.grpc.pb.h"
#include "CharacterServiceImpl.h"


CharacterServiceImpl::CharacterServiceImpl(const std::string &db) {
//cose
}

grpc::Status CharacterServiceImpl::ExchangeSymbol(grpc::ServerContext *context,
                                                  grpc::ServerReaderWriter<protobuf::Message, protobuf::Message> *stream) {
    protobuf::Message msg;
    while (stream->Read(&msg)) {
        std::cout << "Just received " << msg.symbol().character() << " gonna echo" << std::endl;
        stream->Write(msg);
    }
    return grpc::Status::OK;
}
