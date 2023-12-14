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

class FilterListItem : public QWidget
{
    Q_OBJECT

public:
    FilterListItem(QWidget *parent = nullptr);
    ~FilterListItem();

    void setItemName(const QString& name);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QPoint  m_dragPosition  = QPoint();
    QString m_name;
};

class FilterListView : public QWidget
{
    Q_OBJECT

public:
    FilterListView(QWidget *parent = nullptr);
    ~FilterListView();

    void SetModel(const FilterListModel& model);
    void InitUi();



private:
    void addItem(const FilterItem& item);
    
private:
    QListWidget* m_listWidget   = nullptr;
    FilterListModel m_model;
};
