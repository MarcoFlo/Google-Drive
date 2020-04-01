#include "splashscreen.h"
#include "ui_splashscreen.h"


SplashScreen::SplashScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);
    //QTimer::singleShot(2000, this, SLOT(closeSplash()));

}

SplashScreen::~SplashScreen()
{
    delete ui;
}

