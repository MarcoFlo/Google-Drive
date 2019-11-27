#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "account.h"
#include "ui_principale.h"
#include "nuovo.h"
#include "condividi.h"
#include "importa.h"
#include "principale.h"


Principale::Principale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principale)
{
    ui->setupUi(this);

    //ACCOUNT

    QMenu *accountM = new QMenu();
    QVBoxLayout *accountV = new QVBoxLayout(accountM);
    accountM->setLayout(accountV);
    accountV->setAlignment(Qt::AlignCenter);

    QLabel *icona = new QLabel(accountM);
    icona->setAlignment(Qt::AlignCenter);
    QPixmap *iconaP = new QPixmap(":/images/img/logo.png");
    icona->setPixmap(*iconaP);
    accountV->addWidget(icona);

    QLabel *nome = new QLabel(accountM);
    nome->setAlignment(Qt::AlignCenter);
    nome->setText("nome");
    accountV->addWidget(nome);

    QLabel *mail = new QLabel(accountM);
    mail->setAlignment(Qt::AlignCenter);
    mail->setText("mail");
    accountV->addWidget(mail);

    QPushButton *modifica = new QPushButton(accountM);
    modifica->setText("Impostazioni utente");
    accountV->addWidget(modifica);

    QPushButton *logout = new QPushButton(accountM);
    logout->setText("Logout");
    accountV->addWidget(logout);

    QObject::connect(modifica, SIGNAL(clicked()), this, SLOT(on_impostazioni_clicked()));
    QObject::connect(logout, SIGNAL(clicked()), this, SLOT(on_logout_clicked()));

    QToolButton *account = new QToolButton(this);

    QIcon *icon = new QIcon(":/images/img/logo.png");
    account->setIcon(*icon);
    account->setMenu(accountM);
    account->setPopupMode(QToolButton::InstantPopup);

    ui->horizontalLayout->insertWidget(3, account);

}

Principale::~Principale()
{
    delete ui;
}

void Principale::on_nuovo_clicked()
{
    Nuovo nuovo;
    nuovo.setModal(true);
    QObject::connect(&nuovo, SIGNAL(openE(QString)), this, SLOT(open_edi(QString)));
    nuovo.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    nuovo.exec();
}

void Principale::on_condividi_clicked()
{
    Condividi condividi;
    condividi.setModal(true);
    condividi.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    condividi.exec();
}


void Principale::on_scarica_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Salva con nome"), "C:/Users/gigiv/Downloads/untitled.pdf",
           tr("Adobe Acrobat Document (*.pdf);;Tutti i file (*.*)"));

    if (fileName.isEmpty())
            return;
    else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
                 }
        }
}

void Principale::on_importa_clicked()
{
    Importa importa;
    importa.setModal(true);
    importa.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    importa.exec();
}

void Principale::open_edi(QString name)
{
    hide();
    e=new Editor(this, name);
    QObject::connect(e, SIGNAL(closeE()), this, SLOT(on_closeE_signal()));
    QObject::connect(e, SIGNAL(closeEP()), this, SLOT(on_closeEP_signal()));
    e->show();
}

void Principale::on_closeE_signal()
{
    e->hide();
    this->show();
    delete e;
}

void Principale::on_impostazioni_clicked()
{
    Account account;
    account.setModal(true);
    account.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    account.exec();
}

void Principale::on_logout_clicked()
{
    emit closeP();
}

 void Principale::on_closeEP_signal()
{
     e->hide();
     this->show();
     delete e;
     on_logout_clicked();
}

void Principale::on_elimina_clicked()
{

}

void Principale::on_cerca_clicked()
{

}
