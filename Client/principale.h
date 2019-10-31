#ifndef PRINCIPALE_H
#define PRINCIPALE_H

#include <QMainWindow>
#include "nuovo.h"
#include "condividi.h"

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

private:
    Ui::Principale *ui;

};

#endif // PRINCIPALE_H
