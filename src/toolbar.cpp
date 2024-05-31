#include "toolbar.h"

Toolbar::Toolbar(QWidget *parent)
    : QWidget(parent)
{
}

Toolbar::~Toolbar()
{
}

void Toolbar::initData()
{
    if (!toolButtons.empty())
    {
        toolButtons.clear();
    }

    auto buttonAdd = new QToolButton(this);
    buttonAdd->setProperty("toolName", "add");

    auto buttonDel = new QToolButton(this);
    buttonDel->setProperty("toolName", "del");

    auto buttonRun = new QToolButton(this);
    buttonRun->setProperty("toolName", "run");

    auto buttonStop = new QToolButton(this);
    buttonStop->setProperty("toolName", "stop");

    toolButtons.append(buttonAdd);
    toolButtons.append(buttonDel);
    toolButtons.append(buttonRun);
    toolButtons.append(buttonStop);    
}

void Toolbar::initUi()
{
    if (hLayout == nullptr)
    {
        hLayout = new QHBoxLayout(this);
    }

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
    }

    if (toolButtons.empty())
    {
        return;
    }
    
    for (auto button : toolButtons)
    {
        hLayout->addWidget(button);
    }
}

void Toolbar::onToolButtonClicked()
{
    auto button = qobject_cast<QToolButton*>(sender());
    if (button == nullptr)
    {
        return;
    }

    QString toolName = button->property("toolName").toString();
    if (toolName == "add")
    {
        qDebug() << "Add button clicked";
    }
    else if (toolName == "del")
    {
        qDebug() << "Del button clicked";
    }
    else if (toolName == "run")
    {
        qDebug() << "Run button clicked";
    }
    else if (toolName == "stop")
    {
        qDebug() << "Stop button clicked";
    }
}



