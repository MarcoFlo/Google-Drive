#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>
//#include "comunication/CharacterClient.h"
//#include "messageP.grpc.pb.h"
//#include <grpcpp/grpcpp.h>

namespace Ui {
class Account;
}

class Account : public QDialog
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    ~Account();
    //void setUser(CharacterClient *user_);
    bool is_email_valid();
    bool is_pass_valid();
    bool is_something_empty();

private slots:
    void on_pushButton_clicked();



private:
    Ui::Account *ui;

    //CharacterClient *client_;
};

#endif // ACCOUNT_H
