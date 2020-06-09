#include "importa.h"
#include "ui_importa.h"

Importa::Importa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Importa)
{
    ui->setupUi(this);
}

Importa::~Importa()
{
    delete ui;
}

void Importa::on_incolla_clicked()
{
    ui->linkB->paste();
}

void Importa::on_annulla_clicked()
{
    this->hide();
}

void Importa::on_conferma_clicked()
{
    this->hide();
    emit import(ui->linkB->text());
}