#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QToolButton>

class Toolbar : public QWidget
{
    Q_OBJECT
public:
    Toolbar(QWidget *parent = nullptr);
    ~Toolbar();

    void init();

    void initData();
    void initUi();
    void initConnect();

signals:
    void toolButtonClicked(const QString& toolName);

public slots:
    void onToolButtonClicked();

private:
    void initToolButtons();

private:
    QHBoxLayout* hLayout {nullptr};
    QList<QToolButton*> toolButtons;    
};

#endif