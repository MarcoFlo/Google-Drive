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
    explicit Principale(QWidget *parent = nullptr, CharacterClient *client = nullptr);

    ~Principale();

    void abilita(bool s);

    // override
//    void closeEvent( QCloseEvent* event );

signals:
    void closeE();
    void openE(QString, QString);
    void closeP();
    void closeEP();
    void logout();
    void share(QString);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_nuovo_clicked();

    void on_condividi_clicked();

    void on_scarica_clicked();

    void on_importa_clicked();

    void open_edi(std::string);

    void on_closeE_signal();

    void on_impostazioni_clicked();

    void on_logout_clicked();

    void on_closeEP_signal();

    void on_elimina_clicked();

    void on_cerca_clicked();

    void insertTab();

    void onNuovoReturn(QString, QString);

    void on_row_select();

    void onCondividiReturn(QString);

    void cellDoubleClicked();

private:
    Ui::Principale *ui;

    Editor *e;

    CharacterClient *client_;

    enum columnEti
    {
        NUM, NAME, SIZE, PROP, LAST
    };

    protobuf::FilesInfoList *clientFiles_;

};

#endif // PRINCIPALE_H
