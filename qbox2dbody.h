#ifndef QBOX2DBODY_H
#define QBOX2DBODY_H

#include <QGraphicsItemGroup>
#include <QPainter>
#include <QHash>
#include <QGraphicsScene>
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Collision/Shapes/b2ChainShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Dynamics/b2World.h>
#include <QDebug>
#include "qbox2dcommon.h"

class QBox2DBody : public QGraphicsItemGroup
{
public:
    explicit QBox2DBody(b2Body* qb2Body, QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        Q_UNUSED(painter);

        /*add this if you want to show a trace of the boundingRect*/
        //painter->drawRect(childrenBoundingRect());

        b2Vec2 position = getPosition();
        float32 angle = getAngle();
        qreal newRotation = -(angle * 360.0) / (2 * b2_pi);
        setPos(position.x*sizeMultiplier, position.y*-sizeMultiplier);
        if (!qFuzzyCompare(rotation(), newRotation))
            setRotation(newRotation);
        if (isSelected()) {
            painter->setBrush(Qt::transparent);
            painter->setPen(Qt::DashLine);
            painter->drawRect(childrenBoundingRect());
        }
    }
    b2Body* body() {
        return q_b2Body;
    }

    b2Fixture* createFixture(const b2Shape* shape, float32 density, const QBrush& brush = QBrush(Qt::green));
    b2Fixture* createFixture(const b2FixtureDef* def, const QBrush &brush = QBrush(Qt::green));
    void destroyFixture (b2Fixture *fixture) {
        removeFromGroup(q_b2FixtureManager[fixture]);
        scene()->removeItem(q_b2FixtureManager[fixture]);
        q_b2FixtureManager.remove(fixture);
        q_b2Body->DestroyFixture(fixture);
    }
    void setTransform(const b2Vec2 &position, float32 angle) {
        q_b2Body->SetTransform(position,angle);
    }
    const b2Transform& getTransform() const {
        return q_b2Body->GetTransform();
    }
    const b2Vec2& getPosition() const {
        return q_b2Body->GetPosition();
    }
    float32 getAngle() const {
        return q_b2Body->GetAngle();
    }
    const b2Vec2& getWorldCenter() const {
        return q_b2Body->GetWorldCenter();
    }
    const b2Vec2& getLocalCenter() const {
        return q_b2Body->GetLocalCenter();
    }
    void setLinearVelocity (const b2Vec2 &v) {
        q_b2Body->SetLinearVelocity(v);
    }
    b2Vec2 getLinearVelocity() const {
        return q_b2Body->GetLinearVelocity();
    }
    b2Vec2 getLocalPoint (const b2Vec2 &worldPoint) const {
        return q_b2Body->GetLocalPoint(worldPoint);
    }
    void setAngularVelocity(float32 omega) {
        q_b2Body->SetAngularVelocity(omega);
    }
    float32 getAngularVelocity() const {
        return q_b2Body->GetAngularVelocity();
    }
    void applyAngularImpulse(float32 impulse) {
        q_b2Body->ApplyAngularImpulse(impulse);
    }
    void setAwake(bool flag) {
        q_b2Body->SetAwake(flag);
    }
    bool isAwake() const {
        return q_b2Body->IsAwake();
    }

signals:
    
public slots:

private:
    b2Body* q_b2Body;
    QHash<b2Fixture*, QGraphicsItem*> q_b2FixtureManager;

    void processFixture(b2Fixture *qb2Fixture, const QBrush &brush);

};

#endif // QBOX2DBODY_H
