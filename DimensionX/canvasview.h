#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QGraphicsView>

class QWheelEvent;
class QKeyEvent;

class CanvasView : public QGraphicsView
{
    Q_OBJECT
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
    //只有带User的item是可以设置的
    int BlinkIndexBak = -1;
    // void ResetBlinkIndex(){ BlinkIndexBak = -1;}
    // void SetItemUserVisible(bool isVisible,int Index = 1);
    // void SetAllItemColor(QPen pen);
    // void SetItemColor(QString Index, QPen pen);
    // //遍历所有 的item
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
    void fitInView(QRectF fit, Qt::AspectRatioMode mode = Qt::KeepAspectRatio) {FitedView = fit;
        isShowCAD = true;
        return QGraphicsView::fitInView(FitedView,mode);
    }

    void fitImageInView(QRectF fit, Qt::AspectRatioMode mode = Qt::KeepAspectRatio) {
        if(fit.width() < 1) return;
        isShowCAD = false;
        return QGraphicsView::fitInView(fit,mode);
    }

    void fitMapInView(Qt::AspectRatioMode mode = Qt::KeepAspectRatio) {
        if(FitedView.width() < 1) return;
        isShowCAD = true;
        return QGraphicsView::fitInView(FitedView,mode);
    }

    bool isDispCAD(){return isShowCAD;}

    void setLeftButtonAction(INTERACTION act){InterAction = act;}

    void drawItem(int);

protected:
    // 上/下/左/右键向各个方向移动、加/减键进行缩放、空格/回车键旋转
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event);
public Q_SLOTS:
    //void zoomIn();  // 放大
    //void zoomOut();  // 缩小
    void zoom(float scaleFactor); // 缩放 - scaleFactor：缩放的比例因子
    void zoomIn();
    void zoomOut();
    void translate(QPointF delta);  // 平移
    void loadFile(std::string fileName = "./A.dxf");

private:
    QGraphicsItem * CurrentItem = nullptr;
    Qt::MouseButton m_translateButton;  // 平移按钮
    qreal m_translateSpeed;  // 平移速度
    qreal m_zoomDelta;  // 缩放的增量
    bool m_bMouseTranslate;  // 平移标识
    QPoint m_lastMousePos;  // 鼠标最后按下的位置
    qreal m_scale;  // 缩放值
    qreal XOffset;  // X轴偏移量
    qreal YOffset;  // Y轴偏移量
    qreal BaseWidth = 100.0;
    qreal BaseHeight = 100.0;
    QImage qImage;
    QPixmap pixmap;
    QStringList ImageFileType;

    //about display image on the view
    QRectF FitedView;

    //about drawing item ont the view
    QPointF startPoint;
    bool drawing = false;
    bool isShowCAD = true;


private:
    INTERACTION InterAction;
};


#endif // CANVASVIEW_H

