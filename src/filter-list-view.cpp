#include "filter-list-view.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

//FilterListModel---------------------------------------------------------------------
void FilterListModel::AddItem(const FilterItem& item) {
    m_items.append(item);
}

int FilterListModel::GetCount() const {
    return m_items.size();
}

QList<FilterItem> FilterListModel::GetItems() const {
    return m_items;
}



//FilterListView---------------------------------------------------------------------
FilterListView::FilterListView(QWidget *parent)
    : QWidget(parent)
{
}

FilterListView::~FilterListView()
{
}


void FilterListView::SetModel(const FilterListModel& model) {
    m_model = model;    
}

void FilterListView::InitUi() {
    m_listWidget = new QListWidget(this);

    QWidget* customWidget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout();
    QLabel* label = new QLabel("Item 1");
    QPushButton* button = new QPushButton("Button");
    layout->addWidget(label);
    layout->addWidget(button);
    customWidget->setLayout(layout);

    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(customWidget->sizeHint());

    m_listWidget->addItem(item);
    m_listWidget->setItemWidget(item, customWidget);

    m_listWidget->setGeometry(10, 10, 200, 300);
}