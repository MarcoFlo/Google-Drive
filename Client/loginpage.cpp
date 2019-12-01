#include "loginpage.h"
#include "ui_loginpage.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

LoginPage::LoginPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);

    QSqlDatabase mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("path del db");

    if(!mydb.open()) {
        QMessageBox::warning(this,"Database error", "Failed to open the database");
    }
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_Login_clicked()
{
    QString username = ui->EmailEdit->text();
    QString pass = ui->PasswordEdit->text();


//    if(username.compare("test")==0 && pass.compare("test")==0) {
//        hide();
//        emit openP();
//    }
//    else {
//        QMessageBox::warning(this,"Login", "Username and/or password is not correct");
//    }

    protobuf::UserL userL;
    userL.set_username(username.toStdString());
    userL.set_password(pass.toStdString());
    std::string token = client_->Login(userL);
    emit loginSuccess(QString::fromStdString(token));

}

void LoginPage::on_registrati_clicked()
{
    hide();
    emit openR();

}

void LoginPage::Mostra()
{
    show();
}
