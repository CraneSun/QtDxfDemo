#include "pch.h"
#include "formdxffile.h"
#include "ui_formdxffile.h"

int CurrentSeletion = 0;
void changeCurrentView(int* b)
{
    CurrentSeletion = *b;
    qDebug() <<  CurrentSeletion ;
}

int FormDxfFile::getCurrentViewIdx()
{
    return CurrentSeletion;
}

FormDxfFile::FormDxfFile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormDxfFile)
{
    ui->setupUi(this);
    //init the display of cad
    layout = new QGridLayout();
    for(int i = 0; i < 2; i++)
    {
        stackedWidgets.push_back(new QStackedWidget());
        canvasViews.push_back(new CanvasView());
        deviceSences.push_back(new DeviceSence());

        deviceSences.back()->setBackgroundBrush(QBrush(QColor(0,0,0)));
        canvasViews.back()->setInteractive(true);
        canvasViews.back()->setScene(deviceSences.back());
        canvasViews.back()->setRenderHints(QPainter::SmoothPixmapTransform);
        canvasViews.back()->show();

        stackedWidgets.back()->insertWidget(0,canvasViews.back());
        stackedWidgets.back()->setCurrentIndex(0);
        layout->addWidget(stackedWidgets.back(),i,0,1,1);
        //my edit
        canvasViews.back()->setUID(i);
        //canvasViews.back()->currentCanvasSelected = changeSelection;
        canvasViews.back()->currentCanvasSelected = changeCurrentView;
    }
    setLayout(layout);
}

void FormDxfFile::addItem(QGraphicsItem *item, int mapIdx)
{
    try{
        deviceSences.at(mapIdx)->addItem(item);
    }catch(std::exception & e)
    {
        (void)e;
    }
}

bool FormDxfFile::readFile(std::string fileName, int mapIdx){
    try{
        return canvasViews.at(mapIdx)->loadFile(fileName);
    }catch(std::exception & e)
    {
        (void)e;
    }
    return false;
}

FormDxfFile::~FormDxfFile()
{
    for(auto & c : canvasViews){
        delete c;
    }

    for(auto & d: deviceSences){
        delete d;
    }

    for(auto & s: stackedWidgets){
        delete s;
    }

    delete layout;
    delete ui;
}
