#include "tumbler.h"

Tumbler::Tumbler(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    QBox2DBody* ground = NULL;
    {
        b2BodyDef bd;
        ground = createBody(&bd);
    }

    {
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.allowSleep = false;
        bd.position.Set(0.0f, 10.0f);
        QBox2DBody* body = createBody(&bd);

        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 10.0f, b2Vec2( 10.0f, 0.0f), 0.0);
        body->createFixture(&shape, 5.0f);
        shape.SetAsBox(0.5f, 10.0f, b2Vec2(-10.0f, 0.0f), 0.0);
        body->createFixture(&shape, 5.0f);
        shape.SetAsBox(10.0f, 0.5f, b2Vec2(0.0f, 10.0f), 0.0);
        body->createFixture(&shape, 5.0f);
        shape.SetAsBox(10.0f, 0.5f, b2Vec2(0.0f, -10.0f), 0.0);
        body->createFixture(&shape, 5.0f);

        b2RevoluteJointDef jd;
        jd.bodyA = ground->body();
        jd.bodyB = body->body();
        jd.localAnchorA.Set(0.0f, 10.0f);
        jd.localAnchorB.Set(0.0f, 0.0f);
        jd.referenceAngle = 0.0f;
        jd.motorSpeed = 0.05f * b2_pi;
        jd.maxMotorTorque = 1e8f;
        jd.enableMotor = true;
        m_joint = (b2RevoluteJoint*)createJoint(&jd)->joint();
    }

    m_count = 0;
}
