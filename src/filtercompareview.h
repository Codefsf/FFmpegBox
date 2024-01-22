#pragma once

#include <QWidget>

class FFmpegFilter;

class FilterCompareView : public QWidget
{
    Q_OBJECT

public:
    FilterCompareView(QWidget *parent = nullptr);
    ~FilterCompareView();

    void initUi();
    void initData();

    void start();
    void stop();

private:
    QWidget *m_inputWidget  = nullptr;
    QWidget *m_outputWidget = nullptr;

    FFmpegFilter *m_filter  = nullptr;
};