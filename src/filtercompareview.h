#pragma once

#include <QWidget>


class FFmpegFilter;
class FFmpegFormat;

class FilterCompareView : public QWidget
{
    Q_OBJECT

public:
    FilterCompareView(QWidget *parent = nullptr);
    ~FilterCompareView();

    void initUi();
    void initData();

    int start();
    void stop();

private:
    QWidget *m_inputWidget {nullptr};
    QWidget *m_outputWidget {nullptr};

    FFmpegFilter *m_filter {nullptr};
    FFmpegFormat *m_format {nullptr};
};