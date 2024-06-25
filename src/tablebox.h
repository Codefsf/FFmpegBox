#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include <QTableWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QClipboard>

class TableBox : public QWidget
{
    Q_OBJECT
public:
    TableBox(QWidget* parent = nullptr);
    ~TableBox();

    void initUi();
    void initData();
    void initConnect();

private slots:
    void addColumn();
    void delColumn();
    void addRow();
    void delRow();

    void saveFile();
    void clearTable();

private:
    QTableWidget* m_tableView {nullptr};
};


#endif