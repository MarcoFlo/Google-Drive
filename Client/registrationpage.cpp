#include <regex>
#include "registrationpage.h"
#include "ui_registrationpage.h"

RegistrationPage::RegistrationPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegistrationPage)
{
    ui->setupUi(this);
    client_=new CharacterClient();
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QObject::connect(ui->emailEdit, SIGNAL(editingFinished()), this, SLOT(is_email_valid()));
    QObject::connect(ui->password2Edit, SIGNAL(editingFinished()), this, SLOT(is_pass_valid()));
    QObject::connect(ui->passwordEdit, SIGNAL(editingFinished()), this, SLOT(is_pass_valid()));
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
    if(!is_something_empty()) {
        QMessageBox::warning(this, "Registration", "Riempire i campi vuoti");
    } else if(!is_email_valid()) {
        QMessageBox::warning(this, "Registration", "L'email non è valida");
    } else if(!is_pass_valid()) {
        QMessageBox::warning(this, "Registration", "Le password non corrispondono");
    } else {
        QString email = ui->emailEdit->text();
        QString pass = ui->passwordEdit->text();
        QString pass2 = ui->password2Edit->text();
        //QString nome = ui->emailEdit->text();
        //QString cognome = ui->nomeEdit->text();
        protobuf::ProfileInfo profileInfo;
        //protobuf::ProfileInfo profInfo;
        profileInfo.mutable_user()->set_email(email.toStdString());
        profileInfo.mutable_user()->set_password(pass.toStdString());
        profileInfo.mutable_user()->set_passwordr(pass2.toStdString());
        /*profInfo.set_name(nome.toStdString());
        profInfo.set_surname(cognome.toStdString());
        profInfo.email(email.toStdString());
        profInfo.set_allocated_user(&userR);*/
        std::string error = this->client_->Register(profileInfo);
        if (error.empty()) {
            emit closeRReg();
        }
        else {
            QMessageBox::warning(this, "Registration", "Invalid data");
        }
    }
}

bool RegistrationPage::is_email_valid()
{
    // define a regular expression
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool fin;
    // try to match the string with the regular expression
    if((fin = std::regex_match(ui->emailEdit->text().toStdString(), pattern))) {
        ui->email->setText("Email valida");
        ui->email->setStyleSheet("QLabel { color : green; }");
    } else {
        ui->email->setText("Inserire una email valida");
        ui->email->setStyleSheet("QLabel { color : red; }");
    }
    return fin;
}

bool RegistrationPage::is_pass_valid()
{
    bool fin= ui->passwordEdit->text() == ui->password2Edit->text();

    if(fin) {
        ui->password2->setText("Password uguali");
        ui->password2->setStyleSheet("QLabel { color : green; }");
    } else {
        ui->password2->setText("Le password non corrispondono");
        ui->password2->setStyleSheet("QLabel { color : red; }");
    }
    return fin;
}

bool RegistrationPage::is_something_empty()
{
    return !ui->emailEdit->text().isEmpty() && !ui->nomeEdit->text().isEmpty() && !ui->emailEdit->text().isEmpty() &&
           !ui->passwordEdit->text().isEmpty() && !ui->password2Edit->text().isEmpty();
}