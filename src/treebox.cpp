#include "treebox.h"

#include <QDir>
#include <QFileInfo>
#include <QTreeWidgetItem>

TreeBox::TreeBox(QWidget* parent)
    : QWidget(parent)
{
}

TreeBox::~TreeBox()
{
}

void TreeBox::init()
{
    initData();
    initUi();
    initConnect();
}

void TreeBox::initData()
{
    m_rootNode = new FileNode;
    m_rootNode->fileName = "C:/";
    m_rootNode->filePath = "C:/";

    QDir dir("C:/");
    QFileInfoList fileInfoList = dir.entryInfoList();
    for (int i = 0; i < fileInfoList.size(); ++i)
    {
        QFileInfo fileInfo = fileInfoList.at(i);
        if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
        {
            continue;
        }

        FileNode* fileNode = new FileNode;
        fileNode->fileName = fileInfo.fileName();
        fileNode->filePath = fileInfo.filePath();
        m_rootNode->childList.append(fileNode);
    }
}

void TreeBox::initUi()
{
    this->resize(800, 600);

    m_treeWidget = new QTreeWidget(this);
    m_treeWidget->setHeaderLabels(QStringList() << "File Name" << "File Path");
    m_treeWidget->setColumnWidth(0, 200);
    m_treeWidget->setColumnWidth(1, 600);
    m_treeWidget->setFixedSize(800, 600);
    m_treeWidget->setColumnCount(2);

    for(auto iter = m_rootNode->childList.begin(); iter != m_rootNode->childList.end(); ++iter)
    {
        FileNode* fileNode = *iter;
        QTreeWidgetItem* item = new QTreeWidgetItem(m_treeWidget);
        item->setText(0, fileNode->fileName);
        item->setText(1, fileNode->filePath);
    }

}

void TreeBox::initConnect()
{
}

void TreeBox::addChildren(FileNode* parentNode)
{
   
}