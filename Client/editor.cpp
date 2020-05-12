#include <QColorDialog>
#include <QFontDialog>
#include <QToolButton>
#include <QWidgetAction>
#include <QLineEdit>
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
#include <QVBoxLayout>
#include <QThread>
#include <QPixmap>
#include <QChar>
#include <messageP.pb.h>
#include <QtWidgets/QMessageBox>
#include "account.h"
#include "ui_editor.h"
#include "editor.h"
#include "comunication/Symbol.h"



Editor::Editor(QWidget *parent, std::string *fileid, CharacterClient *client) :
    QMainWindow(parent),
    ui(new Ui::Editor)
{
    client_=client;
    ui->setupUi(this);
    client_->GetFiles();
    file_ = new protobuf::FileInfo();
    *file_ = client_->getFileInfo(*fileid);
/*    if(!client_->GetFileContent(*file_).empty())
    {
        QMessageBox::warning(this, "Errore", "Non è stato possibile leggere il file");
    }*/
    setupGeneral();
}

Editor::~Editor()
{
    delete ui;
}

void Editor::setupGeneral() {
    setWindowTitle(QString::fromStdString(file_->filename()));
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));

    QObject::connect(ui->txt, SIGNAL(cursorPositionChanged()), this, SLOT(checkFont()));
    on_txt_cursorPositionChanged();

    setupAccount();
    setupFont();
    setupSize();
    setupColor();
    ui->toolBar_2->insertSeparator(ui->actiongrassetto);
    readFile();
    QObject::connect(ui->txt, SIGNAL(textChanged()), this, SLOT(saveFile()));
    on_txt_cursorPositionChanged();
}

void Editor::setupAccount() {
    //ACCOUNT

    QMenu *accountM = new QMenu();
    QVBoxLayout *accountV = new QVBoxLayout(accountM);
    accountM->setLayout(accountV);
    accountV->setAlignment(Qt::AlignCenter);

    QLabel *icona = new QLabel(accountM);
    icona->setAlignment(Qt::AlignCenter);
    QPixmap *iconaP = new QPixmap("img/logo.png");
    icona->setPixmap(*iconaP);
    accountV->addWidget(icona);

    QLabel *nome = new QLabel(accountM);
    nome->setAlignment(Qt::AlignCenter);
    nome->setText(QString::fromStdString(client_->getUsername()));
    accountV->addWidget(nome);

    QLabel *mail = new QLabel(accountM);
    mail->setAlignment(Qt::AlignCenter);
    mail->setText("mail");
    accountV->addWidget(mail);

    QPushButton *modifica = new QPushButton(accountM);
    modifica->setText("Impostazioni utente");
    accountV->addWidget(modifica);

    QPushButton *logout = new QPushButton(accountM);
    logout->setText("Logout");
    accountV->addWidget(logout);

    QObject::connect(modifica, SIGNAL(clicked()), this, SLOT(on_impostazioni_clicked()));
    QObject::connect(logout, SIGNAL(clicked()), this, SLOT(on_logout_clicked()));

    QToolButton *account = new QToolButton(this);

    QIcon *icon = new QIcon(":/img/logo.png");
    account->setIcon(*icon);
    account->setMenu(accountM);
    account->setPopupMode(QToolButton::InstantPopup);

    QWidget* empty = new QWidget();
    empty->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    ui->toolBar_3->addWidget(empty);

    ui->toolBar_3->addWidget(account);
}

void Editor::setupFont() {
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

    ui->toolBar_2->insertWidget(ui->actiongrassetto, font);

    QObject::connect(fontG, SIGNAL(triggered(QAction*)), this, SLOT(changeFont()));

    //QObject::connect(altriB, SIGNAL(pressed()), this, SLOT(on_actionfont_triggered()));

    listaFont = fontMenu->actions();

    ui->txt->setFont(QFont("Arial"));
}

void Editor::setupSize() {
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

    ui->toolBar_2->insertWidget(ui->actiongrassetto, dim);

    QObject::connect(dimG, SIGNAL(triggered(QAction*)), this, SLOT(changeDim()));

    QObject::connect(lEdit, SIGNAL(editingFinished()), this, SLOT(setTextDimEdit()));

    listaDim = dimMenu->actions();
}

void Editor::setupColor() {
    //MENU COLORE

    coloreM = new QMenu();
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
    QObject::connect(neroB, SIGNAL(clicked(bool)), this, SLOT(changeColor()));

    QPushButton *rossoB = new QPushButton(this);
    rossoB->setStyleSheet("background-color:rgb(255,0,0)");
    rossoB->setAutoExclusive(true);
    rossoB->setCheckable(true);
    coloreG->addWidget(rossoB, 0, 1);
    QObject::connect(rossoB, SIGNAL(clicked(bool)), this, SLOT(changeColor()));

    QPushButton *verdeB = new QPushButton(this);
    verdeB->setStyleSheet("background-color:rgb(0,255,0)");
    verdeB->setAutoExclusive(true);
    verdeB->setCheckable(true);
    coloreG->addWidget(verdeB, 0, 2);
    QObject::connect(verdeB, SIGNAL(clicked(bool)), this, SLOT(changeColor()));

    QPushButton *gialloB = new QPushButton(this);
    gialloB->setStyleSheet("background-color:rgb(253,244,3)");
    gialloB->setAutoExclusive(true);
    gialloB->setCheckable(true);
    coloreG->addWidget(gialloB, 1, 0);
    QObject::connect(gialloB, SIGNAL(clicked(bool)), this, SLOT(changeColor()));

    QPushButton *grigioB = new QPushButton(this);
    grigioB->setStyleSheet("background-color:rgb(112,112,112)");
    grigioB->setAutoExclusive(true);
    grigioB->setCheckable(true);
    coloreG->addWidget(grigioB, 1, 1);
    QObject::connect(grigioB, SIGNAL(clicked(bool)), this, SLOT(changeColor()));

    QPushButton *azzurroB = new QPushButton(this);
    azzurroB->setStyleSheet("background-color:rgb(7,203,238)");
    azzurroB->setAutoExclusive(true);
    azzurroB->setCheckable(true);
    coloreG->addWidget(azzurroB, 1, 2);
    QObject::connect(azzurroB, SIGNAL(clicked(bool)), this, SLOT(changeColor()));

    QPushButton *editB = new QPushButton("Altri Colori", this);
    coloreV->addWidget(editB);
    editB->setCheckable(true);
    editB->setAutoExclusive(true);

    QObject::connect(editB, SIGNAL(clicked(bool)), this, SLOT(on_actioncolore_triggered()));

    colore = new QToolButton(this);
    colore->setStyleSheet("background-color:rgb(0,0,0)");
    colore->setMenu(coloreM);
    colore->setPopupMode(QToolButton::InstantPopup);

    ui->toolBar_2->insertWidget(ui->actiongrassetto, colore);

    listaColor.insert(0, neroB);
    listaColor.insert(1, rossoB);
    listaColor.insert(2, verdeB);
    listaColor.insert(3, gialloB);
    listaColor.insert(4, grigioB);
    listaColor.insert(5, azzurroB);
}

void Editor::on_actionindietro_triggered()
{
    emit closeE();
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

    if(ui->actiongrassetto->isChecked())
        ui->txt->setFontWeight(QFont::Bold);
    else {
        ui->txt->setFontWeight(QFont::Normal);
    }
}


void Editor::on_actioncorsivo_triggered()
{
    ui->txt->setFontItalic(ui->actioncorsivo->isChecked());
}

void Editor::on_actionsottolineato_triggered()
{
    ui->txt->setFontUnderline(ui->actionsottolineato->isChecked());
}

void Editor::on_actioncolore_triggered()
{
    QColor colB = colore->palette().color(QPalette::Background);

                QColor color = QColorDialog::getColor(colB, this, "Scegli un colore");
                if(color.isValid()) {
                    ui->txt->setTextColor(color);
                    QString qss = QString("background-color: %1").arg(color.name());
                    colore->setStyleSheet(qss);

                }

                checkFont();
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
    ui->actiongrassetto->setChecked(ui->txt->currentFont().bold());

    ui->actionsottolineato->setChecked(ui->txt->currentFont().underline());

    ui->actioncorsivo->setChecked(ui->txt->currentFont().italic());

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

    ui->txt->alignment();

    if(ui->txt->alignment() == Qt::AlignLeft) {

        ui->actionallineaD->setChecked(false);
        ui->actionallineaC->setChecked(false);
        ui->actionallineaS->setChecked(true);
        ui->actionalineaG->setChecked(false);
    }
    else if(ui->txt->alignment() == Qt::AlignRight) {

        ui->actionallineaD->setChecked(true);
        ui->actionallineaC->setChecked(false);
        ui->actionallineaS->setChecked(false);
        ui->actionalineaG->setChecked(false);
    }
    else if(ui->txt->alignment() == Qt::AlignCenter) {

        ui->actionallineaD->setChecked(false);
        ui->actionallineaC->setChecked(true);
        ui->actionallineaS->setChecked(false);
        ui->actionalineaG->setChecked(false);
    }
    else if(ui->txt->alignment() == Qt::AlignJustify) {

        ui->actionallineaD->setChecked(false);
        ui->actionallineaC->setChecked(false);
        ui->actionallineaS->setChecked(false);
        ui->actionalineaG->setChecked(true);
    }

}

void Editor::changeDim()
{
    int dimens = dimG->checkedAction()->text().toInt();
    setTextDim(dimens);
    lEdit->clear();
}

void Editor::changeFont()
{
    QString fontS = fontG->checkedAction()->text();
    setTextFont(fontS);
}

/*void Editor::changeZoom()
{

    QString zoomS = zoomG->checkedAction()->text();
    //int zoomI = zoomS.split("%")[0].toInt();                            //da fare
    //qDebug()<<zoomI;
    QString z = "{zoom: " + zoomS + "}";
    ui->groupBox_2->setStyleSheet(z);

}*/

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

    coloreM->close();

    checkFont();
}

void Editor::setTextFont(QString fontS)
{
    QFont *font1 = new QFont(fontS);
    QTextCursor cursor = ui->txt->textCursor();
    QTextCharFormat format = cursor.blockCharFormat();
    format.setFont(*font1);
    format.setFontPointSize(ui->txt->currentFont().pointSize());
    cursor.setCharFormat(format);
    ui->txt->setTextCursor(cursor);

    font->setText(fontS);
    font->setFont(fontS);
    //checkFont();

}

void Editor::setTextDim(int dim1)
{
    QTextCursor cursor = ui->txt->textCursor();
    QTextCharFormat format = cursor.blockCharFormat();
    format.setFont(ui->txt->currentFont().family());
    format.setFontPointSize(dim1);
    cursor.setCharFormat(format);
    ui->txt->setTextCursor(cursor);
    dim->setText(QString::number(dim1));
    //checkFont();
}

void Editor::setTextDimEdit()
{
    int dimension = lEdit->text().toInt();
    setTextDim(dimension);
}

void Editor::on_verticalScrollBar_sliderMoved(int position)
{
    ui->txt->verticalScrollBar()->setValue(position);
}

void Editor::on_txt_cursorPositionChanged()
{
    ui->verticalScrollBar->setPageStep(ui->txt->verticalScrollBar()->pageStep());
    ui->verticalScrollBar->setRange(ui->txt->verticalScrollBar()->minimum(),ui->txt->verticalScrollBar()->maximum());
    ui->verticalScrollBar->setValue(ui->txt->verticalScrollBar()->value());
}

void Editor::resizeEvent(QResizeEvent* event)
{
    on_txt_cursorPositionChanged();
}

void Editor::on_impostazioni_clicked()
{
    Account account;
    account.setModal(true);
    account.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    account.exec();
}

void Editor::on_logout_clicked()
{
    emit closeEP();
}

void Editor::readFile() {
    int i=0;
    QTextCursor cursor = ui->txt->textCursor();

    if(!client_->GetFileContent(*file_).empty())
    {
        QMessageBox::warning(this, "Errore", "Non è stato possibile leggere il file");
    }

    std::cout << client_->getSymbolVector().DebugString() << "\n";

    for(i=0; i<client_->getSymbolVector().symbolvector_size(); i++)
    {
        protobuf::Symbol symbol = client_->getSymbolVector().symbolvector(i);
        cursor.setPosition(symbol.pos().data()[0]);
        ui->txt->setTextCursor(cursor);
        char p = std::stoi(symbol.character());
        ui->txt->insertPlainText(QChar(p));
    }
}

void Editor::saveFile() {
    QTextCursor cur = ui->txt->textCursor();
    cur.movePosition(QTextCursor::PreviousCharacter,QTextCursor::KeepAnchor,1);
    qDebug() << cur.selectedText();
    std::vector<int> pos;
    pos.push_back(cur.position());
    Symbol *symbol = new Symbol(cur.selectedText().toStdString()[0],client_->getUsername(), pos);
/*
    symbol.set_character(cur.selectedText().toStdString());
    symbol.set_pos(0, cur.position());
    symbol.set_uniqueid(client_->getUsername());*/
    client_->InsertSymbols(*symbol, false);
}

/*void Editor::setupZoom() {
 * /*MENU ZOOM

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

       QObject::connect(zoomG, SIGNAL(triggered(QAction*)), this, SLOT(changeZoom()));*/
 // }
