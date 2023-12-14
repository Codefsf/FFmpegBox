#include "filterlistview.h"
#include "ffmpegfilter.h"

#include <QListWidget>
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

//----------FilterListModel----------
void FilterListModel::AddItem(const FilterItem& item) {
    m_items.append(item);
}

int FilterListModel::GetCount() const {
    return m_items.size();
}

QList<FilterItem> FilterListModel::GetItems() {
    if (!m_items.isEmpty()) {
        return m_items;
    }

    auto filtersList = FFmpegFilter::GetAllFilter();
    for (auto& filter : filtersList) {
        FilterItem item;
        item.name = QString::fromStdString(filter);
        item.description = QString::fromStdString(filter);

        m_items.append(item);
    }

    return m_items;
}

//----------FilterListItem----------
FilterListItem::FilterListItem(QWidget *parent)
    : QWidget(parent)
{
}

FilterListItem::~FilterListItem()
{
}

void FilterListItem::setItemName(const QString& name) {
    m_name = name;
}

void FilterListItem::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
        m_dragPosition = event->pos();
}

void FilterListItem::mouseMoveEvent(QMouseEvent* event) {
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - m_dragPosition).manhattanLength()
         < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(m_name);
    drag->setMimeData(mimeData);

    drag->exec(Qt::CopyAction | Qt::MoveAction);
}


//----------FilterListView----------
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
    QVBoxLayout* mainLayout = new QVBoxLayout(this); 
    mainLayout->addWidget(m_listWidget); 
    this->setLayout(mainLayout); 

    for(auto& item : m_model.GetItems()) {
        addItem(item);
    } 

    QLabel* label = new QLabel(QString("Total: %1").arg(m_model.GetCount()));
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);
}

void FilterListView::addItem(const FilterItem& item) {
    if (m_listWidget == nullptr)
    {
        return;
    }

    if (item.name.isEmpty())
    {
        return;
    }
    
    FilterListItem* customWidget = new FilterListItem();
    QHBoxLayout* layout = new QHBoxLayout();

    QLabel* label = new QLabel(item.name);
    layout->addWidget(label);
    customWidget->setLayout(layout);
    customWidget->setItemName(item.name);

    QListWidgetItem* list_item = new QListWidgetItem();
    list_item->setSizeHint(customWidget->sizeHint());

    m_listWidget->addItem(list_item);
    m_listWidget->setItemWidget(list_item, customWidget);
}