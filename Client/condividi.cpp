#include "condividi.h"
#include "ui_condividi.h"
#include <QKeyEvent>
#include <QProcess>
#include <QtWidgets/QMessageBox>
#include <regex>

Condividi::Condividi(QWidget *parent, QString s, CharacterClient *user) :
    QDialog(parent),
    ui(new Ui::Condividi)
{
    client = user;
    url = s;
    ui->setupUi(this);
    ui->url->setReadOnly(true);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    ui->url->setText(url);

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
    people=ui->condividiB->text();
    if(people == "")
    {
        QMessageBox::warning(this, "Condivisione", "Inserire uno o più nomi utente");
        return;
    }
    else
    {
        std::string delimiter = " ";
        std::string token;
        size_t pos =0;
        std::string s = (people.toStdString()+" ");

        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
//            std::cout << token << std::endl;
            if(token != "" && token != " ")
            {
                if (!is_email_valid(token)) {
                    QMessageBox::warning(this, "Condivisione", "Una o più email non sono valide");
                    return;
                }
            }
            s.erase(0, pos + delimiter.length());
        }

    }

    hide();
    emit share(people);

}

bool Condividi::is_email_valid(std::string s)
{
    // define a regular expression
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool fin;
    // try to match the string with the regular expression
    if((fin = std::regex_match(s, pattern))) {

    } else {

    }
    return fin;
}