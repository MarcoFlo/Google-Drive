#include <iostream>
#include <thread>
#include <sstream>
#include <fstream>
#include <QApplication>
#include "loginpage.h"
#include "registrationpage.h"
#include "principale.h"
#include "splashscreen.h"
#include "editor.h"
#include "nuovo.h"

#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"

#include "comunication/CharacterClient.h"
#include "comunication/SharedEditor.h"
#include "comunication/AsyncClientGetSymbols.h"

void read(const std::string &filename, std::string &data) {
    std::ifstream file(filename.c_str(), std::ios::in);

    if (file.is_open()) {
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        data = ss.str();
    }
}

int main(int argc, char **argv) {

    std::string serverCert;
    read("../../certs/server.cert", serverCert);
    grpc::SslCredentialsOptions opts;
    opts.pem_root_certs = serverCert;

    auto channel_creds = grpc::SslCredentials(opts);

    CharacterClient client(grpc::CreateChannel("localhost:50051", channel_creds));

    protobuf::UserR userR;
    userR.set_username("prova@test.it");
    userR.set_password("1234");
    userR.set_passwordr("1234");
    client.Register(userR);


    protobuf::UserL userL;
    userL.set_username("prova@test.it");
    userL.set_password("1234");
//    SharedEditor editor(client, userL);

    std::string token = client.Login(userL);
    client.Logout(token);
    token = client.Login(userL);

    AsyncClientGetSymbols *asyncClientGetSymbols = client.GetSymbols("file1", token);


    std::thread thread_ = std::thread(&CharacterClient::AsyncCompleteRpc, &client);

    QApplication a(argc, argv);
    SplashScreen w;

    w.show();

    //fa partire l'interfaccia grafica
    //non lasciarlo nel return
    //è bloccante
    a.exec();

    return 0;

}
