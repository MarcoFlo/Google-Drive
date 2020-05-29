#ifndef CONDIVIDI_H
#define CONDIVIDI_H

#include <QDialog>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"

namespace Ui {
class Condividi;
}

class Condividi : public QDialog
{
    Q_OBJECT

public:
    explicit Condividi(QWidget *parent = nullptr, QString s = nullptr, CharacterClient *user = nullptr);
    ~Condividi();
    bool is_email_valid();

signals:
    void share(QString);

private slots:
    void on_annulla_clicked();

    void on_copia_clicked();

    void on_conferma_clicked();

private:
    Ui::Condividi *ui;
    QString people;
    CharacterClient *client;
    QString url;
};

#endif // CONDIVIDI_H
