#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <sstream>
#include "account.h"
#include "ui_principale.h"
#include "nuovo.h"
#include "condividi.h"
#include "importa.h"
#include "principale.h"


Principale::Principale(QWidget *parent, CharacterClient *client) :
    QMainWindow(parent),
    client_(client),
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
    QObject::connect(ui->lista->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(on_row_select()));

    QToolButton *account = new QToolButton(this);

    QIcon *icon = new QIcon(":/images/img/logo.png");
    account->setIcon(*icon);
    account->setMenu(accountM);
    account->setPopupMode(QToolButton::InstantPopup);

    ui->horizontalLayout->insertWidget(3, account);

    ui->elimina->setDisabled(true);
    ui->condividi->setDisabled(true);
    ui->scarica->setDisabled(true);
    ui->lista->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStringList etichette;
    etichette << "#" << "Nome file" << "Data creazione" << "Proprietario" << "Ultima modifica";
    ui->lista->setColumnCount(5);
    ui->lista->setHorizontalHeaderLabels(etichette);

    connect(ui->lista, &QTableWidget::cellDoubleClicked, this, &Principale::cellDoubleClicked);

    insertTab();
}

Principale::~Principale()
{
    delete ui;
}

void Principale::on_nuovo_clicked()
{
    Nuovo nuovo;
    nuovo.setModal(true);
    QObject::connect(&nuovo, SIGNAL(openE(QString, QString)), this, SLOT(onNuovoReturn(QString, QString)));
    nuovo.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    nuovo.exec();
}

void Principale::on_condividi_clicked()
{
    Condividi condividi;
    condividi.setModal(true);
    condividi.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QObject::connect(&condividi, SIGNAL(share(QString)), this, SLOT(onCondividiReturn(QString)));
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

void Principale::open_edi(std::string name)
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
    insertTab();
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
    std::string error = client_->Logout();

    if (error == "")
        emit logout();
    else
        QMessageBox::warning(this, "Logout", "Logout service failed");
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
    QItemSelectionModel *selitem = ui->lista->selectionModel();
    int fileindex = selitem->selectedRows(NUM)[0].data().toInt();
    client_->RemoveFile(clientFiles_->fileil(fileindex));
    insertTab();
}

void Principale::on_cerca_clicked()
{
    int i=0;
    std::string cerca= ui->cercaBarra->text().toStdString();
    if(cerca =="")
    {
        insertTab();
    }
    else {
        std::list<int> search;
        search = client_->searchFileInfo(ui->cercaBarra->text().toStdString());

        ui->lista->clearContents();
        ui->lista->setRowCount(0);
        clientFiles_= new protobuf::FilesInfoList;
        protobuf::FileInfo fileInfo;

        if(client_->GetFiles() == "")
        {
            *clientFiles_ = client_->getFileInfoList();
        }

        for(std::list<int>::iterator it = search.begin(); it != search.end(); it++)
        {
            ui->lista->insertRow(ui->lista->rowCount());
            fileInfo = clientFiles_->fileil(*it);
            ui->lista->setItem(ui->lista->rowCount() - 1, NUM, new QTableWidgetItem(QString::number(*it)));
            ui->lista->setItem(ui->lista->rowCount() - 1, NAME, new QTableWidgetItem(QString::fromStdString(fileInfo.filename())));
            ui->lista->setItem(ui->lista->rowCount() - 1, SIZE, new QTableWidgetItem(fileInfo.size()));
            ui->lista->setItem(ui->lista->rowCount() - 1, PROP, new QTableWidgetItem(QString::fromStdString(fileInfo.usernameo())));
        }
    }
}

void Principale::closeEvent( QCloseEvent* event )
{
    emit closeP();
    event->accept();
}

void Principale::insertTab()
{
    ui->lista->clearContents();
    ui->lista->setRowCount(0);
    clientFiles_= new protobuf::FilesInfoList;
    protobuf::FileInfo fileInfo;
    int i=0;

    if(client_->GetFiles() == "")
    {
        *clientFiles_ = client_->getFileInfoList();
    }

    for(i=0; i < clientFiles_->fileil_size(); i++)
    {
        ui->lista->insertRow(ui->lista->rowCount());
        fileInfo = clientFiles_->fileil(i);
        ui->lista->setItem(ui->lista->rowCount() - 1, NUM, new QTableWidgetItem(QString::number(i)));
        ui->lista->setItem(ui->lista->rowCount() - 1, NAME, new QTableWidgetItem(QString::fromStdString(fileInfo.filename())));
        ui->lista->setItem(ui->lista->rowCount() - 1, SIZE, new QTableWidgetItem(fileInfo.size()));
        ui->lista->setItem(ui->lista->rowCount() - 1, PROP, new QTableWidgetItem(QString::fromStdString(fileInfo.usernameo())));
    }
}

void Principale::onNuovoReturn(QString name, QString share)
{
    protobuf::FileName fileName;
    std::string namefile = name.toStdString();
    fileName.set_filename(namefile.c_str());
    std::string fileid =client_->InsertFile(fileName);
    std::string delimiter = " ";
    std::string token;
    size_t pos =0;
    std::string s = (share.toStdString()+" ");

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        client_->ShareFile(fileid, token);
        s.erase(0, pos + delimiter.length());
    }

    open_edi(fileid);
}

void Principale::on_row_select()
{
    if(ui->lista->selectionModel()->hasSelection()) {
        ui->elimina->setEnabled(true);
        ui->condividi->setEnabled(true);
        ui->scarica->setEnabled(true);
    }
    else {
        ui->elimina->setEnabled(false);
        ui->condividi->setEnabled(false);
        ui->scarica->setEnabled(false);
    }
}

void Principale::onCondividiReturn(QString nomi)
{
    std::string delimiter = " ";
    std::string token;
    size_t pos =0;
    std::string s = (nomi.toStdString()+" ");
    QItemSelectionModel *selitem = ui->lista->selectionModel();
    int fileindex = selitem->selectedRows(NUM)[0].data().toInt();
    std::string file = clientFiles_->fileil(fileindex).fileidentifier();

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        client_->ShareFile(file, token);
        s.erase(0, pos + delimiter.length());
    }
    QMessageBox::information(this, "Condivisione completata", "La condivisione ha avuto successo");
}

void Principale::cellDoubleClicked() {
    QItemSelectionModel *selitem = ui->lista->selectionModel();
    int fileindex = selitem->selectedRows(NUM)[0].data().toInt();
    std::string file = clientFiles_->fileil(fileindex).fileidentifier();
    open_edi(file);
}