#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
// #include "registrationpage.h" -> circular inclusion!
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"
#include "comunication/SharedEditor.h"
#include "comunication/AsyncClientGetSymbols.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    LoginPage(CharacterClient *client);
    ~LoginPage();

signals:
    void openR();
    void openP();

    void loginSuccess(QString token);

private slots:
    void on_Login_clicked();

    void on_registrati_clicked();

    void Mostra();

private:
    Ui::LoginPage *ui;
    CharacterClient *client_;
};

#endif // LOGINPAGE_H
