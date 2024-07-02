#include "containerbox.h"
#include "containerboxpaint.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QLineEdit>
#include <QIntValidator>
#include <QSpinBox>
#include <QTextBrowser>
#include <QDateTime>
#include <QPainter>

ContainerBox::ContainerBox(QWidget* parent)
    : QWidget(parent)
{
}

void ContainerBox::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(0, 0, width(), height());
}

ContainerBox::~ContainerBox()
{
}

void ContainerBox::init()
{
    initData();
    initUi();
    initConnect();
}

void ContainerBox::initData()
{
}

void ContainerBox::initUi()
{
    this->resize(800, 600);
    this->setStyleSheet("ContainerBox { border: 1px solid black; }");   

    m_containerBoxPaint = new ContainerBoxPaint(this);
    m_dataWidget = new QWidget(this);
    m_dataWidget->setFixedHeight(200);
    m_controlWidget = new QWidget(this);
    m_controlWidget->setFixedWidth(200);

    QVBoxLayout* vLayout = new QVBoxLayout(); 
    vLayout->addWidget(m_containerBoxPaint);
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    vLayout->addWidget(line);
    vLayout->addWidget(m_dataWidget);

    QHBoxLayout* hLayout = new QHBoxLayout(); 
    hLayout->addWidget(m_controlWidget);
    QFrame* line2 = new QFrame();
    line2->setFrameShape(QFrame::VLine);
    line2->setFrameShadow(QFrame::Sunken);
    hLayout->addWidget(line2);
    hLayout->addLayout(vLayout); 

    this->setLayout(hLayout); 

    initUiControl();
    initUiData();
}

void ContainerBox::initUiControl()
{
    m_inputLineEdit = new QLineEdit(m_controlWidget);
    m_numberSpinBox = new QSpinBox(this);
    m_numberSpinBox->setRange(0, 100000000); 
    m_numberSpinBox->setValue(10); 
    m_createBtn = new QPushButton("Create", m_controlWidget);
    m_deleteBtn = new QPushButton("Delete", m_controlWidget);
    m_updateBtn = new QPushButton("Update", m_controlWidget);
    m_searchBtn = new QPushButton("Search", m_controlWidget);

    //Control Layout
    auto vLayout = new QVBoxLayout(m_controlWidget);
    vLayout->addWidget(m_inputLineEdit);
    vLayout->addWidget(m_numberSpinBox);
    vLayout->addWidget(m_createBtn);
    vLayout->addWidget(m_deleteBtn);

    //PushBack Layout
    auto hLayout = new QHBoxLayout();
    m_pushBackBtn = new QPushButton("PushBack", m_controlWidget);
    m_pushBackComboBox = new QComboBox(m_controlWidget);
    m_pushBackComboBox->addItem("PushBack");
    m_pushBackComboBox->addItem("EmplaceBack");
    hLayout->addWidget(m_pushBackBtn);
    hLayout->addWidget(m_pushBackComboBox);
    vLayout->addLayout(hLayout);

    //Search Layout 
    vLayout->addWidget(m_searchBtn);
    auto hLayout2 = new QHBoxLayout();
    m_searchLabel = new QLabel("SearchText:", m_controlWidget);
    m_searchLineEdit = new QLineEdit(m_controlWidget);
    hLayout2->addWidget(m_searchLabel);
    hLayout2->addWidget(m_searchLineEdit);
    vLayout->addLayout(hLayout2);

    //Update Layout
    vLayout->addWidget(m_updateBtn);
    auto hLayout3 = new QHBoxLayout();
    m_updateLabel = new QLabel("UpdateText:", m_controlWidget);
    m_updateLineEdit = new QLineEdit(m_controlWidget);
    hLayout3->addWidget(m_updateLabel);
    hLayout3->addWidget(m_updateLineEdit);
    vLayout->addLayout(hLayout3);

    vLayout->setAlignment(Qt::AlignTop);
    vLayout->setSpacing(10);
    vLayout->setContentsMargins(10, 10, 10, 10);
}

void ContainerBox::initUiData()
{
    m_dataTextBrowser = new QTextBrowser(m_dataWidget);
    QHBoxLayout* hLayout = new QHBoxLayout(m_dataWidget);
    hLayout->addWidget(m_dataTextBrowser);
}

void ContainerBox::initConnect()
{
    connect(m_createBtn, &QPushButton::clicked, this, &ContainerBox::onCreate);
    connect(m_deleteBtn, &QPushButton::clicked, this, &ContainerBox::onDelete);
    connect(m_updateBtn, &QPushButton::clicked, this, &ContainerBox::onUpdate);
    connect(m_searchBtn, &QPushButton::clicked, this, &ContainerBox::onSearch);
    connect(m_pushBackBtn, &QPushButton::clicked, [=](){
        if (m_pushBackComboBox->currentText() == "PushBack") {
            onAppend(AppendType::PushBack);
        } else if (m_pushBackComboBox->currentText() == "EmplaceBack") {
            onAppend(AppendType::EmplaceBack);
        }
    });
}

void ContainerBox::onCreate()
{
    auto text = m_inputLineEdit->text();
    auto number = m_numberSpinBox->value();

    m_dataTextBrowser->append("Create count: " + QString::number(number) + ", Content: " + text);

    auto startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    m_dataVector = std::make_shared<std::vector<std::string>>(number, text.toStdString());
    auto endTime = QDateTime::currentDateTime().toMSecsSinceEpoch();

    m_dataTextBrowser->append("Create time: " + QString::number(endTime - startTime) + " ms");

    updatePaintBox();
}

void ContainerBox::onDelete()
{
    m_dataTextBrowser->append("Delete");
    auto startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    m_dataVector.reset();
    auto endTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    m_dataTextBrowser->append("Delete time: " + QString::number(endTime - startTime) + " ms");

    updatePaintBox();
}

void ContainerBox::onUpdate()
{
    auto text = m_updateLineEdit->text();
    if(text.isEmpty()) {
        m_dataTextBrowser->append("Update text is empty.");
        return;
    }
    
    if (m_dataVector == nullptr) {
        m_dataTextBrowser->append("Data is empty, please create first.");
        return;
    }

    auto startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    std::for_each(m_dataVector->begin(), m_dataVector->end(), [&](std::string& str) {
        str = text.toStdString();
    });
    auto endTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    m_dataTextBrowser->append("Update time: " + QString::number(endTime - startTime) + " ms");

    updatePaintBox();
}

void ContainerBox::onSearch()
{
    if (m_dataVector == nullptr) {
        m_dataTextBrowser->append("Data is empty, please create first.");
        return;
    }

    auto text = m_searchLineEdit->text();
    if (text.isEmpty()) {
        m_dataTextBrowser->append("Search text is empty.");
        return;
    }
    
    auto startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    auto iter = std::find(m_dataVector->begin(), m_dataVector->end(), text.toStdString());
    auto endTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
    if (iter != m_dataVector->end()) {
        m_dataTextBrowser->append("Search text: " + text + " found.");
    } else {
        m_dataTextBrowser->append("Search text: " + text + " not found.");
    }

    m_dataTextBrowser->append("Search time: " + QString::number(endTime - startTime) + " ms");
}


void ContainerBox::onAppend(const AppendType& type)
{
    if (m_dataVector == nullptr) {
        m_dataTextBrowser->append("Data is empty, please create first.");
        return;
    }

    auto text = m_inputLineEdit->text();
    auto number = m_numberSpinBox->value();

    if (type == AppendType::PushBack) {
        auto startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        m_dataVector->push_back(text.toStdString());
        auto endTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        m_dataTextBrowser->append("PushBack time: " + QString::number(endTime - startTime) + " ms "
                                 + "Text: " + text + " Number: " + QString::number(number));
    } else if (type == AppendType::EmplaceBack) {
        auto startTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        m_dataVector->emplace_back(text.toStdString());
        auto endTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
        m_dataTextBrowser->append("EmplaceBack time: " + QString::number(endTime - startTime) + " ms "
                                 + "Text: " + text + " Number: " + QString::number(number));}

    updatePaintBox();
}

void ContainerBox::updatePaintBox()
{
    m_containerBoxPaint->setVectorData(m_dataVector);
    m_containerBoxPaint->update();
}