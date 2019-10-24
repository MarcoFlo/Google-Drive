#ifndef SCARICA_H
#define SCARICA_H

#include <QDialog>

namespace Ui {
class Scarica;
}

class Scarica : public QDialog
{
    Q_OBJECT

public:
    explicit Scarica(QWidget *parent = nullptr);
    ~Scarica();

private:
    Ui::Scarica *ui;
};

#endif // SCARICA_H
