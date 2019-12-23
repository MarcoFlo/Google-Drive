#include "registrationpage.h"
#include "ui_registrationpage.h"

#include <QMessageBox>

RegistrationPage::RegistrationPage(QWidget *parent, CharacterClient *client) :
    QMainWindow(parent),
    client_(client),
    ui(new Ui::RegistrationPage)
{
    ui->setupUi(this);
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
    QString username = ui->usernameEdit->text();
    QString pass = ui->passwordEdit->text();
    QString pass2 = ui->password2Edit->text();

    protobuf::User userR;
    userR.set_username(username.toStdString());
    userR.set_password(pass.toStdString());
    userR.set_passwordr(pass2.toStdString());
    std::string error = this->client_->Register(userR);

    if (error.compare("") == 0) {   // status == ok
        //hide(); // already made by loginpage
        std::cout << "EMIT SIGNAL" << std::endl;
        emit closeRReg();
    }
    else {
        QMessageBox::warning(this, "Registration", "Invalid data");
    }
}

