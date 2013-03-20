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
    QGraphicsScene(parent), q_isRunning(0)
{
    q_b2World = new b2World(gravity);
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setBackgroundBrush(Qt::white);
    q_timeStep = timeStep;
    q_velocityIterations = velocityIterations;
    q_positionIterations = positionIterations;
}

QBox2DBody* QBox2DWorld::createBody(const b2BodyDef *qb2BodyDef)
{
    QBox2DBody* qb2Body = new QBox2DBody(q_b2World->CreateBody(qb2BodyDef));
    addItem(qb2Body);
    return qb2Body;
}

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
        step();
    }
    QObject::timerEvent(event);
}
