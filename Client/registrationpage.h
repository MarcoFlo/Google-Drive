#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QMainWindow>
#include "principale.h"

namespace Ui {
class RegistrationPage;
}

class RegistrationPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationPage(QWidget *parent = nullptr, CharacterClient *client = nullptr);
    ~RegistrationPage();

signals:
    void closeR();
    void closeRReg();

private slots:
    void on_annulla_clicked();

    void on_registrati_clicked();

private:
    Ui::RegistrationPage *ui;

    CharacterClient *client_;

};


#endif // REGISTRATIONPAGE_H
