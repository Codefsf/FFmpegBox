#include <QWidget>

class FilterGraphView : public QWidget
{
    Q_OBJECT

public:
    FilterGraphView(QWidget *parent = nullptr);
    ~FilterGraphView();

    void InitUi();

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
    QWidget* m_draggedWidget  = nullptr;
    QList<QWidget*> m_items;
    bool m_dragging;
    QPoint m_lastPos;
};