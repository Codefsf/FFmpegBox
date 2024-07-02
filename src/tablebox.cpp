#include "tablebox.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSpacerItem>

TableBox::TableBox(QWidget* parent)
    : QWidget(parent)
{
}

TableBox::~TableBox()
{
}

void TableBox::initUi()
{
    this->resize(800, 600);

    QHBoxLayout* hLayout = new QHBoxLayout();
    QPushButton* addColumnBtn = new QPushButton("Add Column", this);
    QPushButton* delColumnBtn = new QPushButton("Del Column", this);
    QPushButton* addRowBtn = new QPushButton("Add Row", this);
    QPushButton* delRowBtn = new QPushButton("Del Row", this);

    connect(addColumnBtn, &QPushButton::clicked, this, &TableBox::addColumn);
    connect(delColumnBtn, &QPushButton::clicked, this, &TableBox::delColumn);
    connect(addRowBtn, &QPushButton::clicked, this, &TableBox::addRow);
    connect(delRowBtn, &QPushButton::clicked, this, &TableBox::delRow);

    hLayout->addWidget(addColumnBtn);
    hLayout->addWidget(delColumnBtn);
    hLayout->addWidget(addRowBtn);
    hLayout->addWidget(delRowBtn);

    m_tableView = new QTableWidget(this);
    m_tableView->installEventFilter(this);

    QVBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addLayout(hLayout);
    vLayout->addWidget(m_tableView);

    QHBoxLayout* hLayout2 = new QHBoxLayout();
    QPushButton* saveBtn = new QPushButton("Save", this);
    QPushButton* clearBtn = new QPushButton("Clear", this);

    connect(saveBtn, &QPushButton::clicked, this, &TableBox::saveFile);
    connect(clearBtn, &QPushButton::clicked, this, &TableBox::clearTable);

    QSpacerItem* spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hLayout2->addItem(spacer);
    hLayout2->addWidget(saveBtn);
    hLayout2->addWidget(clearBtn);

    vLayout->addLayout(hLayout2);
}

void TableBox::initData()
{
    if (m_tableView == nullptr)
    {
        return;
    }

    m_tableView->setColumnCount(5);
    m_tableView->setRowCount(5);

    for (int i = 0; i < m_tableView->rowCount(); i++)
    {
        for (int j = 0; j < m_tableView->columnCount(); j++)
        {
            m_tableView->setItem(i, j, new QTableWidgetItem(QString::number(i) + "," + QString::number(j)));
        }
    }
}

void TableBox::initConnect()
{
}

void TableBox::contextMenuEvent(QContextMenuEvent* event)
{
    QMenu menu(this);
    QAction* clearAction = menu.addAction("Clear");
    QAction* copyAction = menu.addAction("Copy");

    connect(clearAction, &QAction::triggered, [&]() {
        QTableWidgetItem* item = 
            m_tableView->itemAt(m_tableView->mapFromGlobal(event->globalPos()));
        if (item != nullptr)
        {
            item->setText("");
        }
    });

    connect(copyAction, &QAction::triggered, [&]() {
        QTableWidgetItem* item = 
            m_tableView->itemAt(m_tableView->mapFromGlobal(event->globalPos()));
        if (item != nullptr)
        {
            QApplication::clipboard()->setText(item->text());
        }
    });

    menu.exec(event->globalPos());
}

bool TableBox::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == m_tableView)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->matches(QKeySequence::Copy))
            {
                QTableWidgetItem* item = m_tableView->currentItem();
                if (item != nullptr)
                {
                    QApplication::clipboard()->setText(item->text());
                    qDebug() << "Copy";
                }
            }
            else if (keyEvent->matches(QKeySequence::Paste))
            {
                QTableWidgetItem* item = m_tableView->currentItem();
                if (item != nullptr)
                {
                    item->setText(QApplication::clipboard()->text());
                    qDebug() << "Paste";
                }
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}

void TableBox::addColumn()
{
    m_tableView->setColumnCount(m_tableView->columnCount() + 1);
}

void TableBox::delColumn()
{
    m_tableView->setColumnCount(m_tableView->columnCount() - 1);
}

void TableBox::addRow()
{
    m_tableView->setRowCount(m_tableView->rowCount() + 1);
}

void TableBox::delRow()
{
    m_tableView->setRowCount(m_tableView->rowCount() - 1);
}

void TableBox::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt)"));
    if (fileName.isEmpty())
    {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < m_tableView->rowCount(); i++)
    {
        for (int j = 0; j < m_tableView->columnCount(); j++)
        {
            if (m_tableView->item(i, j) != nullptr)
            {
                out << m_tableView->item(i, j)->text() << "\t";
            }
            
        }
        out << "\n";
    }

    file.close();

    QMessageBox::information(this, tr("Save File"), tr("Save File Successfully"));
}

void TableBox::clearTable()
{
    m_tableView->clear();
}