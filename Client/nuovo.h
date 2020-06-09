#ifndef NUOVO_H
#define NUOVO_H

#include <QDialog>
#include "messageP.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "comunication/CharacterClient.h"
#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

namespace Ui {
class Nuovo;
}

class Nuovo : public QDialog
{
    Q_OBJECT

public:
    explicit Nuovo(QWidget *parent = nullptr, CharacterClient *user = nullptr);
    ~Nuovo();
    bool is_email_valid(std::string s);


signals:
    void openE(QString, QString);

private slots:
    void on_Annulla_clicked();

    void on_conferma_clicked();


private:
    Ui::Nuovo *ui;
    CharacterClient *client;
    QString share;
};

#endif // NUOVO_H
