//
// Created by flori on 23/10/2019.
//

#ifndef SERVER_CHARACTERSERVICEIMPL_H
#define SERVER_CHARACTERSERVICEIMPL_H


class CharacterServiceImpl final : public protobuf::CharacterService::Service {
public:
    explicit CharacterServiceImpl(const std::string& db);

    grpc::Status ExchangeSymbol(grpc::ServerContext *context,
                                          grpc::ServerReaderWriter<protobuf::Message, protobuf::Message> *stream) override;
};


#endif //SERVER_CHARACTERSERVICEIMPL_H
