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
            if(!request_.iserasebool()) {
                symbolVector.mutable_symbolvector()->Add(std::move(symbol));

                std::ofstream output("fileContainer/" + request_.fileidentifier(),
                                     std::ios::out | std::ios::app | std::ios_base::binary);
                symbolVector.SerializeToOstream(&output);
                output.close();
            }
            /*else {
                auto vec=symbolVector.mutable_symbolvector();
                std::cout << "bau\n";
                google::protobuf::internal::RepeatedPtrIterator<protobuf::Symbol> findPos = std::find(vec->begin(), vec->end(), symbol);
                std::cout << "miao\n";
                vec->erase(findPos);
                std::cout << "bee\n";
                std::ofstream output("fileContainer/" + request_.fileidentifier(),
                                     std::ios::out | std::ios::app | std::ios_base::binary);
                std::cout << "muu\n";
                symbolVector.SerializeToOstream(&output);
                std::cout << "quack\n";
                output.close();
            }*/
          /*  std::for_each(
                    subscribedClientMap.at(request_.fileidentifier()).begin(),
                    subscribedClientMap.at(request_.fileidentifier()).end(),
                    [&messageReceived](AbstractSubscribedCallData *getSymbolsCallData) {
                        dynamic_cast<GetSymbolsCallData *>(getSymbolsCallData)->HandleSymbol(messageReceived);
                    });*/
            responder_.Finish(reply_, grpc::Status::OK, this);
        } else {
            status_ = FINISH;
            responder_.Finish(reply_, grpc::Status(grpc::StatusCode::NOT_FOUND, "File non presente"), this);
        }
    }
}
