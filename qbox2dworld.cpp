/*
Copyright (c) 2013, Ronie P. Martinez <ronmarti18@gmail.com>
All rights reserved.

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright notice
and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "qbox2dworld.h"
#include <QDebug>

QBox2DWorld::QBox2DWorld(const b2Vec2 &gravity, QObject *parent) :
    QGraphicsScene(parent)
{
    q_b2World = new b2World(gravity);
}

b2Body *QBox2DWorld::createBody(const b2BodyDef *qb2BodyDef)
{
    return q_b2World->CreateBody(qb2BodyDef);
    //addItem(qBox2DBody);

    //return qBox2DBody;
}

//will changed list from b2 to QBox2D prefix
QList<b2Body*> QBox2DWorld::getBodyList()
{
    QList<b2Body*> qb2BodyList;
    b2Body* qb2Body = q_b2World->GetBodyList();
    while (qb2Body != NULL) {
        qb2BodyList << qb2Body;
        qb2Body = qb2Body->GetNext();
    }
    return qb2BodyList;
}

QList<b2Contact*> QBox2DWorld::getContactList()
{
    QList<b2Contact*> qb2ContactList;
    b2Contact* qb2Contact = q_b2World->GetContactList();
    while (qb2Contact != NULL){
        qb2ContactList << qb2Contact;
        qb2Contact = qb2Contact->GetNext();
    }
    return qb2ContactList;
}

QList<b2Joint*> QBox2DWorld::getJointList()
{
    QList<b2Joint*> qb2JointList;
    b2Joint* qb2Joint = q_b2World->GetJointList();
    while (qb2Joint != NULL){
        qb2JointList << qb2Joint;
        qb2Joint = qb2Joint->GetNext();
    }
    return qb2JointList;
}

void QBox2DWorld::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == q_timerId) {
            q_b2World->Step(timeStep, velocityIterations, positionIterations);
            //update();
            //update is required so that all QBox2DBody and the like will repaint...
            //use this ONLY if you have a separate implementation of the items below
            //e.g. subclassing a QGraphicsItem for a specific fixture
            QList<b2Body*> bodyList = getBodyList();
            foreach (b2Body *body, bodyList) {
                b2Vec2 position = body->GetPosition();
                float32 angle = body->GetAngle();
                qreal newRotation = -(angle * 360.0) / (2 * b2_pi);
                if (!bodyManager.contains(body)) {
                    b2Fixture* fixture = body->GetFixtureList();
                    QList<b2Fixture *> fixtureList;
                    while (fixture != NULL) {
                        fixtureList << fixture;
                        fixture = fixture->GetNext();
                    }
                    QGraphicsItemGroup *qItem = new QGraphicsItemGroup;
                    addItem(qItem);
                    foreach (fixture, fixtureList) {
                        b2Shape *qb2Shape = fixture->GetShape();
                        switch (qb2Shape->GetType()) {
                        case 0:
                        {
                            QGraphicsEllipseItem* item = new QGraphicsEllipseItem;
                            b2CircleShape *qb2CircleShape = dynamic_cast<b2CircleShape*>(qb2Shape);
                            float32 qRadius = qb2CircleShape->m_radius*sizeMultiplier;
                            QRectF rect(-qRadius,-qRadius,2*qRadius,2*qRadius);
                            item->setRect(rect);
                            qItem->addToGroup(item);
                            //FIXME: by setting the style, the circle doesn't seem to rotate
                            item->setBrush(QBrush(Qt::green/*, Qt::HorPattern*/));
                        } break;
                        case 1:
                        {
                            QGraphicsLineItem *item =new QGraphicsLineItem;
                            b2EdgeShape *qb2EdgeShape = dynamic_cast<b2EdgeShape*>(qb2Shape);
                            b2Vec2 v1 = qb2EdgeShape->m_vertex1;
                            b2Vec2 v2 = qb2EdgeShape->m_vertex2;
                            item->setLine(v1.x*sizeMultiplier, v1.y*-sizeMultiplier,
                                          v2.x*sizeMultiplier, v2.y*-sizeMultiplier);
                            qItem->addToGroup(item);
                        } break;
                        case 2:
                        {
                            QGraphicsPolygonItem* item = new QGraphicsPolygonItem;
                            b2PolygonShape *qb2PolygonShape = dynamic_cast<b2PolygonShape*>(qb2Shape);
                            int32 vertexCount = qb2PolygonShape->GetVertexCount();
                            QPolygonF polygon;
                            for (int i=0; i<vertexCount; ++i) {
                                b2Vec2 vertex = qb2PolygonShape->GetVertex(i);
                                polygon << QPointF(vertex.x*sizeMultiplier, vertex.y*-sizeMultiplier);
                            }
                            item->setPolygon(polygon);
                            qItem->addToGroup(item);
                            item->setBrush(QBrush(Qt::blue /*, Qt::HorPattern*/));
                        } break;
                        }
                        bodyManager.insertMulti(body, qItem);
                    }
                    bodyManager[body]->setPos(position.x*sizeMultiplier, position.y*-sizeMultiplier);
                    if (!qFuzzyCompare(bodyManager[body]->rotation(), newRotation))
                        bodyManager[body]->setRotation(newRotation);
                }
                bodyManager[body]->setPos(position.x*sizeMultiplier, position.y*-sizeMultiplier);
                if (!qFuzzyCompare(bodyManager[body]->rotation(), newRotation))
                    bodyManager[body]->setRotation(newRotation);
            }
    }
    QObject::timerEvent(event);
}
