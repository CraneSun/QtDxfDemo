#ifndef FORMDXFLAYOUT_H
#define FORMDXFLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include "formdxffile.h"
#include "formdxffilectrlpannel.h"
#include "formdxffile.h"

namespace Ui {
class FormdxfLayout;
}

class FormdxfLayout : public QWidget
{
    Q_OBJECT

public:
    explicit FormdxfLayout(QWidget *parent = nullptr);
    ~FormdxfLayout();

private:
    QGridLayout * gridLayout = nullptr;
    FormDxfFileCtrlPannel * formCtrlPannel = nullptr;
    FormDxfFile * formDxfFile = nullptr;
    Ui::FormdxfLayout *ui;
};

#endif // FORMDXFLAYOUT_H
