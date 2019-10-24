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
    void openR();
    void openP();

private slots:
    void on_Login_clicked();

    void on_registrati_clicked();

    void Mostra();

private:
    Ui::LoginPage *ui;
};

#endif // LOGINPAGE_H
