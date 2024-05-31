#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QToolButton>

class Toolbar : public QWidget
{
public:
    Toolbar(QWidget *parent = nullptr);
    ~Toolbar();

    void initData();
    void initUi();
    void initConnect();

public slots:
    void onToolButtonClicked();

private:
    void initToolButtons();

private:
    QHBoxLayout* hLayout {nullptr};
    QList<QToolButton*> toolButtons;    
};

#endif