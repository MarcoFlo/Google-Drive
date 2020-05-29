#include "nuovo.h"
#include "ui_nuovo.h"
#include <QMessageBox>
#include <regex>
#include <QDebug>
#include <sstream>
#include "principale.h"
#include "ui_principale.h"
#include <QCloseEvent>

Nuovo::Nuovo(QWidget *parent, CharacterClient *user) :
    QDialog(parent),
    ui(new Ui::Nuovo)
{
    client = user;
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
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
    share = ui->cond->text();

    if(name.compare("")==0)
    {
        QMessageBox::warning(this,"Creazione", "Inserire il nome del documento da creare");
    }
    else {
        std::list<int> cli;
        cli = client->searchFileInfo(name.toStdString());

        if (cli.empty() == false) {
            cli.clear();
            QMessageBox::warning(this, "Creazione", "Esiste già un documento con questo nome");
        }
        else {

            if (share.compare("") != 0) {

                if (!is_email_valid()) {
                    //aggiungere per email separate da spazio
                    QMessageBox::warning(this, "Creazione", "Email non valida");
                } else{

                    this->hide();
                    emit openE(name, share);
                }
            } else{

                this->hide();
                emit openE(name, share);
            }
        }
    }


}

bool Nuovo::is_email_valid()
{
    // define a regular expression
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool fin;
    // try to match the string with the regular expression
    fin = std::regex_match(share.toStdString(), pattern);

    return fin;
}