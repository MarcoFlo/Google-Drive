#include "account.h"
#include "ui_account.h"

Account::Account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);

    QPixmap *logo = new QPixmap("$/img/logo.png");
    ui->label->setPixmap(*logo);
}

Account::~Account()
{
    delete ui;
}

void Account::on_pushButton_clicked()
{
    this->hide();
}
