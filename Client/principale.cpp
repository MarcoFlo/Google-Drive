#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <sstream>
#include "principale.h"
#include "ui_principale.h"
#include <QCloseEvent>

Principale::Principale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principale)
{
    ui->setupUi(this);
    showSplash();
    setupUI();
    this->setEnabled(FALSE);
}

Principale::~Principale()
{
    delete ui;
}

void Principale::closeEvent( QCloseEvent* event )
{
    emit closeP();
    event->accept();
}

void Principale::setupUI()
{
    setWindowTitle("Just Wtite");
    QIcon *ic = new QIcon(":/images/img/logoVero.png");
    setWindowIcon(*ic);


    QPixmap *pixmap = new QPixmap(":/images/img/logoVero.png");
    ui->icona->setPixmap(*pixmap);
    

    auto *accountM = new QMenu();
    auto *accountV = new QVBoxLayout(accountM);
    accountM->setLayout(accountV);
    accountV->setAlignment(Qt::AlignCenter);
    accountM->setStyleSheet("background-color: white;"
                                      "border: 1px solid #336b8a;"
                                      "padding: 10px;");

    /*auto *icona = new QLabel(accountM);
    icona->setAlignment(Qt::AlignCenter);
    icona->setStyleSheet("border-radius: 12px;"
                                   "border: 1px white;"
                                   "padding: 10px;");*/

    nome = new QLabel(accountM);
    nome->setAlignment(Qt::AlignCenter);
    //QString s = client_->getNome().c_str();
    //s.append(" ");
    //s.append(client_->getCognome().c_str());
    //nome->setText(s);
    nome->setStyleSheet("color: #3a848a;"
                        "font-size: 15px;"
                        "border: none;"
                        "padding: 5px;"
                        "font-family: 'Calibri';"
                        "background-color:none");
    accountV->addWidget(nome);

    mail = new QLabel(accountM);
    mail->setAlignment(Qt::AlignCenter);
    mail->setStyleSheet("color: #3a848a;"
                        "font-size: 15px;"
                        "border: none;"
                        "padding: 5px;"
                        "font-family: 'Calibri';"
                        "background-color:none");
    accountV->addWidget(mail);

    auto *modifica = new QPushButton(accountM);
    modifica->setText("Impostazioni utente");
    modifica->setStyleSheet("QPushButton {"
                            "background-color:none;"
                            "border:2px solid #336b8a;"
                            "padding: 6px;"
                            "color: #336b8a;"
                            "font-size: 15px;"
                            "font-family: 'Calibri';"
                            "border-radius: 15px;}"
                            "QPushButton:hover {"
                            "background-color: #336b8a;"
                            "color:white;};");
    accountV->addWidget(modifica);

    auto *logout = new QPushButton(accountM);
    logout->setText("Logout");
    logout->setStyleSheet("QPushButton {"
                          "background-color:none;"
                          "border:2px solid #336b8a;"
                          "padding: 6px;"
                          "color: #336b8a;"
                          "font-size: 15px;"
                          "font-family: 'Calibri';"
                          "border-radius: 15px;}"
                          "QPushButton:hover {"
                          "background-color: #336b8a;"
                          "color:white;};");
    accountV->addWidget(logout);

    QObject::connect(modifica, SIGNAL(clicked()), this, SLOT(on_impostazioni_clicked()));
    QObject::connect(logout, SIGNAL(clicked()), this, SLOT(on_logout_clicked()));
    QObject::connect(ui->lista->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(on_row_select()));

    accountT = new QToolButton(this);

    accountT->setStyleSheet("QToolButton::menu-indicator {"
                           "image: none;}"
                           "QToolButton {"
                           "border: 1px solid white;}");

    //auto *icon = new QIcon(":/images/img/logovero.png");
    //accountT->setIcon(*icon);
    accountT->setMenu(accountM);
    accountT->setPopupMode(QToolButton::InstantPopup);

    ui->horizontalLayout->insertWidget(3, accountT);

     /*ui->elimina->setStyleSheet("::disabled {border-radius: 12px;"
                                "                               background-color: #8395a7;"
                                "                               padding: 6px;"
                                "                               color: #dfe6e9;"
                                "                               border: none;"
                                "                               font-size: 15px;"
                                "                               font-family: 'Calibri';}");



    ui->condividi->setStyleSheet("::disabled {border-radius: 12px;"
                               "                               background-color: #8395a7;"
                               "                               padding: 6px;"
                               "                               color: #dfe6e9;"
                               "                               border: none;"
                               "                               font-size: 15px;"
                               "                               font-family: 'Calibri';}");


    ui->scarica->setStyleSheet("::disabled {border-radius: 12px;"
                               "                               background-color: #8395a7;"
                               "                               padding: 6px;"
                               "                               color: #dfe6e9;"
                               "                               border: none;"
                               "                               font-size: 15px;"
                               "                               font-family: 'Calibri';}");*/


    /*ui->nuovo->setStyleSheet("::disabled {border-radius: 12px;"
                               "                               background-color: #8395a7;"
                               "                               padding: 6px;"
                               "                               color: #dfe6e9;"
                               "                               border: none;"
                               "                               font-size: 15px;"
                               "                               font-family: 'Calibri';}");


    ui->importa->setStyleSheet("::disabled {border-radius: 12px;"
                               "                               background-color: #8395a7;"
                               "                               padding: 6px;"
                               "                               color: #dfe6e9;"
                               "                               border: none;"
                               "                               font-size: 15px;"
                               "                               font-family: 'Calibri';}");*/

    ui->elimina->setDisabled(true);
    ui->condividi->setDisabled(true);
    ui->scarica->setDisabled(true);

    ui->lista->setSelectionBehavior(QAbstractItemView::SelectRows);
    QStringList etichette;
    /*ui->lista->setStyleSheet("background-color: #dfe6e9;"
                             "color: #3c6382;"
                             "font-family: 'Calibri';"
                             "font-size: 12px;");
    
    etichette << "#" << "Nome file" << "Data creazione" << "Proprietario" << "Ultima modifica";
    ui->lista->setColumnCount(5);
    ui->lista->setHorizontalHeaderLabels(etichette);*/

    connect(ui->lista, &QTableWidget::cellDoubleClicked, this, &Principale::cellDoubleClicked);
    connect(ui->lista, &QTableWidget::cellClicked, this, &Principale::cellClicked);

    ui->annullaCerca->setVisible(false);
}

void Principale::on_nuovo_clicked()
{
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }

    nuovo = new Nuovo(this, client_);
    //nuovo->setModal(true);
    QObject::connect(nuovo, SIGNAL(openE(QString, QString)), this, SLOT(onNuovoReturn(QString, QString)));
    //nuovo->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    nuovo->show();
}

void Principale::on_condividi_clicked()
{
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    condividi = new Condividi(this, link, client_);
    //condividi.setModal(true);
    //condividi.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QObject::connect(condividi, SIGNAL(share(QString)), this, SLOT(onCondividiReturn(QString)));
    condividi->show();
}


void Principale::on_scarica_clicked()
{
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
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
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    Importa importa;
    importa.setModal(true);
    importa.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    QObject::connect(&importa, SIGNAL(import(QString)), this, SLOT(onImportaReturn(QString)));
    importa.exec();
}

void Principale::on_impostazioni_clicked()
{
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    account = new Account(this, client_);
    //account.setUser(client_);
    //account->setModal(true);
    //account->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    account->show();
}

void Principale::on_logout_clicked()
{
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    accountT->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    std::string error = client_->Logout();
    ui->lista->clearContents();
    if (error.empty()) {
        login = new LoginPage(this);
        QObject::connect(login, SIGNAL(clientReturn(CharacterClient * )), this,
                         SLOT(onLoginReturn(CharacterClient * )));
        QObject::connect(login, SIGNAL(regRequest()), this, SLOT(onRegistrationRequest()));
        login->show();
        this->setEnabled(false);
        login->setEnabled(true);
    }
    else
        QMessageBox::warning(this, "Logout", "Logout service failed");
}

void Principale::on_elimina_clicked()
{
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    QItemSelectionModel *selitem = ui->lista->selectionModel();
    int fileindex = selitem->selectedRows(NUM)[0].data().toInt();
    client_->RemoveFile(clientFiles_->fileil(fileindex));
    insertTab();
}

void Principale::on_cerca_clicked()
{
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    std::string cerca= ui->cercaBarra->text().toStdString();
    if(cerca.empty())
    {
        insertTab();
        ui->annullaCerca->setVisible(false);
    }
    else {
        ui->annullaCerca->setVisible(true);
        std::list<int> search;
        search = client_->searchFileInfo(ui->cercaBarra->text().toStdString());

        ui->lista->clearContents();
        ui->lista->setRowCount(0);
        clientFiles_= new protobuf::FilesInfoList;
        protobuf::FileInfo fileInfo;

        if(client_->GetFiles().empty())
        {
            *clientFiles_ = client_->getFileInfoList();
        }

        for(std::_List_iterator<std::_List_val<std::_List_simple_types<int> > >::value_type & it : search)
        {
            ui->lista->insertRow(ui->lista->rowCount());
            fileInfo = clientFiles_->fileil(it);
            ui->lista->setItem(ui->lista->rowCount() - 1, NUM, new QTableWidgetItem(QString::number(it)));
            ui->lista->setItem(ui->lista->rowCount() - 1, NAME, new QTableWidgetItem(QString::fromStdString(fileInfo.filename())));
            ui->lista->setItem(ui->lista->rowCount() - 1, SIZE, new QTableWidgetItem(fileInfo.size()));
            ui->lista->setItem(ui->lista->rowCount() - 1, PROP, new QTableWidgetItem(QString::fromStdString(fileInfo.emailo())));
        }
    }
}

void Principale::cellDoubleClicked() {
    QItemSelectionModel *selitem = ui->lista->selectionModel();
    int fileindex = selitem->selectedRows(NUM)[0].data().toInt();
    std::string file = clientFiles_->fileil(fileindex).fileidentifier();
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    open_edi(&file);
}

void Principale::cellClicked()
{
    QItemSelectionModel *selitem = ui->lista->selectionModel();
    int fileindex = selitem->selectedRows(NUM)[0].data().toInt();
    std::string fileind = clientFiles_->fileil(fileindex).fileidentifier();
    protobuf::FileInfo *file_ = new protobuf::FileInfo();
    *file_ = client_->getFileInfo(fileind);
    ui->proprietarioL->setText("");
    ui->proprietarioL->setText(QString::fromStdString(file_->emailo()));
    ui->dataL->setText("");
    ui->dataL->setText(QString::fromStdString(file_->date()));
    link = QString::fromStdString(file_->fileidentifier());
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    /*if(file_->emailal_size() == 0)
    {
        QMessageBox::warning(this, "bla", "non c'è nulla");
    }*/
    for(int i = 0; i < file_->emailal_size(); i++)
    {
        QLabel *item = new QLabel(this);
        item->setStyleSheet("color: black;"
                            "font-size: 12px;"
                            "font-family: 'Calibri';"
                            "background-color:none;");
        item->setText(file_->emailal(i).c_str());
        item->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        ui->verticalLayout_4->addWidget(item);

    }
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

void Principale::on_closeE_signal()
{
    e->hide();
    this->show();
    delete e;
    insertTab();
}

void Principale::on_closeEP_signal()
{
    e->hide();
    this->show();
    delete e;
    on_logout_clicked();
}

void Principale::open_edi(std::string *name)
{
    hide();
    e=new Editor(this, name, client_);
    QObject::connect(e, SIGNAL(closeE()), this, SLOT(on_closeE_signal()));
    QObject::connect(e, SIGNAL(closeEP()), this, SLOT(on_closeEP_signal()));
    e->show();
}

void Principale::insertTab()
{
    ui->lista->clearContents();
    ui->lista->setRowCount(0);
    clientFiles_= new protobuf::FilesInfoList;
    protobuf::FileInfo fileInfo;
    int i=0;

    if(client_->GetFiles().empty())
    {
        *clientFiles_ = client_->getFileInfoList();
    } else {
        *clientFiles_ = client_->getFileInfoList();
    }

    for(i=0; i < clientFiles_->fileil_size(); i++)
    {
        ui->lista->insertRow(ui->lista->rowCount());
        fileInfo = clientFiles_->fileil(i);
        ui->lista->setItem(ui->lista->rowCount() - 1, NUM, new QTableWidgetItem(QString::number(i)));
        ui->lista->setItem(ui->lista->rowCount() - 1, NAME, new QTableWidgetItem(QString::fromStdString(fileInfo.filename())));
        ui->lista->setItem(ui->lista->rowCount() - 1, SIZE, new QTableWidgetItem(fileInfo.size()));
        ui->lista->setItem(ui->lista->rowCount() - 1, PROP, new QTableWidgetItem(QString::fromStdString(fileInfo.emailo())));
    }
}

void Principale::onNuovoReturn(QString name, QString share)
{
    /*std::list<int> search;
    search = client_->searchFileInfo(name.toStdString());
    if(search.empty() == false)
    {
        QMessageBox::warning(this,"Creazione", "Esiste già un documento con questo nome");
        search.clear();
        return;
    }*/

    protobuf::FileName fileName;
    std::string namefile = name.toStdString();
    fileName.set_filename(namefile.c_str());
    std::string fileid =client_->InsertFile(fileName);

    if(share.compare("") != 0)
    {
        std::string delimiter = " ";
        std::string token;
        size_t pos =0;
        std::string s = (share.toStdString()+" ");

        while ((pos = s.find(delimiter)) != std::string::npos && s != " ") {
            token = s.substr(0, pos);
            if(token != "" && token != " ")
            {
                client_->ShareFile(fileid, token);
            }
            s.erase(0, pos + delimiter.length());
        }
    }

    open_edi(&fileid);
}

void Principale::onCondividiReturn(const QString nomi)
{
    if(nomi.isEmpty())
        return;
    std::string delimiter = " ";
    std::string token;
    size_t pos =0;
    std::string s = (nomi.toStdString()+" ");
    QItemSelectionModel *selitem = ui->lista->selectionModel();
    int fileindex = selitem->selectedRows(NUM)[0].data().toInt();
    std::string file = clientFiles_->fileil(fileindex).fileidentifier();

    while ((pos = s.find(delimiter)) != std::string::npos && s != " ") {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        if(token != "" && token != " ")
        {
            client_->ShareFile(file, token);
        }
        s.erase(0, pos + delimiter.length());
    }
    QMessageBox::information(this, "Condivisione completata", "La condivisione ha avuto successo");
}

void Principale::onImportaReturn(const QString link)
{
    for(int i = 0; i < clientFiles_->fileil_size(); i++)
    {
        if(clientFiles_->fileil(i).fileidentifier() == link.toStdString())
        {
            QMessageBox::warning(this, "Import", "Il documento è già stato importato");
            return;
        }
    }

    std::string error = client_->ImportFile(link.toStdString());

    if (error.empty()) {   // status == ok
        QMessageBox::information(this, "Import", "Il documento è stato importato correttamente");
        insertTab();
    } else {
        QMessageBox::warning(this, "Import", "Il documento associato al link non è stato trovato");
    }
}

void Principale::onLoginReturn(CharacterClient* cli)
{
    client_=cli;
    userLogged = client_->getProfileInfoLogged();
    delete login;
    insertTab();
    nome->setText(QString::fromStdString(userLogged.name()));
    mail->setText(QString::fromStdString(userLogged.user().email()));
    accountT->setText(QString::fromStdString(userLogged.username()));
    accountT->setStyleSheet("QToolButton::menu-indicator {"
                            "image: none;}"
                            "QToolButton {"
                            "border: 1px solid white;"
                            "color: white;"
                            "font-size: 17px; "
                            "text-align: center}");

    this->setEnabled(TRUE);
}

void Principale::onRegistrationRequest()
{
    regist=new RegistrationPage(this);
    QObject::connect(regist, SIGNAL(closeR()), this, SLOT(on_closeReg_signal()));
    QObject::connect(regist, SIGNAL(closeRReg()), this, SLOT(on_closeRReg_signal()));
    regist->show();
}

void Principale::on_closeReg_signal() {
    delete regist;
    login->show();
}

void Principale::on_closeRReg_signal() {
    delete regist;
    login->on_closeRReg_signal();
}

void Principale::showSplash() {
    splash = new SplashScreen(this);
    splash->show();
    QTimer::singleShot(2000, this, SLOT(closeSplash()));
}

void Principale::closeSplash() {
    splash->hide();
    delete splash;
    login = new LoginPage(this);
    QObject::connect(login, SIGNAL(clientReturn(CharacterClient*)), this, SLOT(onLoginReturn(CharacterClient*)));
    QObject::connect(login, SIGNAL(regRequest()), this, SLOT(onRegistrationRequest()));
    login->show();
}

void Principale::on_annullaCerca_clicked()
{
    ui->proprietarioL->setText("");
    ui->dataL->setText("");
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout_4->takeAt(0)) != 0)
    {
        //delete wItem;
        delete wItem->widget();
    }
    ui->cercaBarra->setText("");
    on_cerca_clicked();
}
