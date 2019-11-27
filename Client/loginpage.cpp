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
    ui->regi->setVisible(false);
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

    if(username.compare("test")==0 && pass.compare("test")==0) {
        hide();
        p=new Principale();
        QObject::connect(p, SIGNAL(closeP()), this, SLOT(on_closeP_signal()));
        p->show();
    }
    else {
        QMessageBox::warning(this,"Login", "Username and/or password is not correct");
    }
}

void LoginPage::on_registrati_clicked()
{
    hide();
    //emit openR();
    r = new RegistrationPage(this);
    QObject::connect(r, SIGNAL(closeR()), this, SLOT(on_closeR_signal()));
    QObject::connect(r, SIGNAL(closeRReg()), this, SLOT(on_closeRReg_signal()));
    r->show();

}

void LoginPage::on_closeR_signal() {

    r->hide();
    this->show();
    delete r;
}

void LoginPage::on_closeP_signal() {

    p->hide();
    this->show();
    delete p;
}

void LoginPage::on_closeRReg_signal() {
    r->hide();
    ui->regi->setVisible(true);
    ui->regi->setText("Registrazione completata. Accedi inserendo username e password");
    this->show();
    delete r;
}

