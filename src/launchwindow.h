#ifndef LAUNCHWINDOW_H
#define LAUNCHWINDOW_H

#include <QWidget>
#include <QList>

using LaunchItemFunc = std::function<void(bool)>;

class LaunchItem : public QWidget
{
    Q_OBJECT

public:
    LaunchItem(QWidget* parent = nullptr);
    ~LaunchItem();

    void init();
    void setStartFunc(LaunchItemFunc func);
    void start();
    void stop();

private:
    LaunchItemFunc m_startFunc;
};

class LaunchWindow : public QWidget
{
    Q_OBJECT
public:
    LaunchWindow(QWidget* parent = nullptr);
    ~LaunchWindow();

    void init();

private:
    QList<LaunchItem*> m_launchItemList;
};

#endif