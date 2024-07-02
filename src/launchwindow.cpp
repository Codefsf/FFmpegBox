#include "launchwindow.h"

#include <QPushButton>
#include <QGridLayout>

LaunchItem::LaunchItem(QWidget* parent)
    : QWidget(parent)
{
}

LaunchItem::~LaunchItem()
{
}

void LaunchItem::init()
{
    this->resize(100, 100);
    this->setStyleSheet("border: 5px solid black");

    QPushButton* startButton = new QPushButton(this);
    startButton->setText("Start");
    startButton->setGeometry(10, 10, 80, 30);

    QPushButton* stopButton = new QPushButton(this);
    stopButton->setText("Stop");
    stopButton->setGeometry(10, 50, 80, 30);

    connect(startButton, &QPushButton::clicked, this, [=]() {
        start();
        startButton->hide();
        stopButton->show();
    });

    connect(stopButton, &QPushButton::clicked, this, [=]() {
        stop();
        startButton->show();
        stopButton->hide();
    });
}

void LaunchItem::setStartFunc(LaunchItemFunc func)
{
    m_startFunc = func;
}

void LaunchItem::start()
{
    if (m_startFunc)
    {
        m_startFunc(true);
    }
}

void LaunchItem::stop()
{
    if (m_startFunc)
    {
        m_startFunc(false);
    }
}

LaunchWindow::LaunchWindow(QWidget* parent)
    : QWidget(parent)
{
}

LaunchWindow::~LaunchWindow()
{
}

void LaunchWindow::init()
{
    this->resize(800, 600);

    QGridLayout* gridLayout = new QGridLayout(this);
    gridLayout->setContentsMargins(10, 10, 10, 10);
    gridLayout->setSpacing(10);
    
    for (int i = 0; i < 10; ++i)
    {
        LaunchItem* launchItem = new LaunchItem(this);
        launchItem->init();
        launchItem->setStartFunc([=](bool start) {
            if (start)
            {
                launchItem->setStyleSheet("border: 5px solid red");
            }
            else
            {
                launchItem->setStyleSheet("border: 5px solid black");
            }
        });
        gridLayout->addWidget(launchItem, i / 5, i % 5);
        m_launchItemList.append(launchItem);
    }
}