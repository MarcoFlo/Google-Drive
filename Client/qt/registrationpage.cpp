#include "registrationpage.h"
#include "ui_registrationpage.h"


RegistrationPage::RegistrationPage(QWidget *parent) :
    QMainWindow(parent),
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
    hide();
    emit openL();
}

void RegistrationPage::on_registrati_clicked()
{
    hide();
    emit openP();
}

void RegistrationPage::Mostra()
{
    show();
}
