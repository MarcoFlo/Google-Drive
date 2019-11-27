#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include "principale.h"
#include "registrationpage.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

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

private:
    Ui::LoginPage *ui;
    RegistrationPage *r;
    Principale *p;
};
#endif // LOGINPAGE_H
