#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class SplashScreen;
}

class SplashScreen : public QDialog
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();
    void setupUI();

private:
    Ui::SplashScreen *ui;


};

#endif // SPLASHSCREEN_H
