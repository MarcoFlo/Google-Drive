#include "splashscreen.h"
#include "ui_splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);
    QTimer::singleShot(4000, this, SLOT(closeSplash()));

}

SplashScreen::~SplashScreen()
{
    delete ui;
}

void SplashScreen::closeSplash()
{
    hide();
    emit openL();
}
