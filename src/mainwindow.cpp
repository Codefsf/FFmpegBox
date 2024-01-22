#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "filterlistview.h"
#include "filtergraphview.h"
#include "filtercompareview.h"

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

    vLayout->addWidget(filterCompareView);

    QPushButton *btn = new QPushButton("Start", ui->centralwidget);
    btn->setFixedSize(100, 30);
    vLayout->addWidget(btn);

    connect(btn, &QPushButton::clicked, [filterCompareView](){
        filterCompareView->start();
    });
}

void MainWindow::initConnect()
{}
