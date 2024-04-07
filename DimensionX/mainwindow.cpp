#include "pch.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphicsitem.h"
#include "formdxflayout.h"


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
    InitToolBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}


