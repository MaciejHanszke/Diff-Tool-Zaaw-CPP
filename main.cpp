#include "mainwindow.h"
#include <QApplication>
#include "lcs.h"

int main(int argc, char *argv[])
{
    Lcs l;
    l.test();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
