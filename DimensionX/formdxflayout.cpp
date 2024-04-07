/*
 * @Author: CraneSun sk602015817@hotmail.com
 */
#include "formdxflayout.h"
#include "ui_formdxflayout.h"
#include "../WidgetCAD/widgetcad.h"


FormdxfLayout::FormdxfLayout(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormdxfLayout)
{
    ui->setupUi(this);


    gridLayout = new QGridLayout(this);
    formCtrlPannel = new FormDxfFileCtrlPannel();
    gridLayout->addWidget(formCtrlPannel,0,0,1,1);
    formCtrlPannel->setFixedWidth(350);

    formDxfFile = new FormDxfFile();
    gridLayout->addWidget(formDxfFile,0,1,1,1);

    connect(formCtrlPannel, &FormDxfFileCtrlPannel::pushButton_load,[=](){
        QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Load File"), "", tr("DXF Files (*.dxf);; DWG Files (*.dwg);; CXF Files (*cxf)"));
        bool res = formDxfFile->readFile(fileName.toStdString(),formDxfFile->getCurrentViewIdx());
    });
}

FormdxfLayout::~FormdxfLayout()
{
    delete ui;
}
