#include "editor.h"
#include "ui_editor.h"
#include <QScrollBar>
#include <QAbstractScrollArea>
#include <QTextEdit>
#include <QColorDialog>
#include <QFontDialog>

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);
    //ui->txt->verticalScrollBar()->setDisabled(true);
    //ui->textEdit->setSizePolicy(QAbstractScrollArea::AdjustToContents);
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

void Editor::on_actiondimensione_triggered()
{

}
