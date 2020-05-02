#include <QApplication>
#include "principale.h"
#include "comunication/CharacterClient.h"

int main(int argc, char **argv) {
    CharacterClient client;

    /*
    protobuf::User user;
    user.set_username("provabase@test.it");
    user.set_password("1234");
    user.set_passwordr("1234");
    client.Register(user);
    client.Login(user);

    protobuf::FileName fileName;
    fileName.set_filename("fileshare");
    client.InsertFile(fileName);

    client.GetFiles();
    client.GetFileContent(client.getFileInfoList().fileil(0));
    /*

    QApplication a(argc, argv);
    Principale main;

    main.show();

    //fa partire l'interfaccia grafica
    //non lasciarlo nel return
    //è bloccante
    a.exec();

    return 0;

}
