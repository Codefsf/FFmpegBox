#include "filtergraphview.h"
#include "filtergraphitem.h"

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

void FilterGraphView::addItem(const QString &name)
{
    auto *item = new FilterGraphItem(this);
    item->setInfo({name, SizeType_Small});
    item->initUi();

    QPoint globalMousePos = QCursor::pos();
    QPoint localMousePos = this->mapFromGlobal(globalMousePos);
    item->move(localMousePos);

    item->show();
}

void FilterGraphView::deleteItem(const QString &name)
{
}

void FilterGraphView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/plain"))
    {
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