#include <QApplication>
#include "principale.h"
#include "comunication/CharacterClient.h"

int main(int argc, char **argv) {
    CharacterClient client;


    protobuf::ProfileInfo profileInfo;
    profileInfo.mutable_user()->set_email("provabase@test.it");
    profileInfo.mutable_user()->set_password("1234");
    profileInfo.mutable_user()->set_passwordr("1234");
    profileInfo.set_username("username");
    profileInfo.set_name("name");
    profileInfo.set_surname("surname");
    client.Register(profileInfo);
    client.Login(profileInfo.user());
    protobuf::ProfileInfo userLogged = client.getProfileInfoLogged();

    std::cout << userLogged.name() << "\t" << userLogged.surname() << "\t"
              << userLogged.username() << "\t" << userLogged.user().email() << std::endl;

//    client.ImportFile("1591635029186033100adf");
    client.Logout();


    QApplication a(argc, argv);
    Principale main;

    main.show();

    //fa partire l'interfaccia grafica
    //non lasciarlo nel return
    //è bloccante
    a.exec();

    return 0;

}
