#include <QWidget>
#include <QPoint>
#include <QMouseEvent>

class QListWidget;

struct FilterItem {
    QString name;
    QString description;
};

class FilterListModel
{
public:
    FilterListModel() = default;
    ~FilterListModel() = default;

    void AddItem(const FilterItem& item);

    int GetCount() const;
    QList<FilterItem> GetItems();

private:
    QList<FilterItem> m_items;
};

class FilterListView : public QWidget
{
    Q_OBJECT

public:
    FilterListView(QWidget *parent = nullptr);
    ~FilterListView();

    void SetModel(const FilterListModel& model);
    void InitUi();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void addItem(const FilterItem& item);
    
private:
    QListWidget* m_listWidget   = nullptr;
    QPoint      m_dragPosition  = QPoint();
    FilterListModel m_model;
};
