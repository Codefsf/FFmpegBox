#include "filterlistview.h"

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
    this->setFixedWidth(200);
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    m_listWidget = new QListWidget(this);
    m_listWidget->setStyleSheet("border: 0px;");

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

    QVBoxLayout* mainLayout = new QVBoxLayout(this);  // 创建一个新的布局
    mainLayout->addWidget(m_listWidget);  // 将m_listWidget添加到布局中
    this->setLayout(mainLayout);  // 将布局设置为FilterListView的布局
}