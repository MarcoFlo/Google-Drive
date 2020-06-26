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
        } else {

            if (share.compare("") != 0) {

                std::string delimiter = " ";
                std::string token;
                size_t pos = 0;
                std::string s = (share.toStdString() + " ");

                while ((pos = s.find(delimiter)) != std::string::npos) {
                    token = s.substr(0, pos);
//                    std::cout << token << std::endl;
                    if (token != "" && token != " ") {
                        if (!is_email_valid(token)) {
                            QMessageBox::warning(this, "Creazione", "Una o più email non sono valide");
                            return;
                        }
                    }
                    s.erase(0, pos + delimiter.length());
                }

                this->hide();
                emit openE(name, share);

            } else {

                this->hide();
                emit openE(name, share);
            }
        }
    }

}

bool Nuovo::is_email_valid(std::string s)
{
    // define a regular expression
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool fin;
    // try to match the string with the regular expression
    fin = std::regex_match(s, pattern);

    return fin;
}