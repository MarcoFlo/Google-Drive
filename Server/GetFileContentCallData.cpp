#include <string>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "GetFileContentCallData.h"


GetFileContentCallData::GetFileContentCallData(protobuf::CharacterService::AsyncService *service,
                                               grpc::ServerCompletionQueue *cq)
        : service_(service), cq_(cq), responder_(&ctx_) {
    status_ = READ_CALLED;
    service_->RequestGetFileContent(&ctx_, &request_, &responder_, cq_, cq_, this);
}

void
GetFileContentCallData::HandleFileCall(protobuf::FileClientMap &fileClientMap, bool ok) {
    if (status_ == FINISH) {
        delete this;
        return;
    }

    if (!ok) {
        responder_.Finish(grpc::Status::OK, this);
        status_ = FINISH;
        return;
    }

    if (status_ == READ_CALLED) {
        new GetFileContentCallData(service_, cq_);
        protobuf::FileInfo messageReceived = request_;


        const std::string principal = ctx_.auth_context()->FindPropertyValues(
                ctx_.auth_context()->GetPeerIdentityPropertyName()).front().data();

        std::cout << "Get file content requested ->" << request_.filename() << std::endl;

        if (fileClientMap.fileclientmap().contains(principal)) {
            auto fileGet = std::find_if(fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->begin(),
                                        fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end(),
                                        [&messageReceived](protobuf::FileInfo &file) {
                                            return messageReceived.fileidentifier() == file.fileidentifier();
                                        });
            if (fileGet != fileClientMap.mutable_fileclientmap()->at(principal).mutable_fileil()->end()) {
                status_ = WRITE;
                std::cout << (*fileGet).fileidentifier() << "\n";
                std::ifstream input("db/fileContainer/" + (*fileGet).fileidentifier(),
                                    std::ios_base::in | std::ios_base::binary);
                symbolVector.ParseFromIstream(&input);
                input.close();
                std::cout << "vectorSize: " << symbolVector.symbolvector_size() << " bytesize: " << symbolVector.ByteSize() << "\n";
                int vectorSize = symbolVector.symbolvector_size()-1;

                if (symbolVector.ByteSize() == 0) {
                    status_ = FINISH;
                    responder_.Finish(grpc::Status::OK, this);
                    return;
                }

                int averageSymbolSize =
                        (symbolVector.symbolvector(0).ByteSize() +
                         symbolVector.symbolvector(vectorSize / 2).ByteSize() +
                         symbolVector.symbolvector(vectorSize).ByteSize()) /
                        3; //non serve una misurazione precisa contando che i singoli symbol anche nella loro variabilità in dimensione sono molto più piccoli di 32K
                std::cout << "AverageSymbolSize: "<< averageSymbolSize << "\n";
                chunkSize = 32000 / averageSymbolSize;
                std::cout << "chunkSize: " << chunkSize << "\n";

                protobuf::Chunk msg;
                msg.set_chunk("prova");
                responder_.Write(msg, this);
                return;
            } else {
                status_ = FINISH;
                responder_.Finish(grpc::Status(grpc::StatusCode::NOT_FOUND, "File non presente"), this);
            }
        } else {
            status_ = FINISH;
            responder_.Finish(grpc::Status(grpc::StatusCode::NOT_FOUND, "File non presente"), this);
        }
    } else if(status_ == WRITE) {
        protobuf::Chunk chunk;
        int vectorSize = symbolVector.ByteSize();
        std::cout << "VectorSize: " << vectorSize << "\n" << "symbolVector: " << symbolVector.DebugString() <<"\n";
        if (vectorSize < 64000) {
            //Se siamo sotto i 64KB non spezzettiamo
            status_ = FINISH;

            chunk.mutable_chunk()->assign(symbolVector.SerializeAsString());
            responder_.WriteAndFinish(chunk, grpc::WriteOptions(), grpc::Status::OK, this);
        } else {
            //altrimenti cerchiamo di stare attorno allo sweet spot di 32000 (16K-64K sono valori buoni)

            protobuf::SymbolVector symbolVectorPartial;
            if (index + chunkSize < symbolVector.symbolvector_size()) {
                //devo scrivere almeno ancora una volta
                symbolVectorPartial.mutable_symbolvector()->CopyFrom(
                        {symbolVector.symbolvector().begin() + index,
                         symbolVector.symbolvector().begin() + index + chunkSize});
                chunk.mutable_chunk()->assign(symbolVectorPartial.SerializeAsString());
                responder_.Write(chunk, this);
                index += chunkSize;
            } else {
                //è l'ultima volta che devo scrivere
                status_ = FINISH;
                symbolVectorPartial.mutable_symbolvector()->CopyFrom(
                        {symbolVector.symbolvector().begin() + index,
                         symbolVector.symbolvector().end()});
                chunk.mutable_chunk()->assign(symbolVectorPartial.SerializeAsString());
                responder_.WriteAndFinish(chunk, grpc::WriteOptions(), grpc::Status::OK, this);
            }
        }
    }
    return;
}
