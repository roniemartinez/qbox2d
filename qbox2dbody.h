#ifndef QBOX2DBODY_H
#define QBOX2DBODY_H

#include <QGraphicsItemGroup>
#include <QPainter>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include "qbox2dcommon.h"

class QBox2DBody : public QGraphicsItemGroup
{
public:
    explicit QBox2DBody(b2Body* qb2Body, QGraphicsItem *parent = 0);
    ~QBox2DBody() {}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        /*add this if you want to show a trace of the boundingRect*/
        //painter->drawRect(childrenBoundingRect());        
        Q_UNUSED(painter);


        b2Vec2 position = q_b2Body->GetPosition();
        float32 angle = q_b2Body->GetAngle();
        qreal newRotation = -(angle * 360.0) / (2 * b2_pi);
        setPos(position.x*sizeMultiplier, position.y*-sizeMultiplier);
        if (!qFuzzyCompare(rotation(), newRotation))
            setRotation(newRotation);
    }

signals:
    
public slots:

private:
    b2Body* q_b2Body;

};

#endif // QBOX2DBODY_H
