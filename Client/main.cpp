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

    client.GetProfile();
    protobuf::ProfileInfo userLogged = client.getProfileInfoLogged();
    std::cout << userLogged.name() << "\t" << userLogged.surname() << "\t"
              << userLogged.username() << "\t" << userLogged.user().email() << std::endl;

    userLogged.set_name("a");
    userLogged.set_surname("b");
    userLogged.set_username("c");
    userLogged.mutable_user()->set_email("d");
    userLogged.mutable_user()->set_password("pw");
    userLogged.mutable_user()->set_passwordr("pw");
    client.SetProfile(userLogged);
    std::cout << userLogged.name() << "\t" << userLogged.surname() << "\t"
              << userLogged.username() << "\t" << userLogged.user().email() << "\t" << userLogged.user().password()
              << std::endl;

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
