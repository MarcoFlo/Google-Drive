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
    service_->RequestInsertSymbols(&ctx_, &responder_, cq_, cq_,
                                   this);
}

void InsertSymbolsCallData::HandleFileSubscribedCall(protobuf::FileClientMap &fileClientMap,
                                                     std::map<std::string, std::vector<AbstractSubscribedCallData *>> &subscribedClientMap,
                                                     bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (!ok) {
        std::cout << "finish" << std::endl;
//        responder_.Finish(&reply_, grpc::Status::OK, this);
        status_ = FINISH;
        return;
    }

    if (status_ == PROCESS) {
        status_ = READ;
        new InsertSymbolsCallData(service_, cq_);
    } else if (status_ == READ) {
        status_ = READ_CALLED;
        responder_.Read(&request_, this);
    } else if (status_ == READ_CALLED) {
        status_ = READ;
        protobuf::Message messageReceived = request_;
        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        auto fileInsert = std::find_if(fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->begin(),
                                       fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end(),
                                       [&messageReceived](protobuf::FileInfo &file) {
                                           return messageReceived.fileinfo().identifier() == file.identifier();
                                       });

        if (fileInsert != fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end()) {
            //scrittura su file passando dal vettore in modo che scrivendo un symbol alla volta poi si possa comunque leggere il tutto come vettore
            protobuf::SymbolVector symbolVector;
            protobuf::Symbol symbol = request_.symbol();
            symbolVector.mutable_symbolvector()->Add(std::move(symbol));
            std::ofstream output("fileContainer/" + request_.fileinfo().identifier(),
                                 std::ios::out | std::ios::app | std::ios_base::binary);
            symbolVector.SerializeToOstream(&output);
            output.close();

            std::for_each(
                    subscribedClientMap.at(request_.fileinfo().identifier()).begin(),
                    subscribedClientMap.at(request_.fileinfo().identifier()).end(),
                    [&messageReceived](AbstractSubscribedCallData *getSymbolsCallData) {
                        dynamic_cast<GetSymbolsCallData *>(getSymbolsCallData)->HandleSymbol(messageReceived);
                    });
        } else {
            status_ = FINISH;
            responder_.Finish(reply_, grpc::Status(grpc::StatusCode::NOT_FOUND, "File non presente"), this);
        }
    }
}
