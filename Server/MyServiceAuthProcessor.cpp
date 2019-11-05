#include <string>
#include <grpcpp/grpcpp.h>
#include "MyServiceAuthProcessor.h"

struct Const {
    static const std::string &TokenKeyName() {
        static std::string _("token");
        return _;
    }

    static const std::string &PeerIdentityPropertyName() {
        static std::string _("username");
        return _;
    }
};

grpc::Status MyServiceAuthProcessor::Process(const grpc_impl::AuthMetadataProcessor::InputMetadata &auth_metadata,
                                             grpc::AuthContext *context,
                                             grpc_impl::AuthMetadataProcessor::OutputMetadata *consumed_auth_metadata,
                                             grpc_impl::AuthMetadataProcessor::OutputMetadata *response_metadata) {
// determine intercepted method
    std::string dispatch_keyname = ":path";
    auto dispatch_kv = auth_metadata.find(dispatch_keyname);
    if (dispatch_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::INTERNAL, "Internal Error");

    // if token metadata not necessary, return early, avoid token checking
    auto dispatch_value = std::string(dispatch_kv->second.data(), (dispatch_kv->second).length());
    std::cout << "Processor got call for: " << dispatch_value << std::endl << std::endl;
    if (dispatch_value == "/protobuf.CharacterService/Connect") {
        context->AddProperty("ideditor", "ciaone");
        return grpc::Status::OK;
    }

    // determine availability of token metadata
    auto token_kv = auth_metadata.find(Const::TokenKeyName());
    if (token_kv == auth_metadata.end())
        return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Missing Token");

    // determine validity of token metadata
    auto token_value = std::string(token_kv->second.data(), (token_kv->second).length());
    std::cout << "Processor got token: " << token_value << std::endl << std::endl;
    if (tokens.count(token_value) == 0)
        return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "Invalid Token");

    // once verified, mark as consumed and store user for later retrieval
    consumed_auth_metadata->insert(std::make_pair(Const::TokenKeyName(), token_value));     // required
    context->AddProperty(Const::PeerIdentityPropertyName(), tokens[token_value]);           // optional
    context->SetPeerIdentityPropertyName(Const::PeerIdentityPropertyName());                // optional

    return grpc::Status::OK;
}
