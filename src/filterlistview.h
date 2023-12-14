#include <QWidget>

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
    QList<FilterItem> GetItems() const;

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

private:
    QListWidget* m_listWidget   = nullptr;
    FilterListModel m_model;
};
