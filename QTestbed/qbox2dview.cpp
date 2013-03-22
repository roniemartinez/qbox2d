#include "qbox2dview.h"
#include <QScrollBar>

QBox2DView::QBox2DView(QWidget *parent) :
    QGraphicsView(parent)
{
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);
    setOptimizationFlag(DontSavePainterState);
    setResizeAnchor(AnchorViewCenter);
    //setRenderHint(QPainter::Antialiasing);
    horizontalScrollBar()->setHidden(true);
    verticalScrollBar()->setHidden(true);
    setInteractive(true);
    q_label = new QLabel(this);
    q_label->setMargin(9);
}
