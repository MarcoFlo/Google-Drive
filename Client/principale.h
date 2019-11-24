#ifndef PRINCIPALE_H
#define PRINCIPALE_H

#include <QMainWindow>
#include "nuovo.h"
#include "condividi.h"

#include <iostream>
#include <thread>
#include <sstream>
#include <fstream>

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

signals:
    void openL();
    void openE();

private slots:
    void on_nuovo_clicked();

    void on_condividi_clicked();

    void Mostra();

    void on_scarica_clicked();

    void on_importa_clicked();

    void open_edi();

private:
    Ui::Principale *ui;

    /* client stuff */
    std::string session_id;

};

#endif // PRINCIPALE_H
