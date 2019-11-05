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
//    std::string serverCert;
//    read ( "../../certs/server.cert", serverCert );
//    grpc::SslCredentialsOptions opts;
//    opts.pem_root_certs = serverCert;
//
//    auto channel_creds = grpc::SslCredentials(opts);
//
//    CharacterClient client(grpc::CreateChannel("localhost:50051", channel_creds));
//
//    protobuf::UserR user;
//    user.set_username("prova@test.it");
//    SharedEditor editor(client, user);
//
//    std::thread thread_ = std::thread(&CharacterClient::GetSymbols, &client);

    QApplication a(argc, argv);
    SplashScreen w;
    LoginPage l;
    Principale p;
    RegistrationPage r;
    Editor e;

    e.show();

    QObject::connect(&w, SIGNAL(openL()), &l, SLOT(Mostra()));
    QObject::connect(&l, SIGNAL(openR()), &r, SLOT(Mostra()));
    QObject::connect(&l, SIGNAL(openP()), &p, SLOT(Mostra()));
    QObject::connect(&r, SIGNAL(openL()), &l, SLOT(Mostra()));
    QObject::connect(&r, SIGNAL(openP()), &p, SLOT(Mostra()));
    QObject::connect(&p, SIGNAL(openL()), &l, SLOT(Mostra()));
    QObject::connect(&e, SIGNAL(openP()), &p, SLOT(Mostra()));
    QObject::connect(&p, SIGNAL(openE()), &e, SLOT(Mostra()));

    //fa partire l'interfaccia grafica
    //non lasciarlo nel return
    //è bloccante
    a.exec();

//    thread_.join(); //blocks forever
    return 0;

}