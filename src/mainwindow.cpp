#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filterlistview.h"
#include "filtergraphview.h"

#include <QUrl>
#include <QHBoxLayout>
#include <QFrame>

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
    setMinimumSize(800, 600);

    QHBoxLayout* hLayout = new QHBoxLayout();

    FilterListView* filterListView = new FilterListView();
    filterListView->InitUi();
    hLayout->addWidget(filterListView);

    filterListView->setStyleSheet("background-color: red;");

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::VLine);  
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);
    hLayout->addWidget(line); 

    FilterGraphView* filterGraphView = new FilterGraphView();
    filterGraphView->InitUi();
    hLayout->addWidget(filterGraphView);

    filterGraphView->setStyleSheet("background-color: blue;");

    ui->centralwidget->setLayout(hLayout);
}

void MainWindow::InitConnect()
{}
