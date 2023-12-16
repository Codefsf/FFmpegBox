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

    QHBoxLayout* hLayout = new QHBoxLayout(ui->centralwidget);

    FilterListView* filterListView = new FilterListView(ui->centralwidget);
    filterListView->InitUi();

    hLayout->addWidget(filterListView);

    QFrame* line = new QFrame(ui->centralwidget);
    line->setFrameShape(QFrame::VLine);  
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);
    hLayout->addWidget(line); 

    FilterGraphView* filterGraphView = new FilterGraphView(ui->centralwidget);
    filterGraphView->InitUi();
    hLayout->addWidget(filterGraphView);
}

void MainWindow::InitConnect()
{}
