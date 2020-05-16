#ifndef NUOVO_H
#define NUOVO_H

#include <QDialog>
//#include "comunication/CharacterClient.h"

namespace Ui {
class Nuovo;
}

class Nuovo : public QDialog
{
    Q_OBJECT

public:
    explicit Nuovo(QWidget *parent = nullptr);
    ~Nuovo();
    //void Nuovo::setClient(CharacterClient* cli);

signals:
    void openE(QString, QString);

private slots:
    void on_Annulla_clicked();

    void on_conferma_clicked();



private:
    Ui::Nuovo *ui;
    //CharacterClient *client;
};

#endif // NUOVO_H
