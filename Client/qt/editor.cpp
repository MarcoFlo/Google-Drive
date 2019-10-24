#include "editor.h"
#include "ui_editor.h"
#include <QScrollBar>
#include <QAbstractScrollArea>
#include <QTextEdit>

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
