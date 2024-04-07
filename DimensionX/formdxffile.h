#ifndef FORMDXFFILE_H
#define FORMDXFFILE_H

#include <vector>
#include <QWidget>
#include <QStackedWidget>
#include <QGridLayout>
//#include "../../DimensionX/WidgetCAD/widgetcad.h"
#include "../WidgetCAD/widgetcad.h"

#define CHECK_MAPIDX(x) {if(0!=x)x=1;}

namespace Ui {
class FormDxfFile;
}

class FormDxfFile : public QWidget
{
    Q_OBJECT

public:
    explicit FormDxfFile(QWidget *parent = nullptr);
    ~FormDxfFile();
    int getCurrentViewIdx();
    void addItem(QGraphicsItem *item, int mapIdx = 0);
    bool readFile(std::string fileName, int mapIdx = 0);

signals:
    void changeView();

private:
    std::vector<CanvasView*> canvasViews;
    std::vector<DeviceSence*> deviceSences;
    std::vector<QStackedWidget*> stackedWidgets;

    QGridLayout *layout = nullptr;
    Ui::FormDxfFile *ui;
};

#endif // FORMDXFFILE_H
