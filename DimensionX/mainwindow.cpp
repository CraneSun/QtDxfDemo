#include "pch.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsitem.h"
#include "formdxflayout.h"

/*
界面类似 qt或者vsc，左侧为活动栏，然后就是控制菜单等,
ToolBar    DockWiget

page 0 welcome
page 1 show effection
page 2 show cad
page 3 show statics



*/

const int ToolBarWidth = 48;
const int DockWidgetWidth = 150;


void MainWindow::changePage(int pageIndex)
{

    (void)pageIndex;
}

void MainWindow::InitToolBar()
{
    QToolBar * tools = new QToolBar("Tools");
    addToolBar(Qt::LeftToolBarArea, tools);

    QPushButton * buttonWelcome = new QPushButton("Welcome");
    connect(buttonWelcome,&QPushButton::clicked,[=](){
        changePage(0);
    });
    tools->addWidget(buttonWelcome);

    QPushButton * buttonShowResult = new QPushButton("Effect");
    connect(buttonShowResult,&QPushButton::clicked,[=](){
        changePage(1);
    });
    tools->addWidget(buttonShowResult);


    stackLayout = new QGridLayout();
    stackWidget = std::make_unique<QStackedWidget>();
    setCentralWidget(stackWidget.get());

    static auto formdxfLayout = new FormdxfLayout();
    stackWidget->insertWidget(0,formdxfLayout);









    tools->setFixedWidth(ToolBarWidth);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //init tool bar
    //init dockwidet
    //init mainboard
    //the fill by myself
    InitToolBar();



//     static auto n = new FormDxfFile(ui->widget) ;
//     QPen ptpen;
//     ptpen.setColor(QColor(255,0,0));
//     ptpen.setWidth(5.0);
//     ptpen.setCosmetic(true);

// //auto item = new GraphicsRectItem(0,0,100,100);
// #if 0
//         auto item = new GraphicsDotItem(0,0,50);
// #else
//     QGraphicsRectItem *item =
//         new QGraphicsRectItem(150,150,50,50);
// #endif
//     auto brush = QBrush(QColor(255,0,0));
//     item->setBrush(brush);
//     item->setPen(ptpen);
//     n->addItem(item);

}

MainWindow::~MainWindow()
{
    delete ui;
}


