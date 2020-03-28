#include "nuovo.h"
#include "ui_nuovo.h"
#include <QMessageBox>

Nuovo::Nuovo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Nuovo)
{
    ui->setupUi(this);

}

Nuovo::~Nuovo()
{
    delete ui;
}

void Nuovo::on_Annulla_clicked()
{

    this->hide();
    //parent->attivo(true);
}
void Nuovo::on_conferma_clicked()
{
    QString name = ui->nome->text();

    if(name.compare("")==0)
    {
        //QMessageBox::warning(this,"Creazione", "Inserire il nome del documento da creare");
        hide();
        emit openE("gisella");
    }
    else {
        hide();
        emit openE(name);
    }
}
