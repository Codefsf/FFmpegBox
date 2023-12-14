#include <QWidget>

class FilterGraphView : public QWidget
{
    Q_OBJECT

public:
    FilterGraphView(QWidget *parent = nullptr);
    ~FilterGraphView();

    void InitUi();

private:
    QWidget* m_graphWidget = nullptr;
};