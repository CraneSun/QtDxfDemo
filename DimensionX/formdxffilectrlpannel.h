#ifndef FORMDXFFILECTRLPANNEL_H
#define FORMDXFFILECTRLPANNEL_H

#include <QWidget>

namespace Ui {
class FormDxfFileCtrlPannel;
}

class FormDxfFileCtrlPannel : public QWidget
{
    Q_OBJECT

public:
    explicit FormDxfFileCtrlPannel(QWidget *parent = nullptr);
    ~FormDxfFileCtrlPannel();


private slots:
    void on_pushButton_load_clicked();

    void on_pushButton_EditParameter_clicked();

signals:
    void pushButton_load();
    void pushButton_EditPara();


private:
    Ui::FormDxfFileCtrlPannel *ui;
};

#endif // FORMDXFFILECTRLPANNEL_H
