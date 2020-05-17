#include "splashscreen.h"
#include "ui_splashscreen.h"
#include <QPixmap>

SplashScreen::SplashScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);
    QTimer::singleShot(2000, this, SLOT(closeSplash()));
    setupUI();
}



SplashScreen::~SplashScreen()
{
    delete ui;
}

void SplashScreen::setupUI()
{
    QPixmap *pixmap = new QPixmap(":/images/img/scrittaB.png");
    ui->label->setPixmap(*pixmap);
}