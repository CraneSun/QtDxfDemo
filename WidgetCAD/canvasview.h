#ifndef CANVASVIEW_H
#define CANVASVIEW_H
#include <QGraphicsView>
#include <QObject>
#include "cadfile.h"
#include "ShapeDefine.h"

//allow file
//so dwg is valid



class QWheelEvent;
class QKeyEvent;

class __declspec(dllexport) CanvasView : public QGraphicsView
{
public:
    enum INTERACTION
    {
        ACT_NONE = 0,
        ACT_DRAW_RECT_START,
        ACT_DRAW_RECT,
        ACT_DRAW_PYLON_START,
        ACT_DRAW_PYLON,
        ACT_MOVING
    };


    explicit CanvasView(QWidget *parent = nullptr);
    int BlinkIndexBak = -1;
    // void ResetBlinkIndex(){ BlinkIndexBak = -1;}
    // void SetItemUserVisible(bool isVisible,int Index = 1);
    // void SetAllItemColor(QPen pen);
    // void SetItemColor(QString Index, QPen pen);
    // QList<QGraphicsItem*> items();
    // void setLabelVisibale(bool isV);
    // void setTranslateSpeed(qreal speed); //speed of moving
    // qreal translateSpeed() const; //get speed of moving
    // void setZoomDelta(qreal delta);// scale factor
    // qreal zoomDelta() const;
    // void setXOffet(qreal xof);//offset of x
    // void setYOffet(qreal yof);
    // void resetSize(qreal bW, qreal bH);
    // QRectF getViewRect(){ return FitedView;}

    void setLeftButtonAction(INTERACTION act){InterAction = act;}
    //each canvas should have uid
    void setUID(int uid);
    int UID();
    //fitInView
    void fitInViewEx(QRectF fit,bool isUpdateFitView = false, Qt::AspectRatioMode mode = Qt::KeepAspectRatio);
    QRectF getFitView() const;

    //item relation, draw item
    void drawItem(int);

    //blow are some fuctions for user

public:
    //register it, and let it know this canvas has been activated
    void (*currentCanvasSelected)(int* ) = nullptr;
    bool loadFile(std::string fileName = "./A.dxf");

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event);
public Q_SLOTS:
    void zoom(float scaleFactor);
    void zoomIn();
    void zoomOut();
    void translate(QPointF delta);


private:
    QGraphicsItem * CurrentItem = nullptr;
    Qt::MouseButton m_translateButton;
    qreal m_translateSpeed;
    qreal m_zoomDelta;
    bool m_bMouseTranslate;
    QPoint m_lastMousePos;
    qreal m_scale;
    qreal XOffset;
    qreal YOffset;
    QImage qImage;
    QPixmap pixmap;
    QStringList ImageFileType;
    //about drawing item ont the view
    QPointF startPoint;
    bool drawing = false;
private:
    bool isInvAxisY = true;
    QRectF FitedView;
    INTERACTION InterAction;
    CadFile cadFile;
    int _uid;
};


#endif // CANVASVIEW_H
