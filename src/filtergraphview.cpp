#include "filtergraphview.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

FilterGraphView::FilterGraphView(QWidget *parent)
    : QWidget(parent)
{
}

FilterGraphView::~FilterGraphView()
{
}

void FilterGraphView::InitUi()
{
    setAcceptDrops(true);
}

void FilterGraphView::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void FilterGraphView::dropEvent(QDropEvent* event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    QString path = urls.first().toLocalFile();
    if (path.isEmpty()) {
        return;
    }

    event->acceptProposedAction();
}