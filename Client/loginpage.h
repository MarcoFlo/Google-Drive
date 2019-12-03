#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include "principale.h"
#include "registrationpage.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "splashscreen.h"
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"
#include <iostream>
#include <thread>
#include <sstream>
#include <fstream>

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

signals:
    void closeR();
    void closeP();

private slots:
    void on_Login_clicked();

    void on_registrati_clicked();

    void on_closeR_signal();

    void on_closeP_signal();

    void on_closeRReg_signal();

    void closeSplash();

private:
    Ui::LoginPage *ui;
    RegistrationPage *r;
    Principale *p;
    SplashScreen *splash;
    CharacterClient *client_;
    QString token;
};
#endif // LOGINPAGE_H
