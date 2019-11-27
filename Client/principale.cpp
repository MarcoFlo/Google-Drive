#include "principale.h"
#include "ui_principale.h"
#include "nuovo.h"
#include "condividi.h"
#include "importa.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

Principale::Principale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principale)
{
    ui->setupUi(this);
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
    e->show();
}

void Principale::on_closeE_signal()
{
    e->hide();
    this->show();
    delete e;
}
