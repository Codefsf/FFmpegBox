#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QQmlApplicationEngine>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // ui->setupUi(this);

    QQmlApplicationEngine engine;
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty())
            return;
        setCentralWidget(qobject_cast<QWidget*>(engine.rootObjects().first()));

    InitUi();
    InitConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi()
{
    setWindowTitle("FFmpegBox");

}

void MainWindow::InitConnect()
{}
