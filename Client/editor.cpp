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
#include <QtCore>
#include <QKeyEvent>
#include <regex>
#include <QPainter>
#include <QMessageBox>
#include <QList>
#include <csignal>

std::atomic<bool> exit_thread_flag{false};

Editor::Editor(QWidget *parent, std::string *fileid, CharacterClient *client) :
        QMainWindow(parent),
        ui(new Ui::Editor) {
    client_ = client;
    _symbolsP = new protobuf::SymbolVector();
    symbol_ = new std::vector<Symbol>();
    ui->setupUi(this);
    client_->GetFiles();
    file_ = new protobuf::FileInfo();
    *file_ = client_->getFileInfo(*fileid);
/*    if(!client_->GetFileContent(*file_).empty())
    {
        QMessageBox::warning(this, "Errore", "Non è stato possibile leggere il file");
    }*/
    setupGeneral();
    startAsyncClient();
    QObject::connect(this, SIGNAL(newAsync()), this, SLOT(add_async_symbol()));

}

Editor::~Editor() {
    delete ui;
}

void Editor::setupGeneral() {

    colorL = {"#fdb9c9", "#ffdcbe", "#f6f3b5", "#bbf6f3", "#a7e0f4", "#b2d8b5", "#b7b4db", "#d6bddd", "#c0d6e4",
              "#fb9692", "#c0d6e4", "#fab297", "#afd7b4", "#c0c0c0"};

    //
    QLayoutItem *wItem;
    while ((wItem = ui->verticalLayout->takeAt(0)) != 0) {
        //delete wItem;
        delete wItem->widget();
    }

    QLabel *io = new QLabel(this);
    io->setText(file_->emailo().c_str());
    emailL.append(file_->emailo().c_str());
    QString colorq = colorL[0];
    QString colorstyleq = QString("font-size: 12px;"
                                  "font-family: 'Calibri';"
                                  "color: black;"
                                  "background-color: %1").arg(colorq);
    io->setStyleSheet(colorstyleq);
    io->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->verticalLayout->addWidget(io);

    for (int i = 0; i < file_->emailal_size(); i++) {
        if (file_->emailal(i).c_str() != file_->emailo().c_str()) {
            QLabel *item = new QLabel(this);
            item->setText(file_->emailal(i).c_str());
            emailL.append(file_->emailal(i).c_str());
            QString colorqqqq = colorL[i + 1];
            QString colorstyle = QString("font-size: 12px;"
                                         "font-family: 'Calibri';"
                                         "color: black;"
                                         "background-color: %1").arg(colorqqqq);
            item->setStyleSheet(colorstyle);
            ui->verticalLayout->addWidget(item);
        }
    }
    //

    QIcon *ic = new QIcon(":/images/img/logoVero.png");
    setWindowIcon(*ic);

    setWindowTitle(QString::fromStdString(file_->filename()));
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));

    QObject::connect(ui->txt, SIGNAL(cursorPositionChanged()), this, SLOT(checkFont()));
    on_txt_cursorPositionChanged();

    //setupAccount();
    setupFont();
    setupSize();
    setupColor();
    ui->toolBar_2->insertSeparator(ui->actiongrassetto);
    readFile();
    ui->txt->installEventFilter(this);
    //QObject::connect(ui->txt, SIGNAL(keyPressEvent(QKeyEvent*)), this, SLOT(saveFile(QKeyEvent*)));
    on_txt_cursorPositionChanged();

}

/*void Editor::setupAccount() {
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
    nome->setText(QString::fromStdString(client_->getProfileInfoLogged().user().email()));
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
}*/

void Editor::setupFont() {
    //MENU FONT

    fontMenu = new QMenu();
    fontMenu->setStyleSheet("QMenu {"
                            "background-color: white;"
                            "border: 1px solid #336b8a;}"
                            "QMenu::item:selected {"
                            "background-color: rgba(245, 245, 245, 200);"
                            "color: black;}"
                            "QMenu::item:checked {"
                            "background-color: rgba(245, 245, 245, 200);"
                            "color: black;}");
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

    QObject::connect(fontG, SIGNAL(triggered(QAction * )), this, SLOT(changeFont()));

    //QObject::connect(altriB, SIGNAL(pressed()), this, SLOT(on_actionfont_triggered()));

    listaFont = fontMenu->actions();

    ui->txt->setFont(QFont("Arial"));
}

void Editor::setupSize() {
    //MENU DIM

    dimMenu = new QMenu();
    dimMenu->setStyleSheet("QMenu {"
                           "background-color: white;"
                           "border: 1px solid #336b8a;}"
                           "QMenu::item:selected {"
                           "background-color: rgba(245, 245, 245, 200);"
                           "color: black;}"
                           "QMenu::item:checked {"
                           "background-color: rgba(245, 245, 245, 200);"
                           "color: black;}");
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
    lEdit->setStyleSheet("QLineEdit {"
                         "border:1px solid #3a848a;}"
                         "QLineEdit:hover {"
                         "border:2px solid #3a848a;}"
                         "QLineEdit:focus {"
                         "border:2px solid #3a848a;}");

    dimMenu->addAction(edit);

    dim = new QToolButton(this);
    dim->setText("8");
    dim->setMenu(dimMenu);
    dim->setPopupMode(QToolButton::InstantPopup);

    ui->toolBar_2->insertWidget(ui->actiongrassetto, dim);

    QObject::connect(dimG, SIGNAL(triggered(QAction * )), this, SLOT(changeDim()));

    QObject::connect(lEdit, SIGNAL(editingFinished()), this, SLOT(setTextDimEdit()));

    listaDim = dimMenu->actions();
}

void Editor::setupColor() {
    //MENU COLORE

    coloreM = new QMenu();
    coloreM->setStyleSheet("QMenu {"
                           "background-color: white;"
                           "border: 1px solid #336b8a;}"
                           "QMenu::item:selected {"
                           "background-color: rgba(245, 245, 245, 200);"
                           "color: black;}"
                           "QMenu::item:checked {"
                           "background-color: rgba(245, 245, 245, 200);"
                           "color: black;}");
    QVBoxLayout *coloreV = new QVBoxLayout(coloreM);
    QGridLayout *coloreG = new QGridLayout(coloreM);
    coloreV->addLayout(coloreG);
    coloreM->setLayout(coloreV);

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
    editB->setStyleSheet("QPushButton {"
                         "color: #3a848a;"
                         "font-size: 12px;"
                         "border: 1px solid #3a848a;"
                         "padding: 5px;"
                         "font-family: 'Calibri';"
                         "background-color:none;}"
                         "QPushButton:hover {"
                         "border:2px solid #3a848a;}");

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

void Editor::on_actionindietro_triggered() {
    client_->closeFile();
    exit_thread_flag = true;
    emit closeE();
}

void Editor::on_actionredo_triggered() {
    ui->txt->redo();
}

void Editor::on_actioncopia_triggered() {
    ui->txt->copy();
}

void Editor::on_actionincolla_triggered() {
    ui->txt->paste();
}

void Editor::on_actiontaglia_triggered() {
    ui->txt->cut();
}

void Editor::on_actionundo_triggered() {
    ui->txt->undo();
}

void Editor::on_actionallineaD_triggered() {
    ui->txt->setAlignment(Qt::AlignRight);
    ui->actionallineaD->setChecked(true);
    ui->actionallineaC->setChecked(false);
    ui->actionallineaS->setChecked(false);
    ui->actionalineaG->setChecked(false);
    allineamento = "destra";

}

void Editor::on_actionallineaS_triggered() {
    ui->txt->setAlignment(Qt::AlignLeft);
    ui->actionallineaD->setChecked(false);
    ui->actionallineaC->setChecked(false);
    ui->actionallineaS->setChecked(true);
    ui->actionalineaG->setChecked(false);
    allineamento = "sinistra";
}

void Editor::on_actionallineaC_triggered() {
    ui->txt->setAlignment(Qt::AlignCenter);
    ui->actionallineaD->setChecked(false);
    ui->actionallineaC->setChecked(true);
    ui->actionallineaS->setChecked(false);
    ui->actionalineaG->setChecked(false);
    allineamento = "centro";
}

void Editor::on_actionalineaG_triggered() {
    ui->txt->setAlignment(Qt::AlignJustify);
    ui->actionallineaD->setChecked(false);
    ui->actionallineaC->setChecked(false);
    ui->actionallineaS->setChecked(false);
    ui->actionalineaG->setChecked(true);
    allineamento = "giustificato";
}

void Editor::on_actiongrassetto_triggered() {

    if (ui->actiongrassetto->isChecked()) {
        ui->txt->setFontWeight(QFont::Bold);
        bold = true;
    } else {
        ui->txt->setFontWeight(QFont::Normal);
        bold = false;
    }
}


void Editor::on_actioncorsivo_triggered() {
    ui->txt->setFontItalic(ui->actioncorsivo->isChecked());
    italic = ui->actioncorsivo->isChecked();
}

void Editor::on_actionsottolineato_triggered() {
    ui->txt->setFontUnderline(ui->actionsottolineato->isChecked());
    underline = ui->actionsottolineato->isChecked();
}

void Editor::on_actioncolore_triggered() {
    QColor colB = colore->palette().color(QPalette::Background);

    QColor color = QColorDialog::getColor(colB, this, "Scegli un colore");
    if (color.isValid()) {
        ui->txt->setTextColor(color);
        colorS = color.name();
        QString qss = QString("background-color: %1").arg(color.name());
        colore->setStyleSheet(qss);

    }

    checkFont();
}

void Editor::on_actionfont_triggered() {
    /*bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        setTextFont(&font);
    }
    else return;*/
}

void Editor::ShowContextMenu(const QPoint &pos) {
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

void Editor::checkFont() {
    ui->actiongrassetto->setChecked(ui->txt->currentFont().bold());
    bold = ui->txt->currentFont().bold();

    ui->actionsottolineato->setChecked(ui->txt->currentFont().underline());
    underline = ui->txt->currentFont().underline();

    ui->actioncorsivo->setChecked(ui->txt->currentFont().italic());
    italic = ui->txt->currentFont().italic();

    dimS = ui->txt->currentFont().pointSize();
    for (int i = 0; i < 11; i++) {

        if (QString::compare(listaDim.at(i)->text(), QString::number(ui->txt->currentFont().pointSize()),
                             Qt::CaseSensitive) == 0) {
            listaDim.at(i)->setChecked(true);
            break;
        } else {
            listaDim.at(i)->setChecked(false);
        }

    }

    dim->setText(QString::number(ui->txt->currentFont().pointSize()));

    fontS = ui->txt->currentFont().family();
    for (int y = 0; y < 6; y++) {

        if (QString::compare(listaFont.at(y)->text(), ui->txt->currentFont().family(), Qt::CaseSensitive) == 0) {
            listaFont.at(y)->setChecked(true);
            break;
        } else {
            listaFont.at(y)->setChecked(false);
        }

    }

    font->setText(ui->txt->currentFont().family());
    font->setFont(QFont(ui->txt->currentFont().family()));

    QColor colorText = ui->txt->currentCharFormat().foreground().color();

    colorS = ui->txt->currentCharFormat().foreground().color().name();
    for (int z = 0; z < 6; z++) {
        if (listaColor.at(z)->palette().color(QPalette::Background) == colorText) {
            listaColor.at(z)->setChecked(true);
            break;
        } else {

            listaColor.at(z)->setChecked(false);
        }
    }

    QString qss = QString("background-color: %1").arg(colorText.name());
    colore->setStyleSheet(qss);

    ui->txt->alignment();

    if (ui->txt->alignment() == Qt::AlignLeft) {

        ui->actionallineaD->setChecked(false);
        ui->actionallineaC->setChecked(false);
        ui->actionallineaS->setChecked(true);
        ui->actionalineaG->setChecked(false);
        allineamento = "sinistra";
    } else if (ui->txt->alignment() == Qt::AlignRight) {

        ui->actionallineaD->setChecked(true);
        ui->actionallineaC->setChecked(false);
        ui->actionallineaS->setChecked(false);
        ui->actionalineaG->setChecked(false);
        allineamento = "destra";
    } else if (ui->txt->alignment() == Qt::AlignCenter) {

        ui->actionallineaD->setChecked(false);
        ui->actionallineaC->setChecked(true);
        ui->actionallineaS->setChecked(false);
        ui->actionalineaG->setChecked(false);
        allineamento = "centro";
    } else if (ui->txt->alignment() == Qt::AlignJustify) {

        ui->actionallineaD->setChecked(false);
        ui->actionallineaC->setChecked(false);
        ui->actionallineaS->setChecked(false);
        ui->actionalineaG->setChecked(true);
        allineamento = "giustificato";
    }

    QTextCharFormat formato = ui->txt->currentCharFormat();

    if (evidenzia == true) {

        QString email = QString::fromStdString(client_->getProfileInfoLogged().user().email());
        int c = emailL.indexOf(email);
        QString colorU = colorL[c];
        QColor colB = QColor(colorU);
        formato.setBackground(colB);

    } else {
        QColor colB = QColor("white");
        formato.setBackground(colB);
    }
    ui->txt->setCurrentCharFormat(formato);
}

void Editor::changeDim() {
    dimS = dimG->checkedAction()->text().toInt();
    setTextDim(dimS);
    lEdit->clear();
}

void Editor::changeFont() {
    fontS = fontG->checkedAction()->text();
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

void Editor::changeColor() {
    for (int i = 0; i < 6; i++) {
        if (listaColor.at(i)->isChecked()) {
            QColor color1 = listaColor.at(i)->palette().color(QPalette::Background);
            colorS = color1.name();
            ui->txt->setTextColor(color1);

            break;
        }
    }

    coloreM->close();

    checkFont();
}

void Editor::setTextFont(QString fontS) {
    QFont *font1 = new QFont(fontS);
    QTextCursor cursor = ui->txt->textCursor();
    QTextCharFormat format = cursor.blockCharFormat();
    format.setFont(*font1);
    format.setFontPointSize(ui->txt->currentFont().pointSize());
    format.setFontUnderline(underline);
    format.setFontItalic(italic);
    if (bold == true)
        format.setFontWeight(QFont::Bold);
    else
        format.setFontWeight(QFont::Normal);

    QColor colF = colore->palette().color(QPalette::Background);
    format.setForeground(colF);

    QString email = QString::fromStdString(client_->getProfileInfoLogged().user().email());
    int c = emailL.indexOf(email);
    QString colorU = colorL[c];
    if (evidenzia == true) {
        QColor colB = QColor(colorU);
        format.setBackground(colB);
    } else {
        QColor colB = QColor("white");
        format.setBackground(colB);
    }
    //QPalette pal;
    //pal.setColor(QPalette::Foreground, colB);
    //ui->txt->setPalette(pal);

    cursor.setCharFormat(format);
    ui->txt->setTextCursor(cursor);

    font->setText(fontS);
    font->setFont(fontS);
    //checkFont();

}

void Editor::setTextDim(int dim1) {
    QTextCursor cursor = ui->txt->textCursor();
    QTextCharFormat format = cursor.blockCharFormat();
    format.setFont(ui->txt->currentFont().family());
    format.setFontPointSize(dim1);
    format.setFontUnderline(underline);
    format.setFontItalic(italic);
    if (bold == true)
        format.setFontWeight(QFont::Bold);
    else
        format.setFontWeight(QFont::Normal);

    QColor colF = colore->palette().color(QPalette::Background);
    format.setForeground(colF);

    QString email = QString::fromStdString(client_->getProfileInfoLogged().user().email());
    int c = emailL.indexOf(email);
    QString colorU = colorL[c];

    if (evidenzia == true) {
        QColor colB = QColor(colorU);
        format.setBackground(colB);
    } else {
        QColor colB = QColor("white");
        format.setBackground(colB);
    }

    cursor.setCharFormat(format);
    ui->txt->setTextCursor(cursor);
    dim->setText(QString::number(dim1));
    //checkFont();
}

void Editor::setTextDimEdit() {
    dimS = lEdit->text().toInt();
    setTextDim(dimS);
}

void Editor::on_verticalScrollBar_sliderMoved(int position) {
    ui->txt->verticalScrollBar()->setValue(position);
}

void Editor::on_txt_cursorPositionChanged() {
    ui->verticalScrollBar->setPageStep(ui->txt->verticalScrollBar()->pageStep());
    ui->verticalScrollBar->setRange(ui->txt->verticalScrollBar()->minimum(), ui->txt->verticalScrollBar()->maximum());
    ui->verticalScrollBar->setValue(ui->txt->verticalScrollBar()->value());
}

void Editor::resizeEvent(QResizeEvent *event) {
    on_txt_cursorPositionChanged();
}

/*void Editor::on_impostazioni_clicked()
{
    Account account;
    account.setModal(true);
    account.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    account.exec();
}*/

void Editor::on_logout_clicked() {
    emit closeEP();
}

void Editor::readFile() {
    int i = 0;
    int j = 0;
    QTextCursor cursor = ui->txt->textCursor();

    if (!client_->GetFileContent(*file_).empty()) {
        QMessageBox::warning(this, "Errore", "Non è stato possibile leggere il file");
    }

//    std::cout << client_->getSymbolVector().DebugString() << std::endl;
    *_symbolsP = client_->getSymbolVector();

    for (i = 0; i < _symbolsP->symbolvector_size(); i++) {
        symbol_->push_back(Symbol(_symbolsP->symbolvector(i)));
        std::sort(symbol_->begin(), symbol_->end());
    }

    for (i = 0; i < symbol_->size(); i++) {
        QFont *font2;

        if (QString::fromStdString(symbol_->at(i).getFont()) == "")
            //font.setFamily("Arial");
            font2 = new QFont("Arial");
        else
            //font.setFamily(QString::fromStdString(symbol_->at(i).getFont()));
            font2 = new QFont(QString::fromStdString(symbol_->at(i).getFont()));

        QTextCharFormat formato = cursor.blockCharFormat();
        formato.setFont(*font2);

        if (symbol_->at(i).getDimension() == -842150451)
            formato.setFontPointSize(8);
        else
            formato.setFontPointSize(symbol_->at(i).getDimension());

        formato.setFontUnderline(symbol_->at(i).getUnderline());
        formato.setFontItalic(symbol_->at(i).getItalic());
        if (symbol_->at(i).getBold() == true)
            formato.setFontWeight(QFont::Bold);
        else
            formato.setFontWeight(QFont::Normal);


        QColor colB = QColor(QString::fromStdString(symbol_->at(i).getColor()));
        formato.setForeground(colB);

        QString all = QString::fromStdString(symbol_->at(i).getAllineamento());

        if (all == "destra") {
            ui->txt->setAlignment(Qt::AlignRight);
            //formato.setVerticalAlignment(Qt::AlignRight);
        } else if (all == "sinistra") {
            ui->txt->setAlignment(Qt::AlignLeft);
        } else if (all == "centro") {
            ui->txt->setAlignment(Qt::AlignCenter);
        } else if (all == "giustificato") {
            ui->txt->setAlignment(Qt::AlignJustify);
        }

        cursor.setCharFormat(formato);
        //QPalette pal;
        //pal.setColor(QPalette::Foreground, colB);


        /*QFont font;
        font.setBold(symbol_->at(i).getBold());
        font.setUnderline(symbol_->at(i).getUnderline());
        font.setItalic(symbol_->at(i).getItalic());
        if(symbol_->at(i).getDimension() == -842150451)
            font.setPointSize(8);
        else
            font.setPointSize(symbol_->at(i).getDimension());
        if(QString::fromStdString(symbol_->at(i).getFont()) == "")
            font.setFamily("Arial");
        else
            font.setFamily(QString::fromStdString(symbol_->at(i).getFont()));

        //QString qss = QString("color: %1").arg(QString::fromStdString(symbol_->at(i).getColor()));
        //colore->setStyleSheet(qss);
        //font.setStyle(qss);
        //ui->txt->setTextColor(QString::fromStdString(symbol_->at(i).getColor()));
        QPalette palette = ui->txt->palette();
        QColor color2 = QColor(QString::fromStdString(symbol_->at(i).getColor()));
        palette.setColor(QPalette::Foreground, color2);*/

        //ui->txt->setPalette(pal);
        cursor.setPosition(i);
        ui->txt->setTextCursor(cursor);
        //ui->txt->setCurrentFont(font);
        //ui->txt->setPalette(palette);
        char y = symbol_->at(i).getCharacter();
        //j = atoi(y);
        ui->txt->insertPlainText(QChar(y));


        //QTextCursor cur = ui->txt->textCursor();
        //cur.movePosition(QTextCursor::PreviousCharacter,QTextCursor::KeepAnchor,1);


        /* switch(j)
         {
             case (-30):
                 ui->txt->insertPlainText("\n");
                 break;
             case (9):
                 ui->txt->insertPlainText("\t");
                 break;
             case (-61):
                 ui->txt->insertPlainText("è");
                 break;
             case (-62):
                 ui->txt->insertPlainText("°");
                 break;
             default:
                 char p = std::stoi(symbol.character());
                 ui->txt->insertPlainText(QChar(p));
         }*/

        //ui->txt->setPlainText(symbol.character().c_str());
        //ui->txt->setPlainText(QChar(t));
    }
}

void Editor::insertFile(char r) {
    QTextCursor cur = ui->txt->textCursor();
    std::vector<int> pos;
    pos.push_back(cur.position());

    //Symbol *symbol = new Symbol(r, client_->getProfileInfoLogged().user().email(), pos);
    //client_->InsertSymbols(*symbol, false);

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

bool Editor::eventFilter(QObject *obj, QEvent *event) {
    if (insert) {
        const std::regex pattern(R"(\w+|\W)");
        if (obj == ui->txt) {
            if (event->type() == QEvent::KeyPress) {
                QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(event);
//                 std::cout << keyEvent->key() << std::endl;
                if (keyEvent->key() == Qt::Key_Up) {
                    qDebug() << "lineEdit -> Qt::Key_Up";
                    return true;
                } else if (keyEvent->key() == Qt::Key_Down) {
                    qDebug() << "lineEdit -> Qt::Key_Down";
                    return true;
                } else if (keyEvent->key() == Qt::Key_Delete || keyEvent->key() == Qt::Key_Cancel ||
                           keyEvent->key() == Qt::Key_Backspace) {
                    std::cout << "cancella\n";
                    localErase(ui->txt->textCursor().position() - 1);
                } else if (keyEvent->key() == Qt::Key_Aacute || keyEvent->key() == Qt::Key_Oacute ||
                           keyEvent->key() == Qt::Key_Iacute || keyEvent->key() == Qt::Key_Uacute ||
                           keyEvent->key() == Qt::Key_Eacute ||
                           keyEvent->key() == Qt::Key_Agrave || keyEvent->key() == Qt::Key_Egrave ||
                           keyEvent->key() == Qt::Key_Igrave ||
                           keyEvent->key() == Qt::Key_Ograve || keyEvent->key() == Qt::Key_Ugrave) {
                    localInsert(ui->txt->textCursor().position(), keyEvent->text().toStdString()[0]);
                } else if (std::regex_match(keyEvent->text().toStdString(), pattern)) {
                    localInsert(ui->txt->textCursor().position(), keyEvent->text().toStdString()[0]);
                }
            }
            return false;
        }
        return QMainWindow::eventFilter(obj, event);
    }
    return false;
}

void Editor::localInsert(int index, char value) {

    if (insert) {
        std::vector<int> posPre = {0};
        std::vector<int> posPost = {2};

        if (symbol_->size() < index)
            //se cerco di inserire a un indice oltre la fine, inserisco alla fine
            index = symbol_->size();

        if (symbol_->size() == index) {
            if (index != 0) {
                posPre = symbol_->at(index - 1).getPos();
                posPost = {(posPre.at(posPre.size() - 1) + 2)};
            }
        } else {
            if (index != 0)
                posPre = symbol_->at(index - 1).getPos();

            posPost = symbol_->at(index).getPos();
        }

#if debug == 1
        //stampa il range in cui deve essere contenuto l'indice frazionario di @value, ad es 0<c<2
   for (int i = 0; i < posPre.size(); i++) {
       std::cout << posPre.at(i);
       if (i == 0 && i != posPre.size() - 1)
           std::cout << ",";
   }
   std::cout << "<" << value << "<";
   for (int i = 0; i < posPost.size(); i++) {
       std::cout << posPost.at(i);
       if (i == 0 && i != posPost.size() - 1)
           std::cout << ",";
   }
#endif

        int newVal;
        bool isPreBigger = posPre.size() >= posPost.size();
        std::vector<int> posNew = isPreBigger ? posPre : posPost;
        unsigned int maxI = posNew.size() - 1;

        if (posPre.size() == posPost.size()) {
            newVal = (posPre.at(maxI) + posPost.at(maxI)) / 2;
            if (newVal != posPre.at(maxI)) {
                //stiamo inserendo tra 1 e 3
                posNew.at(maxI) = newVal;
            } else {
                //stiamo inserendo tra 3,4 e 3,5
                posNew.push_back(5);
            }
        } else {
            if (posNew.at(maxI) == 1) {
                //stiamo inserendo tra 4 e 4,1
                posNew.at(maxI) = 0;
                posNew.push_back(5);
            } else if (posNew.at(maxI) == 9) {
                //stiamo inserendo tra 3,9 e 4
                posNew.push_back(5);
            } else {
                //stiamo inserendo tra 3,477777 e 3,5
                newVal = isPreBigger ? (posNew.at(maxI) + 10) / 2 : posNew.at(maxI) / 2;
                posNew.at(maxI) = newVal;
            }
        }

#if debug == 1
        // stampa l'indice frazionario scelto
   std::cout << "  -->  ";
   for (int j = 0; j < posNew.size(); ++j) {
       std::cout << posNew[j];
       if (j == 0 && j != posNew.size() - 1)
           std::cout << ",";
   }
   std::cout << std::endl;
#endif

        std::string uniqueId = client_->getProfileInfoLogged().user().email();
        Symbol symbol(value, uniqueId, posNew, bold, underline, italic, dimS, colorS.toStdString(), fontS.toStdString(),
                      allineamento.toStdString());
        symbol_->insert(symbol_->begin() + index, 1, symbol);
        protobuf::Symbol s = symbol.makeProtobufSymbol();
//         std::cout << symbol.makeProtobufSymbol().DebugString() << std::endl;
        client_->InsertSymbols(symbol, false);
    }


}

/**
 * Questo metodo elimina dal vettore _symbols l’elemento all’indice indicato, prepara un oggetto
 * di tipo Message in cui descrive l’azione compiuta e lo affida all’oggetto _server affinché lo
 * consegni agli altri SharedEditor.
 *
 * @param index
 */
void Editor::localErase(int index) {
    if (insert) {
        if (symbol_->empty())
            return;

        if (index >= symbol_->size())
            index = symbol_->size() - 1;
        std::cout << symbol_->at(index).getCharacter() << "\n" << symbol_->at(index).getUniqueId() << "\n";
        client_->InsertSymbols(symbol_->at(index), true);
//        std::cout << symbol_->at(index).makeProtobufSymbol().DebugString() << std::endl;
        symbol_->erase(std::find(symbol_->begin(), symbol_->end(), symbol_->at(index)));
    }

    /*
      Message msg(_symbols.at(index), _siteId, true);
      _symbols.erase(_symbols.begin() + index);
      _server.send(msg);*/

}

void Editor::on_evidenzia_clicked() {
    insert = false;
    ui->txt->clear();
    /*if(ui->actionevidenzia_utente->isChecked() == true)
    {
        ui->txt->clear();
        QTextCursor cursor = ui->txt->textCursor();
        cursor.setPosition(0);
        ui->txt->setTextCursor(cursor);
    } else{
        readFile();
    }*/
    int i = 0;
    int j = 0;
    QTextCursor cursor = ui->txt->textCursor();

//    std::cout << client_->getSymbolVector().DebugString() << std::endl;

    for (i = 0; i < symbol_->size(); i++) {
        QFont *font2;

        if (QString::fromStdString(symbol_->at(i).getFont()) == "")
            //font.setFamily("Arial");
            font2 = new QFont("Arial");
        else
            //font.setFamily(QString::fromStdString(symbol_->at(i).getFont()));
            font2 = new QFont(QString::fromStdString(symbol_->at(i).getFont()));

        QTextCharFormat formato = cursor.blockCharFormat();
        formato.setFont(*font2);

        if (symbol_->at(i).getDimension() == -842150451)
            formato.setFontPointSize(8);
        else
            formato.setFontPointSize(symbol_->at(i).getDimension());

        formato.setFontUnderline(symbol_->at(i).getUnderline());
        formato.setFontItalic(symbol_->at(i).getItalic());
        if (symbol_->at(i).getBold())
            formato.setFontWeight(QFont::Bold);
        else
            formato.setFontWeight(QFont::Normal);


        QColor colB = QColor(QString::fromStdString(symbol_->at(i).getColor()));
        formato.setForeground(colB);

        if (!evidenzia) {
            QString email = QString::fromStdString(symbol_->at(i).getUniqueId());

            int c = emailL.indexOf(email);
            QString colorU = colorL[c];
            QColor color3 = QColor(colorU);
            formato.setBackground(color3);
            //palette.setColor(QPalette::Highlight, color3);
        }

        QString all = QString::fromStdString(symbol_->at(i).getAllineamento());

        if (all == "destra") {
            ui->txt->setAlignment(Qt::AlignRight);
            //formato.setVerticalAlignment(Qt::AlignRight);
        } else if (all == "sinistra") {
            ui->txt->setAlignment(Qt::AlignLeft);
        } else if (all == "centro") {
            ui->txt->setAlignment(Qt::AlignCenter);
        } else if (all == "giustificato") {
            ui->txt->setAlignment(Qt::AlignJustify);
        }

        cursor.setCharFormat(formato);

        /*QFont font;
        font.setBold(symbol_->at(i).getBold());
        font.setUnderline(symbol_->at(i).getUnderline());
        font.setItalic(symbol_->at(i).getItalic());
        if(symbol_->at(i).getDimension() == -842150451)
            font.setPointSize(8);
        else
            font.setPointSize(symbol_->at(i).getDimension());
        if(QString::fromStdString(symbol_->at(i).getFont()) == "")
            font.setFamily("Arial");
        else
            font.setFamily(QString::fromStdString(symbol_->at(i).getFont()));
        QPalette palette = ui->txt->palette();
        QColor color2 = QColor(QString::fromStdString(symbol_->at(i).getColor()));
        palette.setColor(QPalette::Foreground, color2);*/

        cursor.setPosition(i);
        ui->txt->setTextCursor(cursor);
        //ui->txt->setCurrentFont(font);
        //ui->txt->setPalette(palette);
        char y = symbol_->at(i).getCharacter();
        ui->txt->insertPlainText(QChar(y));
    }
/*
    for(i=0; i<_symbolsP2->symbolvector_size(); i++) {
        QFont font;
        font.setBold(symbol2_->at(i).getBold());
        font.setUnderline(symbol2_->at(i).getUnderline());
        font.setItalic(symbol2_->at(i).getItalic());
        if (symbol2_->at(i).getDimension() == -842150451)
            font.setPointSize(8);
        else
            font.setPointSize(symbol2_->at(i).getDimension());
        if (QString::fromStdString(symbol2_->at(i).getFont()) == "")
            font.setFamily("Arial");
        else
            font.setFamily(QString::fromStdString(symbol2_->at(i).getFont()));

        //QString qss = QString("color: %1").arg(QString::fromStdString(symbol_->at(i).getColor()));
        //colore->setStyleSheet(qss);
        //font.setStyle(qss);
        //ui->txt->setTextColor(QString::fromStdString(symbol_->at(i).getColor()));
        QPalette palette = ui->txt->palette();
        QColor color2 = QColor(QString::fromStdString(symbol2_->at(i).getColor()));
        palette.setColor(QPalette::Foreground, color2);

        /*if(ui->actionevidenzia_utente->isChecked() == false)
        {
            QString email = QString::fromStdString(symbol_->at(i).getUniqueId());

            int c = emailL.indexOf(email);
            QString colorU = colorL[c];
            QColor color3 = QColor(colorU);

            palette.setColor(QPalette::Highlight, color3);
        }*/
/*
        cursor.setPosition(i);
        ui->txt->setTextCursor(cursor);
        ui->txt->setCurrentFont(font);
        ui->txt->setPalette(palette);
        char y = symbol2_->at(i).getCharacter();
        //j = atoi(y);
        ui->txt->insertPlainText(QChar(y));

    }*/
    QTextCharFormat formato2 = ui->txt->currentCharFormat();
    QString email = QString::fromStdString(client_->getProfileInfoLogged().user().email());
    int c = emailL.indexOf(email);
    QString colorU = colorL[c];
    auto colB = QColor(colorU);
    formato2.setBackground(colB);
    ui->txt->setCurrentCharFormat(formato2);

    evidenzia = !evidenzia;

    insert = true;
}

void Editor::add_async_symbol() {
    std::cout << "Buonasera"<< std::endl;
    ui->txt->setText("");
    this->readFile();
}


void Editor::AsyncCompleteRpc(CharacterClient *pClient) {
    void *got_tag;
    bool ok = false;

    // Block until the next result is available in the completion queue "cq".
    while (!exit_thread_flag) {
        while (pClient->cq_.Next(&got_tag, &ok)) {
            std::cout << got_tag << std::endl;
            static_cast<AsyncClientGetSymbols *>(got_tag)->HandleAsync(ok);
            bool fieldsEqual = std::equal(asyncSymbol.pos().begin(), asyncSymbol.pos().end(), static_cast<AsyncClientGetSymbols *>(got_tag)->GetSymbol().pos().begin());
            if (ok) {
                asyncSymbol = static_cast<AsyncClientGetSymbols *>(got_tag)->GetSymbol();
                emit newAsync();
            }
        }
    }
}

void Editor::startAsyncClient() {
    if(!client_->getAsyncfun()) {
        std::thread([this] { this->AsyncCompleteRpc(client_); }).detach();
        client_->setAsyncfun();
        std::cout << client_->getAsyncfun() << std::endl;
    }
}
