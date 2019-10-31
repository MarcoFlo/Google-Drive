#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

namespace Ui {
class Editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

signals:
    void openP();

private slots:
        void Mostra();

        void on_actionindietro_triggered();

        void on_actionredo_triggered();

        void on_actioncopia_triggered();

        void on_actionincolla_triggered();

        void on_actiontaglia_triggered();

        void on_actionundo_triggered();

        void on_actionallineaD_triggered();

        void on_actionallineaS_triggered();

        void on_actionallineaC_triggered();

        void on_actionalineaG_triggered();

        void on_actiongrassetto_triggered();

        void on_actioncorsivo_triggered();

        void on_actionsottolineato_triggered();

private:
    Ui::Editor *ui;

};

#endif // EDITOR_H
