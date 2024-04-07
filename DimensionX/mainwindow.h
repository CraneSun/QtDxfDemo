#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <memory>
#include <QMainWindow>
#include <QStackedWidget>
#include <QGridLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void changePage(int);
    void InitToolBar(void);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout * stackLayout = nullptr;
    std::unique_ptr<QStackedWidget> stackWidget;
};
#endif // MAINWINDOW_H
