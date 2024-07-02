#ifndef CONTAINERBOXPAINT_H
#define CONTAINERBOXPAINT_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <QWidget>

class ContainerBoxPaint : public QWidget
{
public:
    struct PaintData
    {
        std::shared_ptr<std::vector<std::string>> vectorDataPtr;
        std::shared_ptr<std::list<std::string>> listDataPtr;
        std::shared_ptr<std::map<std::string, std::string>> mapDataPtr;
        std::shared_ptr<std::set<std::string>> setDataPtr;
        std::shared_ptr<std::unordered_map<std::string, std::string>> unorderedMapDataPtr;
        std::shared_ptr<std::unordered_set<std::string>> unorderedSetDataPtr;
    };
    
    ContainerBoxPaint(QWidget* parent = nullptr);
    ~ContainerBoxPaint();

    void init();
    void initData(const PaintData& data);
    void initUi();
    void initConnect();

    void setVectorData(std::shared_ptr<std::vector<std::string>> data);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void paintVectorData(QPainter& painter);

private:
    PaintData m_paintData;
};

#endif // CONTAINERBOXPAINT_H