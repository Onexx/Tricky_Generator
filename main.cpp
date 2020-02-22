#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "data.h"
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap("Materials/Splash.png"));
    splash->show();  // Showing splash screen
    w.setWindowTitle(QString("Generator V." + QString::number(Data::version) +
                             "." + QString::number(Data::build)));
    QTimer::singleShot(2500, splash, SLOT(close()));  // Closing spash screen
    QTimer::singleShot(2500, &w, SLOT(show()));       // Showing menu
    return a.exec();
}
