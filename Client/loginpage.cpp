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


