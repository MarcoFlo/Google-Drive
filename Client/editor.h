#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include <QToolButton>
#include <QList>
#include <QMenu>
#include <QLineEdit>
#include <QPushButton>
#include <grpcpp/grpcpp.h>
#include "messageP.grpc.pb.h"
#include "comunication/CharacterClient.h"
#include "comunication/Symbol.h"
#include <QList>

namespace Ui {
class Editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr, std::string *fileid=nullptr, CharacterClient *client=nullptr);
    ~Editor();

signals:
    void closeE();

    void closeEP();

    void newAsync();

private slots:

        void setupGeneral();

        //void setupAccount();

        void setupFont();

        void setupSize();

        void setupColor();

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

        //void changeZoom();

        void changeColor();

        void setTextFont(QString fontS);

        void setTextDim(int dim);

        void setTextDimEdit();

        void on_verticalScrollBar_sliderMoved(int position);

        void on_txt_cursorPositionChanged();

        void resizeEvent(QResizeEvent* event);

        //void on_impostazioni_clicked();

        void on_logout_clicked();

        void readFile();

        void insertFile(char r);

        void localInsert(int index, char value);

        void localErase(int index);

        void on_evidenzia_clicked();

        void add_async_symbol();

        void AsyncCompleteRpc(CharacterClient *pClient);

        void startAsyncClient();

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

    /*QMenu *zoomMenu;

    QActionGroup *zoomG;

    QToolButton *zoom;*/

    QList <QPushButton*> listaColor;

    QToolButton *colore;

    QMenu *coloreM;

    //int zoomT = 100;

    protobuf::FileInfo *file_;

    CharacterClient *client_;

    std::vector<Symbol> *symbol_;

    protobuf::SymbolVector *_symbolsP;

    bool eventFilter(QObject *obj, QEvent *event);

    bool bold = false;

    bool underline = false;

    bool italic = false;

    int dimS;

    QString colorS;

    QString fontS;

    QList<QString> colorL;

    QList<QString> emailL;

    bool insert = true;

    bool evidenzia = false;

    QString allineamento = "sinistra";

    protobuf::Symbol asyncSymbol;

};

#endif // EDITOR_H
