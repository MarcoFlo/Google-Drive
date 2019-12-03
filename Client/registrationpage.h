#ifndef REGISTRATIONPAGE_H
#define REGISTRATIONPAGE_H

#include <QMainWindow>
//#include "principale.h" -> circular inclusion!


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
    void openL();
    void openP();

private slots:
    void on_annulla_clicked();

    void on_registrati_clicked();

    void Mostra();

private:
    Ui::RegistrationPage *ui;

};

#endif // REGISTRATIONPAGE_H
