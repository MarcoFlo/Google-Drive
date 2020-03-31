#include "condividi.h"
#include "ui_condividi.h"
#include <QKeyEvent>
#include <QProcess>

Condividi::Condividi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Condividi)
{
    ui->setupUi(this);
    ui->url->setReadOnly(true);

}

Condividi::~Condividi()
{
    delete ui;
}

void Condividi::on_annulla_clicked()
{
    this->hide();
}

void Condividi::on_copia_clicked()
{
    ui->url->selectAll();
    ui->url->copy();

}

void Condividi::on_conferma_clicked()
{
    hide();
    emit share(ui->condividiB->text());
}
