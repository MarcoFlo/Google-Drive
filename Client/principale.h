#ifndef PRINCIPALE_H
#define PRINCIPALE_H

#include <QMainWindow>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"
#include "registrationpage.h"
#include "account.h"
#include "nuovo.h"
#include "condividi.h"
#include "importa.h"
#include "editor.h"
#include "loginpage.h"
#include "splashscreen.h"

namespace Ui {
class Principale;
}

class Principale : public QMainWindow
{
    Q_OBJECT

public:
    explicit Principale(QWidget *parent = nullptr);

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
    void clientReturn(CharacterClient*);
    void regRequest();
    void closeR();
    void closeRReg();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void setupUI();

    void on_nuovo_clicked();

    void on_condividi_clicked();

    void on_scarica_clicked();

    void on_importa_clicked();

    void on_impostazioni_clicked();

    void on_logout_clicked();

    void on_elimina_clicked();

    void on_cerca_clicked();

    void cellDoubleClicked();

    void on_row_select();

    void on_closeE_signal();

    void on_closeEP_signal();

    void open_edi(std::string*);

    void insertTab();

    void onNuovoReturn(QString, QString);

    void onCondividiReturn(const QString);

    void onLoginReturn(CharacterClient*);

    void onRegistrationRequest();

    void on_closeRReg_signal();

    void on_closeReg_signal();

    void showSplash();

    void closeSplash();

private:
    Ui::Principale *ui;

    Editor *e;

    LoginPage *login;

    RegistrationPage *regist;

    SplashScreen *splash;

    CharacterClient *client_;

    enum columnEti
    {
        NUM, NAME, SIZE, PROP, LAST
    };

    protobuf::FilesInfoList *clientFiles_;

};

#endif // PRINCIPALE_H
