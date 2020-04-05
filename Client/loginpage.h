#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    void on_closeRReg_signal();

signals:
    void clientReturn(CharacterClient*);
    void regRequest();

private slots:
    void on_Login_clicked();

    void on_registrati_clicked();

private:
    Ui::LoginPage *ui;
    CharacterClient *client_;
    QString token;
};
#endif // LOGINPAGE_H
