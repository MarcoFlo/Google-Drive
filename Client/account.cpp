#include "account.h"
#include "ui_account.h"
#include <QMessageBox>
#include <regex>
//#include <QFileDialog>
#include <QDebug>
#include <sstream>
#include "principale.h"
#include "ui_principale.h"
#include <QCloseEvent>


Account::Account(QWidget *parent, CharacterClient *user) :
        QDialog(parent),
        ui(new Ui::Account) {
    client_ = user;
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    profileInfoLogged = client_->getProfileInfoLogged();
    ui->lineEdit->setText(profileInfoLogged.name().c_str());
    ui->lineEdit_2->setText(profileInfoLogged.username().c_str());
    ui->lineEdit_3->setText(profileInfoLogged.user().email().c_str());
    ui->lineEdit_4->setText(profileInfoLogged.user().password().c_str());
    ui->lineEdit_5->setText(profileInfoLogged.user().password().c_str());
}

Account::~Account() {
    delete ui;
}


void Account::on_pushButton_clicked() {
    this->hide();
    //parent->attivo(true);
}

void Account::on_pushButton_2_clicked() {
    if (is_something_empty() == false) {
        QMessageBox::warning(this, "Account", "Riempire i campi vuoti");
        return;
    } else{

        if(!is_email_valid()) {
            QMessageBox::warning(this, "Account", "L'email non è valida");
            return;
        } else if(!is_pass_valid()) {
            QMessageBox::warning(this, "Account", "Le password non corrispondono");
            return;
        } else {

            profileInfoLogged.set_name(ui->lineEdit->text().toStdString());
            profileInfoLogged.set_username(ui->lineEdit_2->text().toStdString());
            profileInfoLogged.mutable_user()->set_email(ui->lineEdit_3->text().toStdString());
            profileInfoLogged.mutable_user()->set_password(ui->lineEdit_4->text().toStdString());
            profileInfoLogged.mutable_user()->set_passwordr(ui->lineEdit_5->text().toStdString());
            std::string error = client_->SetProfile(profileInfoLogged);

            if (error.empty()) {
                emit closeAccount(client_);
                this->hide();
            }
            else {
                QMessageBox::warning(this, "Account", "Invalid data");
            }
        }
    }
}

bool Account::is_email_valid() {
    // define a regular expression
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool fin;
    // try to match the string with the regular expression
    if ((fin = std::regex_match(ui->lineEdit_3->text().toStdString(), pattern))) {
        ui->email->setText("Email valida");
        ui->email->setStyleSheet("QLabel { color : green; }");
    } else {
        ui->email->setText("Inserire una email valida");
        ui->email->setStyleSheet("QLabel { color : red; }");
    }
    return fin;
}

bool Account::is_pass_valid() {
    bool fin = ui->lineEdit_4->text() == ui->lineEdit_5->text();

    if (fin) {
        ui->password->setText("Password uguali");
        ui->password->setStyleSheet("QLabel { color : green; }");
    } else {
        ui->password->setText("Le password non corrispondono");
        ui->password->setStyleSheet("QLabel { color : red; }");
    }
    return fin;
}

bool Account::is_something_empty() {
    return !ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_3->text().isEmpty() &&
           !ui->lineEdit_4->text().isEmpty() && !ui->lineEdit_5->text().isEmpty();
}