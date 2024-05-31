#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filterlistview.h"
#include "filtergraphview.h"
#include "filtercompareview.h"

#include <iostream>

#include <QUrl>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>

#define FILTER_COMPARE_VIEW 

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUi();
    initConnect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi()
{
    setWindowTitle("FFmpegBox");
    setMinimumSize(800, 600);

#ifdef FILTER_LIST_VIEW
    initFilterListView();
#elif defined(FILTER_COMPARE_VIEW)
    initFilterCompareView();
#endif
}

void MainWindow::initFilterListView()
{
    QHBoxLayout* hLayout = new QHBoxLayout(ui->centralwidget);

    FilterListView* filterListView = new FilterListView(ui->centralwidget);
    filterListView->initUi();

    hLayout->addWidget(filterListView);

    QFrame* line = new QFrame(ui->centralwidget);
    line->setFrameShape(QFrame::VLine);  
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);
    hLayout->addWidget(line); 

    FilterGraphView* filterGraphView = new FilterGraphView(ui->centralwidget);
    hLayout->addWidget(filterGraphView);
}

void MainWindow::initFilterCompareView()
{
    QVBoxLayout* vLayout = new QVBoxLayout(ui->centralwidget);

    FilterCompareView* filterCompareView = new FilterCompareView(ui->centralwidget);
    filterCompareView->initUi();
    filterCompareView->initData();

    vLayout->addWidget(filterCompareView);

    QPushButton *btnStart = new QPushButton("Start", ui->centralwidget);
    QPushButton *btnStop = new QPushButton("Stop", ui->centralwidget);

    btnStart->setFixedSize(100, 30);
    btnStop->setFixedSize(100, 30);
    vLayout->addWidget(btnStart);
    vLayout->addWidget(btnStop);

    connect(btnStart, &QPushButton::clicked, [filterCompareView](){
        filterCompareView->start();
    });
    connect(btnStop, &QPushButton::clicked, [filterCompareView](){
        filterCompareView->stop();
    });
}

void MainWindow::initTestView()
{
    QVBoxLayout* vLayout = new QVBoxLayout(ui->centralwidget);

    QPushButton *btnStart = new QPushButton("Start", ui->centralwidget);
    QPushButton *btnStop = new QPushButton("Stop", ui->centralwidget);

    btnStart->setFixedSize(100, 30);
    btnStop->setFixedSize(100, 30);
    vLayout->addWidget(btnStart);
    vLayout->addWidget(btnStop);

    connect(btnStart, &QPushButton::clicked, [](){
        std::cout << "btnStart clicked" << std::endl;
    });
    connect(btnStop, &QPushButton::clicked, [](){
        std::cout << "btnStop clicked" << std::endl;
    });
}

void MainWindow::initConnect()
{}
