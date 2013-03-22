#ifndef QBOX2DJOINT_H
#define QBOX2DJOINT_H

#include <QGraphicsLineItem>
#include <QPainter>
#include <Box2D/Dynamics/Joints/b2Joint.h>
#include <Box2D/Dynamics/Joints/b2DistanceJoint.h>
#include <Box2D/Dynamics/Joints/b2FrictionJoint.h>
#include <Box2D/Dynamics/Joints/b2GearJoint.h>
#include <Box2D/Dynamics/Joints/b2MouseJoint.h>
#include <Box2D/Dynamics/Joints/b2PrismaticJoint.h>
#include <Box2D/Dynamics/Joints/b2PulleyJoint.h>
#include <Box2D/Dynamics/Joints/b2RevoluteJoint.h>
#include <Box2D/Dynamics/Joints/b2RopeJoint.h>
#include <Box2D/Dynamics/Joints/b2WeldJoint.h>
#include <Box2D/Dynamics/Joints/b2WheelJoint.h>
#include <qbox2dcommon.h>
#include <QDebug>

class QBox2DJoint : public QGraphicsLineItem
{
public:
    explicit QBox2DJoint(b2Joint* qb2Joint, QGraphicsItem *parent = 0);
    b2Joint* joint() {
        return q_b2Joint;
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        Q_UNUSED(painter);

        /*add this if you want to show a trace of the boundingRect*/
        //painter->drawRect(childrenBoundingRect());

        b2Vec2 a = q_b2Joint->GetAnchorA();
        b2Vec2 b = q_b2Joint->GetAnchorB();
        painter->drawLine(a.x*sizeMultiplier,a.y*-sizeMultiplier,
                          b.x*sizeMultiplier, b.y*-sizeMultiplier);
    }

signals:
    
public slots:

private:
    b2Joint* q_b2Joint;
    
};

#endif // QBOX2DJOINT_H
