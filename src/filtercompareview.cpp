#include "filtercompareview.h"
#include "ffmpegfilter.h"
#include "ffmpegformat.h"

#include <iostream>

#include <QHBoxLayout>
#include <QSplitter>

FilterCompareView::FilterCompareView(QWidget *parent) : 
    QWidget(parent)
{
    
}

FilterCompareView::~FilterCompareView()
{
    if (m_filter != nullptr)
    {
        m_filter->unInit();
        delete m_filter;
        m_filter = nullptr;
    }

    if (m_format != nullptr)
    {
        m_format->unInit();
        delete m_format;
        m_format = nullptr;
    }
}

void FilterCompareView::initUi()
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    m_inputWidget = new QWidget(this);
    m_outputWidget = new QWidget(this);
    m_inputWidget->setStyleSheet("background-color: grey;");
    m_outputWidget->setStyleSheet("background-color: grey;");

    layout->addWidget(m_inputWidget);
    layout->addWidget(m_outputWidget);

    layout->setSpacing(50);
    setLayout(layout);
}

void FilterCompareView::initData()
{
    m_filter = new FFmpegFilter();
    m_filter->init("nullsrc");

    m_format = new FFmpegFormat();
    m_format->init();
}

int FilterCompareView::start()
{
    std::cout << "FilterCompareView::start" << std::endl;

    int ret = 0;
    if (!m_filter)
    {
        std::cout << "m_filter is nullptr" << std::endl;
        return -1;
    }
    
    if (!m_format)
    {
        std::cout << "m_format is nullptr" << std::endl;
        return -1;
    }
    
    ret = m_format->openInput("test.mp4");
    if (ret < 0)
    {
        std::cout << "m_format->openInput failed, error code: " << ret << std::endl;
        return ret;
    }

    return 0;
}

void FilterCompareView::stop()
{
    
}