#include "editor.h"
#include "ui_editor.h"
#include <QScrollBar>
#include <QAbstractScrollArea>
#include <QTextEdit>
#include <QColorDialog>
#include <QFontDialog>
#include <QToolButton>
#include <QWidgetAction>
#include <QLineEdit>
#include <QLayout>
#include <QFont>

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);

    this->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
                this, SLOT(ShowContextMenu(const QPoint &)));

        //MENU FONT

        QMenu *fontMenu = new QMenu();
        QAction *arial = new QAction("Arial", this);
        arial->setFont(QFont("Arial"));
        fontMenu->addAction(arial);
        QAction *comic = new QAction("Comic Sans", this);
        comic->setFont(QFont("Comic Sans MS"));
        fontMenu->addAction(comic);
        QAction *georgia = new QAction("Georgia", this);
        georgia->setFont(QFont("Georgia"));
        fontMenu->addAction(georgia);
        QAction *roboto = new QAction("Roboto", this);
        roboto->setFont(QFont("Roboto"));
        fontMenu->addAction(roboto);
        QAction *times = new QAction("Times New Roman", this);
        times->setFont(QFont("Times New Roman"));
        fontMenu->addAction(times);
        QAction *verdana = new QAction("Verdana", this);
        verdana->setFont(QFont("Verdana"));
        fontMenu->addAction(verdana);

        fontMenu->addAction(new QAction("Altri Caratteri", this));

        QToolButton *font = new QToolButton(this);
        font->setText("font");
        font->setMenu(fontMenu);
        font->setPopupMode(QToolButton::InstantPopup);

        ui->toolBar_2->insertWidget(ui->actioncolore, font);

       //MENU DIM

       QMenu *dimMenu = new QMenu();
       dimMenu->addAction(new QAction("8", this));
       dimMenu->addAction(new QAction("10", this));
       dimMenu->addAction(new QAction("11", this));
       dimMenu->addAction(new QAction("12", this));
       dimMenu->addAction(new QAction("14", this));
       dimMenu->addAction(new QAction("18", this));
       dimMenu->addAction(new QAction("24", this));
       dimMenu->addAction(new QAction("30", this));
       dimMenu->addAction(new QAction("36", this));
       dimMenu->addAction(new QAction("48", this));
       dimMenu->addAction(new QAction("72", this));
       QWidgetAction *edit = new QWidgetAction(this);
       edit->setDefaultWidget(new QLineEdit(this));
       dimMenu->addAction(edit);

       //dimMenu->setStyleSheet("QMenu::item { text-align: center; }");

       //MENU ZOOM

       QToolButton *dim = new QToolButton(this);
       dim->setText("dimensione");
       dim->setMenu(dimMenu);
       dim->setPopupMode(QToolButton::InstantPopup);

       ui->toolBar_2->insertWidget(ui->actioncolore, dim);

       QMenu *zoomMenu = new QMenu();
       zoomMenu->addAction(new QAction("200%", this));
       zoomMenu->addAction(new QAction("150%", this));
       zoomMenu->addAction(new QAction("100%", this));
       zoomMenu->addAction(new QAction("80%", this));
       zoomMenu->addAction(new QAction("50%", this));
       zoomMenu->addAction(new QAction("30%", this));
       zoomMenu->addAction(new QAction("10%", this));

       QToolButton *zoom = new QToolButton(this);
       zoom->setText("zoom");
       zoom->setMenu(zoomMenu);
       zoom->setPopupMode(QToolButton::InstantPopup);

       ui->toolBar_2->insertWidget(ui->actionallineaS, zoom);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::Mostra()
{
    show();
}

void Editor::on_actionindietro_triggered()
{
    hide();
    emit openP();
}

void Editor::on_actionredo_triggered()
{
    ui->txt->redo();
}

void Editor::on_actioncopia_triggered()
{
    ui->txt->copy();
}

void Editor::on_actionincolla_triggered()
{
    ui->txt->paste();
}

void Editor::on_actiontaglia_triggered()
{
    ui->txt->cut();
}

void Editor::on_actionundo_triggered()
{
    ui->txt->undo();
}

void Editor::on_actionallineaD_triggered()
{
    ui->txt->setAlignment(Qt::AlignRight);
    ui->actionallineaD->setChecked(true);
    ui->actionallineaC->setChecked(false);
    ui->actionallineaS->setChecked(false);
    ui->actionalineaG->setChecked(false);

}

void Editor::on_actionallineaS_triggered()
{
    ui->txt->setAlignment(Qt::AlignLeft);
    ui->actionallineaD->setChecked(false);
    ui->actionallineaC->setChecked(false);
    ui->actionallineaS->setChecked(true);
    ui->actionalineaG->setChecked(false);
}

void Editor::on_actionallineaC_triggered()
{
    ui->txt->setAlignment(Qt::AlignCenter);
    ui->actionallineaD->setChecked(false);
    ui->actionallineaC->setChecked(true);
    ui->actionallineaS->setChecked(false);
    ui->actionalineaG->setChecked(false);
}

void Editor::on_actionalineaG_triggered()
{
    ui->txt->setAlignment(Qt::AlignJustify);
    ui->actionallineaD->setChecked(false);
    ui->actionallineaC->setChecked(false);
    ui->actionallineaS->setChecked(false);
    ui->actionalineaG->setChecked(true);

}

void Editor::on_actiongrassetto_triggered()
{

    if(ui->actiongrassetto->isChecked()==true)
        ui->txt->setFontWeight(QFont::Bold);
    else {
        ui->txt->setFontWeight(QFont::Normal);
    }
}


void Editor::on_actioncorsivo_triggered()
{
    if(ui->actioncorsivo->isChecked()==true)
        ui->txt->setFontItalic(true);
    else {
        ui->txt->setFontItalic(false);
    }
}

void Editor::on_actionsottolineato_triggered()
{
    if(ui->actionsottolineato->isChecked()==true)
        ui->txt->setFontUnderline(true);
    else {
        ui->txt->setFontUnderline(false);
    }
}

void Editor::on_actioncolore_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Scegli un colore");
    if(color.isValid()) {
        ui->txt->setTextColor(color);
    }
    else return;
}

void Editor::on_actionfont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok) {
        ui->txt->setFont(font);
    }
    else return;
}

void Editor::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

       QAction action1("Gisella", this);
       QAction action2("Marco", this);
       QAction action3("Simone", this);
       connect(&action1, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
       connect(&action2, SIGNAL(triggered()), this, SLOT(removeDataPoint()));
       connect(&action3, SIGNAL(triggered()), this, SLOT(removeDataPoint()));

       contextMenu.addAction(&action1);
       contextMenu.addAction(&action2);
       contextMenu.addAction(&action3);

       contextMenu.exec(mapToGlobal(pos));
}


