#include <QWidget>

class FilterGraphView : public QWidget
{
    Q_OBJECT

public:
    FilterGraphView(QWidget *parent = nullptr);
    ~FilterGraphView();

    void InitUi();

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    QWidget* m_graphWidget = nullptr;
};