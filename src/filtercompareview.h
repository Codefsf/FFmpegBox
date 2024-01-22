#pragma once

#include <QWidget>

class FilterCompareView : public QWidget
{
    Q_OBJECT

public:
    FilterCompareView(QWidget *parent = nullptr);
    ~FilterCompareView();

    void initUi();

    void start();

private:
    QWidget *m_inputWidget = nullptr;
    QWidget *m_outputWidget = nullptr;
};