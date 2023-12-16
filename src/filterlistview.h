#include <QWidget>
#include <QPoint>
#include <QMouseEvent>

class QListWidget;
class QLabel;

struct FilterItem {
    QString name;
    QString description;
};

class FilterListModel
{
public:
    FilterListModel() = default;
    ~FilterListModel() = default;

    void addItem(const FilterItem& item);

    int getCount() const;
    QList<FilterItem> getItems();

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

    void startDrag();

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

    void setModel(const FilterListModel& model);
    void initUi();

private slots:
    void onSearchTextChanged(const QString& text);
    void onSearchButtonClicked();

private:
    void addItem(const FilterItem& item);
    QLabel* createLabel(const QString& text);

private:
    QListWidget* m_listWidget   = nullptr;
    FilterListModel m_model;
};
