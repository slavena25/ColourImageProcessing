#include "mainwindow.h"
#include <QtWidgets>
#include <QtGui>
#include <QHBoxLayout>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
