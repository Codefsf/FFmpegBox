#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QUrl>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
