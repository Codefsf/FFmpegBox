#include "filtercompareview.h"
#include "ffmpegfilter.h"

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
}

void FilterCompareView::start()
{
    
}

void FilterCompareView::stop()
{
    
}