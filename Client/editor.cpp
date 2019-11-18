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
#include <QLabel>
#include <QPushButton>
#include <QAbstractButton>
#include <QMenu>
#include <QMessageLogger>
#include <QDebug>
#include <QList>
#include <QTextBlock>
#include <QIntValidator>
#include <QGridLayout>
#include <QVBoxLayout>

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);

    this->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
                this, SLOT(ShowContextMenu(const QPoint &)));

        QObject::connect(ui->txt, SIGNAL(cursorPositionChanged()), this, SLOT(checkFont()));


        //MENU FONT

        fontMenu = new QMenu();
        fontG = new QActionGroup(fontMenu);
        fontG->setExclusive(true);

        QAction *arial = new QAction("Arial", fontMenu);
        arial->setCheckable(true);
        arial->setChecked(true);
        arial->setFont(QFont("Arial"));
        fontG->addAction(arial);
        fontMenu->addAction(arial);
        QAction *comic = new QAction("Comic Sans", fontMenu);
        comic->setCheckable(true);
        comic->setFont(QFont("Comic Sans MS"));
        fontG->addAction(comic);
        fontMenu->addAction(comic);
        QAction *georgia = new QAction("Georgia", fontMenu);
        georgia->setCheckable(true);
        georgia->setFont(QFont("Georgia"));
        fontG->addAction(georgia);
        fontMenu->addAction(georgia);
        QAction *roboto = new QAction("Roboto", fontMenu);
        roboto->setCheckable(true);
        roboto->setFont(QFont("Roboto"));
        fontG->addAction(roboto);
        fontMenu->addAction(roboto);
        QAction *times = new QAction("Times New Roman", fontMenu);
        times->setCheckable(true);
        times->setFont(QFont("Times New Roman"));
        fontG->addAction(times);
        fontMenu->addAction(times);
        QAction *verdana = new QAction("Verdana", fontMenu);
        verdana->setCheckable(true);
        verdana->setFont(QFont("Verdana"));
        fontG->addAction(verdana);
        fontMenu->addAction(verdana);
        /*QWidgetAction *altri = new QWidgetAction(fontMenu);
        QPushButton *altriB = new QPushButton("Altri Caratteri", this);
        altri->setDefaultWidget(altriB);
        fontMenu->addAction(altri);*/

        font = new QToolButton(this);
        font->setText("Arial");
        font->setFont(QFont("Arial"));
        font->setMenu(fontMenu);
        font->setPopupMode(QToolButton::InstantPopup);

        ui->toolBar_2->insertWidget(ui->actioncolore, font);

        QObject::connect(fontG, SIGNAL(triggered(QAction*)), this, SLOT(changeFont()));

        //QObject::connect(altriB, SIGNAL(pressed()), this, SLOT(on_actionfont_triggered()));

        listaFont = fontMenu->actions();

        ui->txt->setFont(QFont("Arial"));

       //MENU DIM

       dimMenu = new QMenu();
       dimG = new QActionGroup(dimMenu);
       dimG->setExclusive(true);

       QAction *otto = new QAction("8", dimMenu);
       otto->setCheckable(true);
       otto->setChecked(true);
       dimG->addAction(otto);
       dimMenu->addAction(otto);
       QAction *dieci = new QAction("10", dimMenu);
       dieci->setCheckable(true);
       dimG->addAction(dieci);
       dimMenu->addAction(dieci);
       QAction *undici = new QAction("11", dimMenu);
       undici->setCheckable(true);
       dimG->addAction(undici);
       dimMenu->addAction(undici);
       QAction *dodici = new QAction("12", dimMenu);
       dodici->setCheckable(true);
       dimG->addAction(dodici);
       dimMenu->addAction(dodici);
       QAction *quattor = new QAction("14", dimMenu);
       quattor->setCheckable(true);
       dimG->addAction(quattor);
       dimMenu->addAction(quattor);
       QAction *dicio = new QAction("18", dimMenu);
       dicio->setCheckable(true);
       dimG->addAction(dicio);
       dimMenu->addAction(dicio);
       QAction *ventiq = new QAction("24", dimMenu);
       ventiq->setCheckable(true);
       dimG->addAction(ventiq);
       dimMenu->addAction(ventiq);
       QAction *tren = new QAction("30", dimMenu);
       tren->setCheckable(true);
       dimG->addAction(tren);
       dimMenu->addAction(tren);
       QAction *trens = new QAction("36", dimMenu);
       trens->setCheckable(true);
       dimG->addAction(trens);
       dimMenu->addAction(trens);
       QAction *quar = new QAction("48", dimMenu);
       quar->setCheckable(true);
       dimG->addAction(quar);
       dimMenu->addAction(quar);
       QAction *sett = new QAction("72", dimMenu);
       sett->setCheckable(true);
       dimG->addAction(sett);
       dimMenu->addAction(sett);
       QWidgetAction *edit = new QWidgetAction(dimMenu);
       lEdit = new QLineEdit(this);
       edit->setDefaultWidget(lEdit);
       lEdit->setValidator(new QIntValidator(1, 100, this));
       lEdit->setMaxLength(2);
       dimMenu->addAction(edit);

       /*QString  menuStyle(
                  "QMenu::item{"
                  "background-color: rgb(0, 170, 0);"
                  "color: rgb(255, 255, 255);"
                  "}"
                  "QMenu::item:selected{"
                  "background-color: rgb(0, 85, 127);"
                  "color: rgb(255, 255, 255);"
                  "}"
               );*/


       /*QString menuStyle(
                   "QMenu::item{"
                   "width: 1px}");*/

       //dimMenu->setStyleSheet(menuStyle);

       dim = new QToolButton(this);
       dim->setText("8");
       dim->setMenu(dimMenu);
       dim->setPopupMode(QToolButton::InstantPopup);

       ui->toolBar_2->insertWidget(ui->actioncolore, dim);

       QObject::connect(dimG, SIGNAL(triggered(QAction*)), this, SLOT(changeDim()));

       QObject::connect(lEdit, SIGNAL(editingFinished()), this, SLOT(setTextDimEdit()));

       listaDim = dimMenu->actions();

       //MENU ZOOM

       zoomMenu = new QMenu();
       zoomG = new QActionGroup(zoomMenu);
       zoomG->setExclusive(true);

       QAction *duec = new QAction("200%", zoomMenu);
       duec->setCheckable(true);
       zoomG->addAction(duec);
       zoomMenu->addAction(duec);
       QAction *cencin = new QAction("150%", zoomMenu);
       cencin->setCheckable(true);
       zoomG->addAction(cencin);
       zoomMenu->addAction(cencin);
       QAction *cen = new QAction("100%", zoomMenu);
       cen->setCheckable(true);
       cen->setChecked(true);
       zoomG->addAction(cen);
       zoomMenu->addAction(cen);
       QAction *otta = new QAction("80%", zoomMenu);
       otta->setCheckable(true);
       zoomG->addAction(otta);
       zoomMenu->addAction(otta);
       QAction *cin = new QAction("50%", zoomMenu);
       cin->setCheckable(true);
       zoomG->addAction(cin);
       zoomMenu->addAction(cin);
       QAction *trent = new QAction("30%", zoomMenu);
       trent->setCheckable(true);
       zoomG->addAction(trent);
       zoomMenu->addAction(trent);
       QAction *diec = new QAction("10%", zoomMenu);
       diec->setCheckable(true);
       zoomG->addAction(diec);
       zoomMenu->addAction(diec);

       zoom = new QToolButton(this);
       zoom->setText("100%");
       zoom->setMenu(zoomMenu);
       zoom->setPopupMode(QToolButton::InstantPopup);

       ui->toolBar_2->insertWidget(ui->actionallineaS, zoom);

       QObject::connect(zoomG, SIGNAL(triggered(QAction*)), this, SLOT(changeZoom()));

       //COLORE

       QMenu *coloreM = new QMenu();
       QVBoxLayout *coloreV = new QVBoxLayout(coloreM);
       QGridLayout *coloreG = new QGridLayout(coloreM);
       coloreM->setLayout(coloreV);
       coloreV->addLayout(coloreG);

       QPushButton *neroB = new QPushButton(this);
       neroB->setStyleSheet("background-color:rgb(0,0,0)");
       neroB->setAutoExclusive(true);
       neroB->setCheckable(true);
       neroB->setChecked(true);
       coloreG->addWidget(neroB, 0, 0);
       QObject::connect(neroB, SIGNAL(toggled(bool)), this, SLOT(changeColor()));

       QPushButton *rossoB = new QPushButton(this);
       rossoB->setStyleSheet("background-color:rgb(255,0,0)");
       rossoB->setAutoExclusive(true);
       rossoB->setCheckable(true);
       coloreG->addWidget(rossoB, 0, 1);
       QObject::connect(rossoB, SIGNAL(toggled(bool)), this, SLOT(changeColor()));

       QPushButton *verdeB = new QPushButton(this);
       verdeB->setStyleSheet("background-color:rgb(0,255,0)");
       verdeB->setAutoExclusive(true);
       verdeB->setCheckable(true);
       coloreG->addWidget(verdeB, 0, 2);
       QObject::connect(verdeB, SIGNAL(toggled(bool)), this, SLOT(changeColor()));

       QPushButton *gialloB = new QPushButton(this);
       gialloB->setStyleSheet("background-color:rgb(253,244,3)");
       gialloB->setAutoExclusive(true);
       gialloB->setCheckable(true);
       coloreG->addWidget(gialloB, 1, 0);
       QObject::connect(gialloB, SIGNAL(toggled(bool)), this, SLOT(changeColor()));

       QPushButton *grigioB = new QPushButton(this);
       grigioB->setStyleSheet("background-color:rgb(112,112,112)");
       grigioB->setAutoExclusive(true);
       grigioB->setCheckable(true);
       coloreG->addWidget(grigioB, 1, 1);
       QObject::connect(grigioB, SIGNAL(toggled(bool)), this, SLOT(changeColor()));

       QPushButton *azzurroB = new QPushButton(this);
       azzurroB->setStyleSheet("background-color:rgb(7,203,238)");
       azzurroB->setAutoExclusive(true);
       azzurroB->setCheckable(true);
       coloreG->addWidget(azzurroB, 1, 2);
       QObject::connect(azzurroB, SIGNAL(toggled(bool)), this, SLOT(changeColor()));

       QPushButton *editB = new QPushButton("Altri Colori", this);
       coloreV->addWidget(editB);

       colore = new QToolButton(this);
       colore->setStyleSheet("background-color:rgb(0,0,0)");
       colore->setMenu(coloreM);
       colore->setPopupMode(QToolButton::InstantPopup);

       ui->toolBar_2->insertWidget(ui->actioncolore, colore);

       listaColor.insert(0, neroB);
       listaColor.insert(1, rossoB);
       listaColor.insert(2, verdeB);
       listaColor.insert(3, gialloB);
       listaColor.insert(4, grigioB);
       listaColor.insert(5, azzurroB);
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
    qDebug()<<ui->txt->currentFont().toString();    //"MS Shell Dlg 2,8,-1,5,50,0,0,0,0,0,Normale" font,dim,boh,boh,grassetto,corsivo,sotto...

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
    QColor color = QColorDialog::getColor(Qt::black, this, "Scegli un colore");         //bisogna aggiungere il colore attuale
    if(color.isValid()) {
        ui->txt->setTextColor(color);
    }
    else return;
}

void Editor::on_actionfont_triggered()
{
    /*bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        setTextFont(&font);
    }
    else return;*/
}

void Editor::ShowContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

       QAction action3("Taglia", this);
       QAction action1("Copia", this);
       QAction action2("Incolla", this);

       connect(&action1, SIGNAL(triggered()), this, SLOT(ui->txt->cut();));
       connect(&action2, SIGNAL(triggered()), this, SLOT(ui->txt->copy();));
       connect(&action3, SIGNAL(triggered()), this, SLOT(ui->txt->paste();));

       contextMenu.addAction(&action1);
       contextMenu.addAction(&action2);
       contextMenu.addAction(&action3);

       contextMenu.exec(mapToGlobal(pos));
}

void Editor::checkFont()
{
    if(ui->txt->currentFont().bold())
        ui->actiongrassetto->setChecked(true);
    else
         ui->actiongrassetto->setChecked(false);

    if(ui->txt->currentFont().underline())
        ui->actionsottolineato->setChecked(true);
    else
         ui->actionsottolineato->setChecked(false);

    if(ui->txt->currentFont().italic())
        ui->actioncorsivo->setChecked(true);
    else
         ui->actioncorsivo->setChecked(false);

    for(int i=0; i<11; i++){

        if(QString::compare(listaDim.at(i)->text(), QString::number(ui->txt->currentFont().pointSize()), Qt::CaseSensitive)==0)
        {
             listaDim.at(i)->setChecked(true);
             break;
        }
        else
        {
             listaDim.at(i)->setChecked(false);
        }

    }

    dim->setText(QString::number(ui->txt->currentFont().pointSize()));

    for(int y=0; y<6; y++){

        if(QString::compare(listaFont.at(y)->text(), ui->txt->currentFont().family(), Qt::CaseSensitive)==0)
        {
             listaFont.at(y)->setChecked(true);
             break;
        }
        else
        {
             listaFont.at(y)->setChecked(false);
        }

    }

    font->setText(ui->txt->currentFont().family());
    font->setFont(QFont(ui->txt->currentFont().family()));

    QColor colorText=ui->txt->currentCharFormat().foreground().color();

    for(int z=0; z<6; z++)
    {
        if(listaColor.at(z)->palette().color(QPalette::Background)==colorText)
        {
            listaColor.at(z)->setChecked(true);
            break;
        }
        else
        {
            listaColor.at(z)->setChecked(false);
        }
    }

    QString qss = QString("background-color: %1").arg(colorText.name());
    colore->setStyleSheet(qss);

}

void Editor::changeDim()
{
    int dim = dimG->checkedAction()->text().toInt();
    setTextDim(dim);
}

void Editor::changeFont()
{
    QString fontS = fontG->checkedAction()->text();
    QFont *font = new QFont(fontS);
    setTextFont(font);
}

void Editor::changeZoom()
{
    /*QString zoomS = zoomG->checkedAction()->text();
    int zoomI = zoomS.split("%")[0].toInt();                            //da fare
    if(zoomI>100)
    {
        ui->centralwidget->ed
    }
    else if(zoom<100)
    {

    }*/

}

void Editor::changeColor()
{
    for(int i=0; i<6; i++)
    {
        if(listaColor.at(i)->isChecked())
        {
            QColor color1 = listaColor.at(i)->palette().color(QPalette::Background);

            ui->txt->setTextColor(color1);

            break;
        }
    }

    checkFont();
}

void Editor::setTextFont(QFont *font)
{
    QTextCursor cursor = ui->txt->textCursor();
    QTextCharFormat *format = new QTextCharFormat();
    format->setFont(*font);
    format->setFontPointSize(ui->txt->currentFont().pointSize());

    cursor.setCharFormat(*format);

    checkFont();

}

void Editor::setTextDim(int dim)
{
    QTextCursor cursor = ui->txt->textCursor();
    QTextCharFormat *format = new QTextCharFormat();
    format->setFont(ui->txt->currentFont().family());
    format->setFontPointSize(dim);

    cursor.setCharFormat(*format);

    checkFont();
}


void Editor::setTextDimEdit()
{
    int dim = lEdit->text().toInt();
    setTextDim(dim);
}
