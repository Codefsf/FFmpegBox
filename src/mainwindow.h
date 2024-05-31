#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Toolbar;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initUi();
    void initConnect();

private:
    void initFilterListView();
    void initFilterCompareView();
    void initTestView();

private:
    Ui::MainWindow *ui;
    Toolbar* toolbar {nullptr};
};
#endif // MAINWINDOW_H
