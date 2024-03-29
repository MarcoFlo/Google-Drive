#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetSymbolsCallData.h"
#include "InsertSymbolsCallData.h"


InsertSymbolsCallData::InsertSymbolsCallData(protobuf::CharacterService::AsyncService *service,
                                             grpc::ServerCompletionQueue *cq) : service_(service), cq_(cq),
                                                                                responder_(&ctx_) {
    status_ = PROCESS;
    service_->RequestInsertSymbols(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void InsertSymbolsCallData::HandleFileSubscribedCall(protobuf::FileClientMap &fileClientMap,
                                                     std::map<std::string, std::vector<AbstractSubscribedCallData *>> &subscribedClientMap,
                                                     bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (!ok) {
        std::cout << "finish insertSymbols -> !ok" << std::endl;
//        responder_.Finish(&reply_, grpc::Status::OK, this);
        status_ = FINISH;
        return;
    }

    if (status_ == PROCESS) {
        std::cout << "InsertSymbols request" << std::endl;

        new InsertSymbolsCallData(service_, cq_);
        status_ = FINISH;

        protobuf::Message messageReceived = request_;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        auto fileInsert = std::find_if(fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->begin(),
                                       fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end(),
                                       [&messageReceived](protobuf::FileInfo &file) {
                                           return messageReceived.fileidentifier() == file.fileidentifier();
                                       });

        if (fileInsert != fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end()) {
            //scrittura su file passando dal vettore in modo che scrivendo un symbol alla volta poi si possa comunque leggere il tutto come vettore
            protobuf::SymbolVector symbolVector;
            protobuf::Symbol symbol = request_.symbol();
            if (!request_.iserasebool()) {
                symbolVector.mutable_symbolvector()->Add(std::move(symbol));

                std::ofstream output("db/fileContainer/" + request_.fileidentifier(),
                                     std::ios::out | std::ios::app | std::ios_base::binary);
                symbolVector.SerializeToOstream(&output);
                output.close();
            } else {
                std::ifstream input("db/fileContainer/" + (*fileInsert).fileidentifier(),
                                    std::ios_base::in | std::ios_base::binary);
                symbolVector.ParseFromIstream(&input);
                input.close();
                auto vec = symbolVector.mutable_symbolvector();
                google::protobuf::internal::RepeatedPtrIterator<protobuf::Symbol> findPos = std::find(vec->begin(),
                                                                                                      vec->end(),
                                                                                                      symbol);
                vec->erase(findPos);
                std::ofstream output("db/fileContainer/" + request_.fileidentifier(),
                                     std::ios::out | std::ios::trunc);
                output.close();
                std::ofstream out("db/fileContainer/" + request_.fileidentifier(),
                                  std::ios::out | std::ios::app | std::ios_base::binary);
                symbolVector.SerializeToOstream(&out);
                out.close();
            }

            std::for_each(
                    subscribedClientMap.at(request_.fileidentifier()).begin(),
                    subscribedClientMap.at(request_.fileidentifier()).end(),
                    [&messageReceived, &principal](AbstractSubscribedCallData *getSymbolsCallData) {
                        GetSymbolsCallData *call = static_cast<GetSymbolsCallData *>(getSymbolsCallData);
                        if (call->mailPrincipal != principal)
                            call->HandleSymbol(messageReceived);
                    });
            responder_.Finish(reply_, grpc::Status::OK, this);
        } else {
            status_ = FINISH;
            responder_.Finish(reply_, grpc::Status(grpc::StatusCode::NOT_FOUND, "File non presente"), this);
        }
    }
}
