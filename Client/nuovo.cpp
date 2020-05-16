#include "nuovo.h"
#include "ui_nuovo.h"
#include <QMessageBox>
//#include "comunication/CharacterClient.h"

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
/*void Nuovo::setClient(CharacterClient* cli)
{
    client = cli;
}*/
void Nuovo::on_Annulla_clicked()
{

    this->hide();
    //parent->attivo(true);
}
void Nuovo::on_conferma_clicked()
{
    QString name = ui->nome->text();
    QString share = ui->cond->text();

    if(name.compare("")==0)
    {
        QMessageBox::warning(this,"Creazione", "Inserire il nome del documento da creare");
    }
    //else {
      //  std::list<int> cli;
        //cli = client->searchFileInfo(name.toStdString());

        /*(cli.empty() == false)
        {
            QMessageBox::warning(this,"Creazione", "Esiste già un documento con questo nome");
        }
        else
        {*/
            //cli.clear();
            hide();
            emit openE(name, share);
        //}

    //}
}
