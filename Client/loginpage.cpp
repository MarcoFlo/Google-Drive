#include <QFile>
#include <QMessageBox>
#include "loginpage.h"
#include "ui_loginpage.h"
#include <QAction>

LoginPage::LoginPage(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::LoginPage) {
    ui->setupUi(this);
    client_ = new CharacterClient();

    protobuf::ProfileInfo user;
    user.set_username("prova@test.it");
    user.set_name("prova");
    user.set_surname("prova");
    user.mutable_user()->set_email("prova@test.it");
    user.mutable_user()->set_password("1234");
    user.mutable_user()->set_passwordr("1234");
    client_->Register(user);

    protobuf::ProfileInfo user1;
    user1.set_username("prova1@test.it");
    user1.set_name("prova1");
    user1.set_surname("prova1");
    user1.mutable_user()->set_email("prova1@test.it");
    user1.mutable_user()->set_password("1234");
    user1.mutable_user()->set_passwordr("1234");
    client_->Register(user1);

    ui->regi->setVisible(false);
    ui->EmailEdit->setText("prova@test.it");
    ui->PasswordEdit->setText("1234");
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //ui->Login->setShortcut(Qt::Key_Enter);

}

LoginPage::~LoginPage() {
    delete ui;
}

void LoginPage::on_Login_clicked() {
    QString email = ui->EmailEdit->text();
    QString pass = ui->PasswordEdit->text();

    protobuf::User userL;
    userL.set_email(email.toStdString());
    userL.set_password(pass.toStdString());
    std::string error = client_->Login(userL);


    if (error.empty()) {   // status == ok
        this->hide();
        emit clientReturn(client_);
    } else {
        QMessageBox::warning(this, "Login", "Username and/or password is not correct");
    }
}

void LoginPage::on_registrati_clicked() {
    this->hide();
    emit regRequest();
}

void LoginPage::on_closeRReg_signal() {
    ui->regi->setVisible(true);
    ui->regi->setText("Registrazione completata. Accedi inserendo email e password");
    this->show();
}


