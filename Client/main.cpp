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

int main(int argc, char **argv) {
    CharacterClient client;

    protobuf::User user;
    user.set_username("prova@test.it");
    user.set_password("1234");
    user.set_passwordr("1234");
    client.Register(user);

//    SharedEditor editor(client, user);

    client.Login(user);
    client.Logout();
    client.Login(user);

    protobuf::FileName fileName;
    fileName.set_filename("file1");
    client.InsertFile(fileName);


    std::vector<int> posNew;
    posNew.push_back(1);
    Symbol symbol('a', "uniqueID", posNew);

    client.InsertSymbols(symbol, false);


    QApplication a(argc, argv);
    LoginPage log;

    log.show();

    //fa partire l'interfaccia grafica
    //non lasciarlo nel return
    //è bloccante
    a.exec();

    return 0;

}
