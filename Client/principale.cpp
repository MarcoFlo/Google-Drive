#include "principale.h"
#include "ui_principale.h"
#include "nuovo.h"
#include "condividi.h"
#include "importa.h"
#include <QFileDialog>
#include <QMessageBox>

#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"
#include "comunication/SharedEditor.h"
#include "comunication/AsyncClientGetSymbols.h"

void read(const std::string &filename, std::string &data) {
    std::ifstream file(filename.c_str(), std::ios::in);

    if (file.is_open()) {
        std::stringstream ss;
        ss << file.rdbuf();
        file.close();
        data = ss.str();
    }
}

Principale::Principale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Principale)
{
    ui->setupUi(this);

    // client initialization
    //
    std::string serverCert;
    read("../../certs/server.cert", serverCert);
    grpc::SslCredentialsOptions opts;
    opts.pem_root_certs = serverCert;
    auto channel_creds = grpc::SslCredentials(opts);
    client_ = new CharacterClient(grpc::CreateChannel("localhost:50051", channel_creds));

}

Principale::~Principale()
{
    delete ui;
}

/**
 * ********************************************************************************************
 *                                      INIT FUNCTIONS
 *  *******************************************************************************************
 */

/**
 * @brief MainWindow::initConnectDialog
 */
void Principale::initLogin()
{
    l = new LoginPage(client_);
    //l->setModal(true);    // after loginPage becomes a dialog

    connect(this->l, SIGNAL(loginSuccess(QString)),
            this, SLOT(on_loginEstablished(QString)));

}


/**
 *  ********************************************************************************************
 *                                      PRIVATE SLOTS
 *  ********************************************************************************************
 */

void Principale::on_nuovo_clicked()
{
    Nuovo nuovo;
    QString doc;
    nuovo.setModal(true);
    QObject::connect(&nuovo, SIGNAL(openE()), this, SLOT(open_edi()));
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

void Principale::Mostra()
{
    show();
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

/**
 *
 */
void Principale::open_edi()
{
    hide();
    emit openE();
}
