#include "formdxffilectrlpannel.h"
#include "ui_formdxffilectrlpannel.h"

FormDxfFileCtrlPannel::FormDxfFileCtrlPannel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDxfFileCtrlPannel)
{
    ui->setupUi(this);
    connect(ui->pushButton_load, &QPushButton::clicked, [=](){
    });
}

FormDxfFileCtrlPannel::~FormDxfFileCtrlPannel()
{
    delete ui;
}

void FormDxfFileCtrlPannel::on_pushButton_load_clicked()
{
      emit pushButton_load();
}


void FormDxfFileCtrlPannel::on_pushButton_EditParameter_clicked()
{
    emit pushButton_EditPara();
}

