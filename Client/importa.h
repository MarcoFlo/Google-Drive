#ifndef IMPORTA_H
#define IMPORTA_H

#include <QDialog>

namespace Ui {
class Importa;
}

class Importa : public QDialog
{
    Q_OBJECT

public:
    explicit Importa(QWidget *parent = nullptr);
    ~Importa();

signals:
    void import(QString);

private slots:
    void on_incolla_clicked();

    void on_annulla_clicked();

    void on_conferma_clicked();

private:
    Ui::Importa *ui;
};

#endif // IMPORTA_H
