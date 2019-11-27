#ifndef PRINCIPALE_H
#define PRINCIPALE_H

#include <QMainWindow>
#include "nuovo.h"
#include "condividi.h"
#include "editor.h"

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
    void closeE();
    void openE(QString);

private slots:
    void on_nuovo_clicked();

    void on_condividi_clicked();

    void on_scarica_clicked();

    void on_importa_clicked();

    void open_edi(QString name);

    void on_closeE_signal();

private:
    Ui::Principale *ui;

    Editor *e;

};

#endif // PRINCIPALE_H
