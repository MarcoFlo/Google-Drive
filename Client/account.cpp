#include "account.h"
#include "ui_account.h"
#include <QMessageBox>
#include <regex>
//#include <QFileDialog>
//#include <QMessageBox>
#include <QDebug>
#include <sstream>
#include "principale.h"
#include "ui_principale.h"
#include <QCloseEvent>


Account::Account(QWidget *parent, CharacterClient *user) :
        QDialog(parent),
    ui(new Ui::Account)
{
    client_ = user;
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //ui->lineEdit->setText(client_->getNome().c_str());
    //ui->lineEdit_2->setText(client_->getCognome().c_str());
    ui->lineEdit_3->setText(client_->getEmail().c_str());
    ui->lineEdit_4->setText(client_->getPassword().c_str());
}

Account::~Account()
{
    delete ui;
}

/*void Account::setUser(CharacterClient *user_) {
    client_ = user_;
}*/

void Account::on_pushButton_clicked()
{
    this->hide();
    //parent->attivo(true);
}

void Account::on_pushButton_2_clicked()
{
    if(is_something_empty() == false)
    {
        QMessageBox::warning(this, "Account", "Riempire i campi vuoti");
        return;
    }

    /*if(client_->getNome().c_str() != ui->lineEdit->text())
    {
        //cambia
    }
    if(client_->getCognome().c_str() != ui->lineEdit_2->text())
    {
        //cambia
    }*/
    if(client_->getEmail().c_str() != ui->lineEdit_3->text())
    {
        if(is_email_valid() == false)
        {
            QMessageBox::warning(this, "Account", "L'email non è valida");
            return;
        }

        //cambia
    }
    //if(client_->getPassword().c_str() != ui->lineEdit_4->text())
    {
        if(is_pass_valid() == false)
        {
            QMessageBox::warning(this, "Account", "Le password non corrispondono");
            return;
        }

        //cambia
    }
    this->hide();
}

bool Account::is_email_valid()
{
    // define a regular expression
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool fin;
    // try to match the string with the regular expression
    if((fin = std::regex_match(ui->lineEdit_3->text().toStdString(), pattern))) {
        ui->label_4->setText("Email valida");
        ui->label_4->setStyleSheet("QLabel { color : green; }");
    } else {
        ui->label_4->setText("Inserire una email valida");
        ui->label_4->setStyleSheet("QLabel { color : red; }");
    }
    return fin;
}

bool Account::is_pass_valid()
{
    bool fin= ui->lineEdit_4->text() == ui->lineEdit_5->text();

    if(fin) {
        ui->label_5->setText("Password uguali");
        ui->label_5->setStyleSheet("QLabel { color : green; }");
    } else {
        ui->label_5->setText("Le password non corrispondono");
        ui->label_5->setStyleSheet("QLabel { color : red; }");
    }
    return fin;
}

bool Account::is_something_empty()
{
    return !ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_3->text().isEmpty() &&
           !ui->lineEdit_4->text().isEmpty();
}