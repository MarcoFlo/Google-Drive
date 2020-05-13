#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QMainWindow>
#include <QMessageBox>
#include <messageP.pb.h>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"

namespace Ui {
class RegistrationPage;
}

class RegistrationPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationPage(QWidget *parent = nullptr);
    ~RegistrationPage();

signals:
    void closeR();
    void closeRReg();

private slots:
    void on_annulla_clicked();

    void on_registrati_clicked();

    bool is_email_valid();

    bool is_pass_valid();

    bool is_something_empty();

private:
    Ui::RegistrationPage *ui;

    CharacterClient *client_;

};


#endif // REGISTRATIONPAGE_H
