#include "scarica.h"
#include "ui_scarica.h"

Scarica::Scarica(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Scarica)
{
    ui->setupUi(this);
}

Scarica::~Scarica()
{
    delete ui;
}
