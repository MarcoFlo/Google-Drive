#ifndef NUOVO_H
#define NUOVO_H

#include <QDialog>

namespace Ui {
class Nuovo;
}

class Nuovo : public QDialog
{
    Q_OBJECT

public:
    explicit Nuovo(QWidget *parent = nullptr);
    ~Nuovo();

signals:
    void openE(QString, QString);

private slots:
    void on_Annulla_clicked();

    void on_conferma_clicked();

private:
    Ui::Nuovo *ui;

};

#endif // NUOVO_H
