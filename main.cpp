#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.loadFile("/home/dianas/test1.asm");
    w.curent_file = "/home/dianas/test1.asm";

    w.show();
    return a.exec();
}

