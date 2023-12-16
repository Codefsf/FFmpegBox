#pragma once

#include <QWidget>

enum SizeType
{
    SizeType_Unknown,
    SizeType_Small,
    SizeType_Medium,
    SizeType_Large
};

struct FilterGraphItemInfo
{
    QString name {""};
    SizeType sizeType {SizeType_Small};
};

class QContextMenuEvent;

class FilterGraphItem : public QWidget
{
    Q_OBJECT

public:
    FilterGraphItem(QWidget *parent = nullptr);
    ~FilterGraphItem();

    void initUi();
    void setSize(const SizeType& sizeType);
    void setInfo(const FilterGraphItemInfo& info);
    void setItemName(const QString& name);



protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    SizeType m_sizeType {SizeType_Small};
    FilterGraphItemInfo m_info;
};