#include "toolbar.h"

Toolbar::Toolbar(QWidget *parent)
    : QWidget(parent)
{
}

Toolbar::~Toolbar()
{
}

void Toolbar::init()
{
    initData();
    initUi();
    initConnect();
}

void Toolbar::initData()
{
    if (!toolButtons.empty())
    {
        toolButtons.clear();
    }

    auto buttonAdd = new QToolButton(this);
    buttonAdd->setProperty("toolName", "add");
    buttonAdd->setText("Add");

    auto buttonDel = new QToolButton(this);
    buttonDel->setProperty("toolName", "del");
    buttonDel->setText("Del");

    auto buttonStart = new QToolButton(this);
    buttonStart->setProperty("toolName", "start");
    buttonStart->setText("Start");

    auto buttonStop = new QToolButton(this);
    buttonStop->setProperty("toolName", "stop");
    buttonStop->setText("Stop");

    toolButtons.append(buttonAdd);
    toolButtons.append(buttonDel);
    toolButtons.append(buttonStart);
    toolButtons.append(buttonStop);    
}

void Toolbar::initUi()
{
    if (hLayout == nullptr)
    {
        hLayout = new QHBoxLayout(this);
    }

    this->setStyleSheet("background-color: grey;");
    this->setFixedHeight(50);

    initToolButtons();

    setLayout(hLayout);
}

void Toolbar::initConnect()
{
    for (auto button : toolButtons)
    {
        connect(button, &QToolButton::clicked, this, &Toolbar::onToolButtonClicked);
    }
}

void Toolbar::initToolButtons()
{
    if (hLayout == nullptr)
    {
        hLayout = new QHBoxLayout(this);
        hLayout->setSpacing(20);
        hLayout->setAlignment(Qt::AlignCenter);
    }

    if (toolButtons.empty())
    {
        return;
    }
    
    hLayout->addStretch();
    for (auto button : toolButtons)
    {
        hLayout->addWidget(button);
    }
    hLayout->addStretch();
}

void Toolbar::onToolButtonClicked()
{
    auto button = qobject_cast<QToolButton*>(sender());
    if (button == nullptr)
    {
        return;
    }

    QString toolName = button->property("toolName").toString();
    if (toolName.isEmpty())
    {
        return;
    }

    qDebug() << "Tool button clicked: " << toolName;
    emit toolButtonClicked(toolName);
}



