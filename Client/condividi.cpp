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
        QMessageBox::warning(this, "Condivisione", "Inserire dei nomi utente");
    }
    else if(!is_email_valid())
    {
        QMessageBox::warning(this, "Condivisione", "Inserire email valida");
    }
    else
    {
        hide();
        emit share(people);

    }

}

bool Condividi::is_email_valid()
{
    // define a regular expression
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool fin;
    // try to match the string with the regular expression
    if((fin = std::regex_match(people.toStdString(), pattern))) {

    } else {

    }
    return fin;
}