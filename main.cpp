#include "mainwindow.h"
#include "linksqLite.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow loginWindow;
    loginWindow.show();

    return a.exec();//循环
}
