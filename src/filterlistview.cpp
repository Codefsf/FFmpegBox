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
#include <QLineEdit>

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
    setFixedWidth(200);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    auto mainLayout = new QVBoxLayout(this);

    auto searchLayout = new QHBoxLayout();

    auto searchInput = new QLineEdit(this);
    connect(searchInput, &QLineEdit::returnPressed, this, &FilterListView::onSearchButtonClicked);
    searchLayout->addWidget(searchInput);

    auto searchButton = new QPushButton("Search", this);
    connect(searchButton, &QPushButton::clicked, this, &FilterListView::onSearchButtonClicked);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);

    m_listWidget = new QListWidget(this);
    m_listWidget->setStyleSheet("border: 0px;");
    mainLayout->addWidget(m_listWidget);

    for(auto& item : m_model.GetItems()) {
        addItem(item);
    }

    QLabel *label = new QLabel(QString("Total: %1").arg(m_model.GetCount()), this);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

    setLayout(mainLayout);
}

QLabel* FilterListView::createLabel(const QString& text) {
    auto label = new QLabel(text);
    label->setAlignment(Qt::AlignCenter);
    return label;
}

void FilterListView::onSearchTextChanged(const QString& text) {
    qDebug() << "onSearchTextChanged: " << text;

    m_listWidget->clear();

    for(auto& item : m_model.GetItems()) {
        if (item.name.contains(text, Qt::CaseInsensitive)) {
            addItem(item);
        }
    }
}

void FilterListView::onSearchButtonClicked() {
    auto searchInput = findChild<QLineEdit*>();
    if (searchInput) {
        onSearchTextChanged(searchInput->text());
    }
}

void FilterListView::addItem(const FilterItem& item) {
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