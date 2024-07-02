#include "mainwindow.h"
#include "tablebox.h"
#include "paintbox.h"
#include "treebox.h"
#include "launchwindow.h"
#include "containerbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ContainerBox containerBox;
    containerBox.init();
    containerBox.show();

    return a.exec();
}
