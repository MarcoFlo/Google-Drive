#include <iostream>
#include <string>
#include <QApplication>
#include "qt/loginpage.h"
#include "qt/registrationpage.h"
#include "qt/principale.h"
#include "qt/splashscreen.h"
#include "qt/editor.h"
#include "qt/nuovo.h"

#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"


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


    CharacterClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::cout << "Expected a: " << client.GetSymbols("prova@test.it") << std::endl;

    return a.exec();

}