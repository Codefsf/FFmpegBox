#include "filtergraphitem.h"

#include <QMenu>
#include <QContextMenuEvent>
#include <QLabel>
#include <QVBoxLayout>

FilterGraphItem::FilterGraphItem(QWidget *parent)
    : QWidget(parent)
{
}

FilterGraphItem::~FilterGraphItem()
{
}

void FilterGraphItem::setItemName(const QString &name)
{
    m_info.name = name;
}

void FilterGraphItem::setSize(const SizeType &sizeType)
{
    m_sizeType = sizeType;
}

void FilterGraphItem::setInfo(const FilterGraphItemInfo &info)
{
    m_info = info;
}

void FilterGraphItem::initUi()
{
    switch (m_sizeType)
    {
    case SizeType_Small:
        setFixedSize(100, 50);
        break;
    case SizeType_Medium:
        setFixedSize(200, 100);
        break;
    case SizeType_Large:
        setFixedSize(300, 150);
        break;
    default:
        break;
    }

    auto *label = new QLabel(this);
    label->setText(m_info.name);
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);
    label->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    setLayout(layout);

    setStyleSheet("background-color: #ff0000; border: 1px solid #000000;");
}

void FilterGraphItem::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    QAction *removeAction = menu.addAction("Remove");
    QAction *markAction = menu.addAction("Mark");

    QAction *selectedAction = menu.exec(event->globalPos());

    if (selectedAction == removeAction)
    {
        deleteLater();
    }
    else if (selectedAction == markAction)
    {
        // mark this item
    }
}
