#ifndef PAINTBOX_H
#define PAINTBOX_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

class QComboBox;
class QLabel;

class PaintBox : public QWidget
{
    Q_OBJECT
public:
    enum PaintType
    {
        Ball,
        Rain,
        Close
    };

    PaintBox(QWidget* parent = nullptr);
    ~PaintBox();

    void init();

    void initData();
    void initUi();
    void initConnect();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void paintBall(QPainter& painter);
    void paintRain(QPainter& painter);
    void paintClose(QPainter& painter);

private:
    QWidget*    m_paintWidget {nullptr};
    QComboBox*  m_comboBox {nullptr};
    QTimer*     m_timer {nullptr};
    QMap<PaintType, QString> m_paintTypeMap;
};




#endif