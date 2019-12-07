#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::LoginPage) {
    ui->setupUi(this);

    splash = new SplashScreen(this);
    splash->show();
    QTimer::singleShot(4000, this, SLOT(closeSplash()));

    client_ = new CharacterClient();

    QPixmap *logo = new QPixmap("img/logo.png");
    ui->logo->setPixmap(*logo);
    ui->regi->setVisible(false);

    ui->EmailEdit->setText("test");
    ui->PasswordEdit->setText("test");
}

LoginPage::~LoginPage() {
    delete ui;
}

void LoginPage::on_Login_clicked() {
    QString username = ui->EmailEdit->text();
    QString pass = ui->PasswordEdit->text();

    protobuf::User userL;
    userL.set_username(username.toStdString());
    userL.set_password(pass.toStdString());
    std::string token = client_->Login(userL);

    if (token.compare("") != 0) {
        this->hide();
        p = new Principale(this, client_);
        QObject::connect(p, SIGNAL(closeP()), this, SLOT(on_closeP_signal()));
        p->show();
    } else {
        QMessageBox::warning(this, "Login", "Username and/or password is not correct");
    }
}

void LoginPage::on_registrati_clicked() {
    hide();
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

void LoginPage::closeSplash() {
    splash->hide();
    delete splash;
}
