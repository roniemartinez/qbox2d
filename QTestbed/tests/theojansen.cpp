#include "theojansen.h"

TheoJansen::TheoJansen(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    m_offset.Set(0.0f, 8.0f);
    m_motorSpeed = 2.0f;
    m_motorOn = true;
    b2Vec2 pivot(0.0f, 0.8f);

    // Ground
    {
        b2BodyDef bd;
        QBox2DBody* ground = createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(-50.0f, 0.0f), b2Vec2(50.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);

        shape.Set(b2Vec2(-50.0f, 0.0f), b2Vec2(-50.0f, 10.0f));
        ground->createFixture(&shape, 0.0f);

        shape.Set(b2Vec2(50.0f, 0.0f), b2Vec2(50.0f, 10.0f));
        ground->createFixture(&shape, 0.0f);
    }

    // Balls
    for (int32 i = 0; i < 40; ++i)
    {
        b2CircleShape shape;
        shape.m_radius = 0.25f;

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(-40.0f + 2.0f * i, 0.5f);

        QBox2DBody* body = createBody(&bd);
        body->createFixture(&shape, 1.0f);
    }

    // Chassis
    {
        b2PolygonShape shape;
        shape.SetAsBox(2.5f, 1.0f);

        b2FixtureDef sd;
        sd.density = 1.0f;
        sd.shape = &shape;
        sd.filter.groupIndex = -1;
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position = pivot + m_offset;
        m_chassis = createBody(&bd);
        m_chassis->createFixture(&sd);
    }

    {
        b2CircleShape shape;
        shape.m_radius = 1.6f;

        b2FixtureDef sd;
        sd.density = 1.0f;
        sd.shape = &shape;
        sd.filter.groupIndex = -1;
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position = pivot + m_offset;
        m_wheel = createBody(&bd);
        m_wheel->createFixture(&sd);
    }

    {
        b2RevoluteJointDef jd;
        jd.Initialize(m_wheel->body(), m_chassis->body(), pivot + m_offset);
        jd.collideConnected = false;
        jd.motorSpeed = m_motorSpeed;
        jd.maxMotorTorque = 400.0f;
        jd.enableMotor = m_motorOn;
        //m_motorJoint = (b2RevoluteJoint*)createJoint(&jd);
        QBox2DJoint* qJoint = createJoint(&jd);
        m_motorJoint = (b2RevoluteJoint*)qJoint->joint();
    }

    b2Vec2 wheelAnchor;

    wheelAnchor = pivot + b2Vec2(0.0f, -0.8f);

    createLeg(-1.0f, wheelAnchor);
    createLeg(1.0f, wheelAnchor);

    m_wheel->setTransform(m_wheel->getPosition(), 120.0f * b2_pi / 180.0f);
    createLeg(-1.0f, wheelAnchor);
    createLeg(1.0f, wheelAnchor);

    m_wheel->setTransform(m_wheel->getPosition(), -120.0f * b2_pi / 180.0f);
    createLeg(-1.0f, wheelAnchor);
    createLeg(1.0f, wheelAnchor);
}

void TheoJansen::createLeg(float32 s, const b2Vec2 &wheelAnchor)
{
    b2Vec2 p1(5.4f * s, -6.1f);
    b2Vec2 p2(7.2f * s, -1.2f);
    b2Vec2 p3(4.3f * s, -1.9f);
    b2Vec2 p4(3.1f * s, 0.8f);
    b2Vec2 p5(6.0f * s, 1.5f);
    b2Vec2 p6(2.5f * s, 3.7f);

    b2FixtureDef fd1, fd2;
    fd1.filter.groupIndex = -1;
    fd2.filter.groupIndex = -1;
    fd1.density = 1.0f;
    fd2.density = 1.0f;

    b2PolygonShape poly1, poly2;

    if (s > 0.0f)
    {
        b2Vec2 vertices[3];

        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        poly1.Set(vertices, 3);

        vertices[0] = b2Vec2_zero;
        vertices[1] = p5 - p4;
        vertices[2] = p6 - p4;
        poly2.Set(vertices, 3);
    }
    else
    {
        b2Vec2 vertices[3];

        vertices[0] = p1;
        vertices[1] = p3;
        vertices[2] = p2;
        poly1.Set(vertices, 3);

        vertices[0] = b2Vec2_zero;
        vertices[1] = p6 - p4;
        vertices[2] = p5 - p4;
        poly2.Set(vertices, 3);
    }

    fd1.shape = &poly1;
    fd2.shape = &poly2;

    b2BodyDef bd1, bd2;
    bd1.type = b2_dynamicBody;
    bd2.type = b2_dynamicBody;
    bd1.position = m_offset;
    bd2.position = p4 + m_offset;

    bd1.angularDamping = 10.0f;
    bd2.angularDamping = 10.0f;

    QBox2DBody* body1 = createBody(&bd1);
    QBox2DBody* body2 = createBody(&bd2);

    body1->createFixture(&fd1);
    body2->createFixture(&fd2);

    b2DistanceJointDef djd;

    // Using a soft distance constraint can reduce some jitter.
    // It also makes the structure seem a bit more fluid by
    // acting like a suspension system.
    djd.dampingRatio = 0.5f;
    djd.frequencyHz = 10.0f;

    djd.Initialize(body1->body(), body2->body(), p2 + m_offset, p5 + m_offset);
    createJoint(&djd);

    djd.Initialize(body1->body(), body2->body(), p3 + m_offset, p4 + m_offset);
    createJoint(&djd);

    djd.Initialize(body1->body(), m_wheel->body(), p3 + m_offset, wheelAnchor + m_offset);
    createJoint(&djd);

    djd.Initialize(body2->body(), m_wheel->body(), p6 + m_offset, wheelAnchor + m_offset);
    createJoint(&djd);

    b2RevoluteJointDef rjd;

    rjd.Initialize(body2->body(), m_chassis->body(), p4 + m_offset);
    createJoint(&rjd);
}
