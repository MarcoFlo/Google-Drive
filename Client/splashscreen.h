#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QDialog>
#include <QTimer>
#include "loginpage.h"

namespace Ui {
class SplashScreen;
}

class SplashScreen : public QDialog
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();

signals:
    void openL();

private slots:
    void closeSplash();

private:
    Ui::SplashScreen *ui;
    LoginPage *l;
};

#endif // SPLASHSCREEN_H
