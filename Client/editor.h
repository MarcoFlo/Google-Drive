#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QToolButton>
#include <QList>
#include <QMenu>
#include <QLineEdit>
#include <QPushButton>

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

        void on_actioncolore_triggered();

        void on_actionfont_triggered();

        void ShowContextMenu(const QPoint &);

        void checkFont();

        void changeDim();

        void changeFont();

        void changeZoom();

        void changeColor();

        void setTextFont(QFont *font);

        void setTextDim(int dim);

        void setTextDimEdit();

        void on_verticalScrollBar_sliderMoved(int position);

        void on_txt_cursorPositionChanged();

        void resizeEvent(QResizeEvent* event);

private:
    Ui::Editor *ui;

    QMenu *dimMenu;

    QList <QAction*> listaDim;

    QToolButton *dim;

    QActionGroup *dimG;

    QMenu *fontMenu;

    QToolButton *font;

    QList <QAction*> listaFont;

    QActionGroup *fontG;

    QLineEdit *lEdit;

    QMenu *zoomMenu;

    QActionGroup *zoomG;

    QToolButton *zoom;

    QList <QPushButton*> listaColor;

    QToolButton *colore;

};

#endif // EDITOR_H
