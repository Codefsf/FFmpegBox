#include "containerboxpaint.h"

#include <QDebug>
#include <QPainter>

ContainerBoxPaint::ContainerBoxPaint(QWidget* parent)
    : QWidget(parent)
{
}

ContainerBoxPaint::~ContainerBoxPaint()
{
}

void ContainerBoxPaint::init()
{
    initUi();
    initConnect();
}

void ContainerBoxPaint::initData(const PaintData& data)
{
    m_paintData = data;
}

void ContainerBoxPaint::initUi()
{
    this->setStyleSheet("ContainerBoxPaint { border: 1px solid black; }");
}

void ContainerBoxPaint::initConnect()
{
    //TODO NOTHING
}

void ContainerBoxPaint::setVectorData(std::shared_ptr<std::vector<std::string>> data)
{
    m_paintData.vectorDataPtr = data;
}

void ContainerBoxPaint::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0, 0, width(), height());

    if (m_paintData.vectorDataPtr != nullptr)
    {
        paintVectorData(painter);
    }
    
}

void ContainerBoxPaint::paintVectorData(QPainter& painter)
{
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0, 0, width(), height());

    int x = 10;
    int y = 10;
    int width = 50;
    int height = 50;
    int space = 0;
    int row = 0;
    int col = 0;
    int count = 0;

    for (const auto& str : *m_paintData.vectorDataPtr)
    {
        painter.setPen(QPen(Qt::black, 1));
        painter.setBrush(QBrush(Qt::white));
        painter.drawRect(x + col * (width + space), y + row * (height + space), width, height);
        painter.drawText(x + col * (width + space), y + row * (height + space), width, height, Qt::AlignCenter, QString::fromStdString(str));

        col++;
        count++;
        if (count % 10 == 0)
        {
            row++;
            col = 0;
        }
    }
}