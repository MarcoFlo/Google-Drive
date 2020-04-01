#include <QApplication>
#include "principale.h"
#include "comunication/CharacterClient.h"

int main(int argc, char **argv) {
    CharacterClient client;
/*
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

    client.GetFiles();
    std::cout << client.getFileInfoList().fileil(0).filename() << "\t" << client.getFileInfoList().fileil_size()
              << std::endl;

    std::vector<int> posNew;
    posNew.push_back(1);
    Symbol symbol('a', "uniqueID", posNew);

    client.InsertSymbols(symbol, false);
*/

    QApplication a(argc, argv);
    Principale main;

    main.show();

    //fa partire l'interfaccia grafica
    //non lasciarlo nel return
    //è bloccante
    a.exec();

    return 0;

}
