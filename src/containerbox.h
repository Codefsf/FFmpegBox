#ifndef CONTAINERBOX_H
#define CONTAINERBOX_H

#include <memory>
#include <vector>
#include <string>

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>

class ContainerBoxPaint;

class ContainerBox : public QWidget
{
    Q_OBJECT

    enum AppendType {
        PushBack,
        EmplaceBack,
    };

public:
    ContainerBox(QWidget* parent = nullptr);
    ~ContainerBox();

    void init();

    void initData();
    void initUi();
    void initUiControl();
    void initUiData();
    void initConnect();

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void onCreate();
    void onDelete();
    void onUpdate();
    void onSearch();
    void onAppend(const AppendType& type);

private:
    void updatePaintBox();

private:
    ContainerBoxPaint* m_containerBoxPaint {nullptr};
    QWidget* m_dataWidget {nullptr};
    QWidget* m_controlWidget {nullptr};

    QLineEdit* m_inputLineEdit {nullptr};
    QSpinBox* m_numberSpinBox {nullptr};
    QPushButton* m_createBtn {nullptr};
    QPushButton* m_deleteBtn {nullptr};
    QPushButton* m_updateBtn {nullptr};
    QPushButton* m_searchBtn {nullptr};

    QLabel* m_searchLabel {nullptr};
    QLineEdit* m_searchLineEdit {nullptr};

    QPushButton* m_pushBackBtn {nullptr};
    QComboBox* m_pushBackComboBox {nullptr};

    QLabel* m_updateLabel {nullptr};
    QLineEdit* m_updateLineEdit {nullptr};
    
    QTextBrowser* m_dataTextBrowser {nullptr};

    std::shared_ptr<std::vector<std::string>> m_dataVector {nullptr};
};


#endif