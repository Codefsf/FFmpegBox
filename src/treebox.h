#ifndef TREEBOX_H
#define TREEBOX_H

#include <QWidget>
#include <QTreeWidget>




class TreeBox : public QWidget
{
    Q_OBJECT
public:
    struct FileNode
    {
        QString fileName;
        QString filePath;
        QList<FileNode*> childList;
    };
    
    TreeBox(QWidget* parent = nullptr);
    ~TreeBox();

    void init();

    void initData();
    void initUi();
    void initConnect();

private:
    void addChildren(FileNode* parentNode);

private:
    QTreeWidget*    m_treeWidget {nullptr};
    FileNode*       m_rootNode {nullptr};
};

#endif