#include "filtercompareview.h"

#include <QHBoxLayout>
#include <QSplitter>

FilterCompareView::FilterCompareView(QWidget *parent) : 
    QWidget(parent)
{
    
}

FilterCompareView::~FilterCompareView()
{
    
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

void FilterCompareView::start()
{
    
}