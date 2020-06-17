#include <QApplication>
#include "principale.h"
#include "comunication/CharacterClient.h"

int main(int argc, char **argv) {
    CharacterClient client;


    protobuf::ProfileInfo profileInfo;
    profileInfo.mutable_user()->set_email("provabase@test.it");
    profileInfo.mutable_user()->set_password("pw");
    profileInfo.mutable_user()->set_passwordr("pw");
    profileInfo.set_username("username");
    profileInfo.set_name("name");
    profileInfo.set_surname("surname");
    client.Register(profileInfo);
    client.Login(profileInfo.user());

    client.GetProfile();
    protobuf::ProfileInfo oldProfileInfo = client.getProfileInfoLogged();
    std::cout << oldProfileInfo.name() << "\t" << oldProfileInfo.surname() << "\t"
              << oldProfileInfo.username() << "\t" << oldProfileInfo.user().email() << "\t" << oldProfileInfo.user().password()
              << std::endl;

    protobuf::ProfileInfo newProfileInfo;
    newProfileInfo.set_name("a");
    newProfileInfo.set_surname("b");
    newProfileInfo.set_username("c");
    newProfileInfo.mutable_user()->set_password("pw");
    newProfileInfo.mutable_user()->set_passwordr("pw");
    client.SetProfile(newProfileInfo);
    client.GetProfile();
    newProfileInfo = client.getProfileInfoLogged();
    std::cout << newProfileInfo.name() << "\t" << newProfileInfo.surname() << "\t"
              << newProfileInfo.username() << "\t" << newProfileInfo.user().email() << "\t" << newProfileInfo.user().password()
              << std::endl;


    protobuf::ProfileInfo nProfileInfo;
    nProfileInfo.set_name("aaaa");
    nProfileInfo.set_surname("bbbb");
    nProfileInfo.set_username("cccc");
    nProfileInfo.mutable_user()->set_password("pw");
    nProfileInfo.mutable_user()->set_passwordr("pw");
    client.SetProfile(nProfileInfo);
    client.GetProfile();
    nProfileInfo = client.getProfileInfoLogged();
    std::cout << nProfileInfo.name() << "\t" << nProfileInfo.surname() << "\t"
              << nProfileInfo.username() << "\t" << nProfileInfo.user().email() << "\t" << nProfileInfo.user().password()
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
