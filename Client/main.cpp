#include <QApplication>
#include "principale.h"
#include "comunication/CharacterClient.h"

int main(int argc, char **argv) {
    CharacterClient client;

    /*
    protobuf::User user_share;
    user_share.set_username("provashare@test.it");
    user_share.set_password("1234");
    user_share.set_passwordr("1234");
    client.Register(user_share);

    protobuf::User user;
    user.set_username("provabase@test.it");
    user.set_password("1234");
    user.set_passwordr("1234");
    client.Register(user);

//    SharedEditor editor(client, user);

    client.Login(user);
    client.Logout();
    client.Login(user);

    protobuf::FileName fileName;
    fileName.set_filename("fileshare");
    client.InsertFile(fileName);


    client.GetFiles();
    std::cout << client.getFileInfoList().fileil(0).filename() << "\t" << client.getFileInfoList().fileil_size()
              << std::endl;
    client.ShareFile(client.getFileInfoList().fileil(0).fileidentifier(), user_share.username());

    client.GetFiles();
    std::cout << client.getFileInfoList().fileil(0).filename() << "\t" << client.getFileInfoList().fileil_size() << "\t" << client.getFileInfoList().fileil(0).usernameo()
              << std::endl;

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
