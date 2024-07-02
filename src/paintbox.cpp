#include "paintbox.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QFrame>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QDateTime>

PaintBox::PaintBox(QWidget* parent)
    : QWidget(parent)
{
}

PaintBox::~PaintBox()
{
}

void PaintBox::init()
{
    initData();
    initUi();
    initConnect();
}

void PaintBox::initData()
{
    m_paintTypeMap = {
        {PaintType::Ball, "Ball"},
        {PaintType::Rain, "Rain"},
        {PaintType::Close, "Close"}
    };
}

void PaintBox::initUi()
{
    this->resize(800, 600);
    m_timer = new QTimer(this);
    m_timer->setInterval(1000 / 60);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        this->update();
    });

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    m_paintWidget = new QWidget(this);
    m_paintWidget->setFixedSize(800, 500);
    vLayout->addWidget(m_paintWidget);

    QWidget* settingWidget = new QWidget(this);
    settingWidget->setFixedSize(800, 100);
    vLayout->addWidget(settingWidget);

    QHBoxLayout* hLayout = new QHBoxLayout(settingWidget);
    hLayout->setContentsMargins(10, 10, 10, 10);

    m_comboBox = new QComboBox(settingWidget);
    for (auto iter = m_paintTypeMap.begin(); iter != m_paintTypeMap.end(); ++iter)
    {
        m_comboBox->addItem(iter.value(), QVariant::fromValue(iter.key()));
    }

    QPushButton* startBtn = new QPushButton("Start", settingWidget);
    QPushButton* stopBtn = new QPushButton("Stop", settingWidget);
    connect(startBtn, &QPushButton::clicked, this, [this]() {
        m_timer->start();
    });
    connect(stopBtn, &QPushButton::clicked, this, [this]() {
        m_timer->stop();
    });

    hLayout->addWidget(m_comboBox);
    hLayout->addWidget(startBtn);
    hLayout->addWidget(stopBtn);
}

void PaintBox::initConnect()
{
}

void PaintBox::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    auto paintType = m_comboBox->currentData().value<PaintType>();
    switch (paintType)
    {
    case PaintType::Ball:
        paintBall(painter);
        break;
    case PaintType::Rain:    
        paintRain(painter);
        break;
    case PaintType::Close:
        paintClose(painter);
        break;
    default:
        break;
    }
}

void PaintBox::paintBall(QPainter& painter)
{
    painter.setBrush(QColor(255, 255, 255));
    painter.drawRect(0, 0, this->width(), m_paintWidget->height());

    int r = 30;

    static int x = 100;
    static int y = 100;
    static int dx = 5;
    static int dy = 5;
    x += dx;
    y += dy;
    if (x < 0 || x + r * 2 > m_paintWidget->width())
    {
        dx = -dx;
    }

    if (y < 0 || y + r * 2 > m_paintWidget->height())
    {
        dy = -dy;
    }

    painter.setBrush(QColor(0, 0, 255));
    painter.drawEllipse(x, y, r * 2, r * 2);
}

void PaintBox::paintRain(QPainter& painter)
{
    

}

void PaintBox::paintClose(QPainter& painter)
{

}