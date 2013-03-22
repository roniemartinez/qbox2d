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

#ifndef QBOX2DWORLD_H
#define QBOX2DWORLD_H

#include <QGraphicsScene>
#include <QTimerEvent>
#include <QGraphicsPolygonItem>
#include <QGraphicsEllipseItem>
#include <QHash>

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/Joints/b2Joint.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2ContactManager.h>
#include <Box2D/Dynamics/Joints/b2GearJoint.h>
#include <Box2D/Dynamics/Joints/b2PrismaticJoint.h>
#include <Box2D/Dynamics/Joints/b2RevoluteJoint.h>
#include "qbox2dcommon.h"
#include "qbox2dbody.h"
#include "qbox2djoint.h"

class QBox2DWorld : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit QBox2DWorld(const b2Vec2 &gravity = b2Vec2(0,0), QObject *parent = 0);
    ~QBox2DWorld() {
        delete q_b2World;
    }
    void start() {
        q_timerId = startTimer(q_timeStep*1000);
        q_isRunning = 1;
    }
    void pause() {
        killTimer(q_timerId);
        q_isRunning = 0;
    }

    QBox2DBody* createBody(const b2BodyDef *qb2BodyDef);
    void destroyBody(QBox2DBody *qb2Body) {
        removeItem(qb2Body);
        q_bodyManager.remove(qb2Body->body());
        q_b2World->DestroyBody(qb2Body->body());
    }
    QBox2DJoint* createJoint (const b2JointDef *def);
    void destroyJoint (QBox2DJoint *qb2Joint) {
        removeItem(qb2Joint);
        q_jointManager.remove(qb2Joint->joint());
        q_b2World->DestroyJoint(qb2Joint->joint());
    }
    b2Vec2 getGravity() {
        return q_b2World->GetGravity();
    }
    void setGravity(const b2Vec2 &qGravity) {
        q_b2World->SetGravity(qGravity);
    }
    bool isLocked() const {
        return q_b2World->IsLocked();
    }
    bool getAutoClearForces() const {
        return q_b2World->GetAutoClearForces();
    }
    void setAutoClearForces(bool flag) {
        q_b2World->SetAutoClearForces(flag);
    }
    void clearForces() {
        q_b2World->ClearForces();
    }
    void dump() {
        q_b2World->Dump();
    }
    QList<b2Body*> getBodyList();
    QList<b2Joint*> getJointList();
    QList<b2Contact*> getContactList();
    void setAllowSleeping(bool flag) {
        q_b2World->SetAllowSleeping(flag);
    }
    bool getAllowSleeping() const {
        return q_b2World->GetAllowSleeping();
    }
    void setWarmStarting(bool flag) {
        q_b2World->SetWarmStarting(flag);
    }
    bool getWarmStarting() const {
        return q_b2World->GetWarmStarting();
    }
    void setContinuousPhysics(bool flag) {
        q_b2World->SetContinuousPhysics(flag);
    }
    bool getContinuousPhysics() const {
        return q_b2World->GetContinuousPhysics();
    }
    void setSubStepping(bool flag) {
        q_b2World->SetSubStepping(flag);
    }
    bool getSubStepping() const {
        return q_b2World->GetSubStepping();
    }
    const b2ContactManager& getContactManager () const {
        return q_b2World->GetContactManager();
    }
    const b2Profile& getProfile () const {
        return q_b2World->GetProfile();
    }
    void setDestructionListener (b2DestructionListener *qListener) {
        q_b2World->SetDestructionListener(qListener);
    }
    void setContactFilter (b2ContactFilter *qFilter) {
        q_b2World->SetContactFilter(qFilter);
    }
    void setContactListener (b2ContactListener *qListener) {
        q_b2World->SetContactListener(qListener);
    }
    void setDebugDraw (b2Draw *qDebugDraw) {
        q_b2World->SetDebugDraw(qDebugDraw);
    }
    void drawDebugData() {
        q_b2World->DrawDebugData();
    }
    void queryAABB(b2QueryCallback *qCallback, const b2AABB &qAABB) const {
        q_b2World->QueryAABB(qCallback, qAABB);
    }
    void rayCast(b2RayCastCallback *qCallback, const b2Vec2 &qPoint1, const b2Vec2 &qPoint2) const {
        q_b2World->RayCast(qCallback, qPoint1, qPoint2);
    }
    int getProxyCount() const {
        return q_b2World->GetProxyCount();
    }
    int getBodyCount() const {
        return q_b2World->GetBodyCount();
    }
    int getJointCount() const {
        return q_b2World->GetJointCount();
    }
    int getContactCount() const {
        return q_b2World->GetContactCount();
    }
    int getTreeHeight() const {
        return q_b2World->GetTreeHeight();
    }
    int getTreeBalance() const {
        return q_b2World->GetTreeBalance();
    }
    float getTreeQuality() const {
        return q_b2World->GetTreeQuality();
    }

    void setTimeStep(float32 tStep) {
        killTimer(q_timerId);
        q_timeStep = tStep;
        start();
    }
    void setVelocityIterations(int32 velIters) {
        q_velocityIterations = velIters;
    }
    void setPositionIterations(int32 posIters) {
        q_positionIterations = posIters;
    }
    bool isRunning() {
        return q_isRunning;
    }
    virtual void step() {
        q_b2World->Step(q_timeStep, q_velocityIterations, q_positionIterations);

        //update is required so that all QBox2DBody, QBox2DJoint, etc will repaint
        update();
    }

signals:
    void showText(QString text);

public slots:
    void simulate(bool flag) {
        if (flag)
            start();
        else pause();
    }

protected:
    void timerEvent(QTimerEvent *event);

private:
    b2World *q_b2World;
    int q_timerId;
    float32 q_timeStep;
    int32 q_velocityIterations;
    int32 q_positionIterations;

    bool q_isRunning;

    QHash<b2Joint*, QGraphicsLineItem*> q_jointManager;
    QHash<b2Body*, QBox2DBody*> q_bodyManager;
};

#endif // QBOX2DWORLD_H
