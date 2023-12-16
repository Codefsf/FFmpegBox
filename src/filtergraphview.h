#pragma once

#include <QWidget>

class FilterGraphView : public QWidget
{
    Q_OBJECT

public:
    FilterGraphView(QWidget *parent = nullptr);
    ~FilterGraphView();

private:
    void addItem(const QString& name);
    void deleteItem(const QString& name);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QWidget* m_draggedWidget { nullptr };
    bool m_dragging { false };
    QPoint m_lastPos;
};