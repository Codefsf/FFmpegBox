#include "filtergraphview.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QLabel>

FilterGraphView::FilterGraphView(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
}

FilterGraphView::~FilterGraphView()
{
}

void FilterGraphView::InitUi()
{
}

void FilterGraphView::addItem(const QString &name)
{
    QWidget *item = new QWidget(this);
    item->setObjectName(name);
    item->setFixedSize(50, 50);
    item->setStyleSheet("background-color: red; border: 1px solid rgb(0, 0, 0);color: rgb(255, 255, 255);");

    QLabel *label = new QLabel(name, item);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
    label->setAlignment(Qt::AlignCenter);
    label->setWordWrap(true);
    label->setFixedSize(item->size());

    QPoint globalMousePos = QCursor::pos();
    QPoint localMousePos = this->mapFromGlobal(globalMousePos);
    item->move(localMousePos);

    item->show();

    m_items.append(item);
}

void FilterGraphView::deleteItem(const QString &name)
{
}

void FilterGraphView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
    {
        qDebug() << "dragEnterEvent";
        event->acceptProposedAction();
    }
}

void FilterGraphView::dropEvent(QDropEvent *event)
{
    auto content = event->mimeData()->text().split("\n");
    if (content.isEmpty())
    {
        return;
    }

    qDebug() << "dropEvent ：" << content[0];
    event->acceptProposedAction();

    addItem(content[0]);
}

void FilterGraphView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_lastPos = event->pos();
        m_draggedWidget = childAt(event->pos());
    }
    QWidget::mousePressEvent(event);
}

void FilterGraphView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && m_draggedWidget)
    {
        auto diff = event->pos() - m_lastPos;
        m_draggedWidget->move(m_draggedWidget->pos() + diff);
        m_lastPos = event->pos();
    }
    QWidget::mouseMoveEvent(event);
}

void FilterGraphView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = false;
        m_draggedWidget = nullptr;
    }
    QWidget::mouseReleaseEvent(event);
}