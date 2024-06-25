#include "mainwindow.h"
#include "tablebox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // MainWindow w;
    // w.show();

    TableBox tableBox;
    tableBox.initUi();
    tableBox.initData();
    tableBox.initConnect();
    
    tableBox.show();

    return a.exec();
}
