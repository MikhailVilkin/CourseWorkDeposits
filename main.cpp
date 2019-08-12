#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(745, 500);
    w.setWindowTitle("ВКЛАД");
    w.show();

    return a.exec();
}
