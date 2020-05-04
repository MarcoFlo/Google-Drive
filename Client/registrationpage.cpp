#include "registrationpage.h"
#include "ui_registrationpage.h"

RegistrationPage::RegistrationPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationPage)
{
    ui->setupUi(this);
    client_=new CharacterClient();
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

RegistrationPage::~RegistrationPage()
{
    delete ui;
}

void RegistrationPage::on_annulla_clicked()
{
    emit closeR();
}

void RegistrationPage::on_registrati_clicked()
{
    QString username = ui->emailEdit->text();
    QString pass = ui->passwordEdit->text();
    QString pass2 = ui->password2Edit->text();
    protobuf::User userR;
    userR.set_username(username.toStdString());
    userR.set_password(pass.toStdString());
    userR.set_passwordr(pass2.toStdString());
   std::string error = this->client_->Register(userR);

    if (error.empty()) {
        emit closeRReg();
    }
    else {
        QMessageBox::warning(this, "Registration", "Invalid data");
    }
}

