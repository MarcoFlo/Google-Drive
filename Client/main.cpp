#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <QApplication>
#include "qt/loginpage.h"
#include "qt/registrationpage.h"
#include "qt/principale.h"
#include "qt/splashscreen.h"
#include "qt/editor.h"
#include "qt/nuovo.h"

#include <grpcpp/grpcpp.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "messageP.grpc.pb.h"
#include "CharacterClient.h"


int main(int argc, char **argv) {

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




    std::string db = "path/to/route_guide_db.json";
    CharacterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()), db);
    client.ExchangeSymbol();

    return a.exec();

}