#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QWidget>

class Toolbar : public QWidget
{
public:
    Toolbar(QWidget *parent = nullptr);
    ~Toolbar();

    void initUi();
    void initConnect();
};

#endif