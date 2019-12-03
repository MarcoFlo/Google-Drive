#ifndef PRINCIPALE_H
#define PRINCIPALE_H

#include <QMainWindow>
#include "nuovo.h"
#include "condividi.h"
#include "editor.h"
#include "account.h"
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"

namespace Ui {
class Principale;
}

class Principale : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principale(QWidget *parent = nullptr, QString token = nullptr, CharacterClient *client);

    ~Principale();

    void abilita(bool s);

signals:
    void closeE();
    void openE(QString);
    void closeP();
    void closeEP();

private slots:
    void on_nuovo_clicked();

    void on_condividi_clicked();

    void on_scarica_clicked();

    void on_importa_clicked();

    void open_edi(QString name);

    void on_closeE_signal();

    void on_impostazioni_clicked();

    void on_logout_clicked();

    void on_closeEP_signal();

    void on_elimina_clicked();

    void on_cerca_clicked();

private:
    Ui::Principale *ui;

    Editor *e;

    QString token_;

    CharacterClient *client_;

};

#endif // PRINCIPALE_H
