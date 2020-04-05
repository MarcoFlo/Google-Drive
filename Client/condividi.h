#ifndef CONDIVIDI_H
#define CONDIVIDI_H

#include <QDialog>

namespace Ui {
class Condividi;
}

class Condividi : public QDialog
{
    Q_OBJECT

public:
    explicit Condividi(QWidget *parent = nullptr);
    ~Condividi();

signals:
    void share(QString);

private slots:
    void on_annulla_clicked();

    void on_copia_clicked();

    void on_conferma_clicked();

private:
    Ui::Condividi *ui;
};

#endif // CONDIVIDI_H
