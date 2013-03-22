#include "car.h"

Car::Car(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    m_hz = 4.0f;
    m_zeta = 0.7f;
    m_speed = 50.0f;

    QBox2DBody* ground = NULL;
    {
        b2BodyDef bd;
        ground = createBody(&bd);

        b2EdgeShape shape;

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 0.0f;
        fd.friction = 0.6f;

        shape.Set(b2Vec2(-20.0f, 0.0f), b2Vec2(20.0f, 0.0f));
        ground->createFixture(&fd);

        float32 hs[10] = {0.25f, 1.0f, 4.0f, 0.0f, 0.0f, -1.0f, -2.0f, -2.0f, -1.25f, 0.0f};

        float32 x = 20.0f, y1 = 0.0f, dx = 5.0f;

        for (int32 i = 0; i < 10; ++i)
        {
            float32 y2 = hs[i];
            shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
            ground->createFixture(&fd);
            y1 = y2;
            x += dx;
        }

        for (int32 i = 0; i < 10; ++i)
        {
            float32 y2 = hs[i];
            shape.Set(b2Vec2(x, y1), b2Vec2(x + dx, y2));
            ground->createFixture(&fd);
            y1 = y2;
            x += dx;
        }

        shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
        ground->createFixture(&fd);

        x += 80.0f;
        shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
        ground->createFixture(&fd);

        x += 40.0f;
        shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 10.0f, 5.0f));
        ground->createFixture(&fd);

        x += 20.0f;
        shape.Set(b2Vec2(x, 0.0f), b2Vec2(x + 40.0f, 0.0f));
        ground->createFixture(&fd);

        x += 40.0f;
        shape.Set(b2Vec2(x, 0.0f), b2Vec2(x, 20.0f));
        ground->createFixture(&fd);
    }

    // Teeter
    {
        b2BodyDef bd;
        bd.position.Set(140.0f, 1.0f);
        bd.type = b2_dynamicBody;
        QBox2DBody* body = createBody(&bd);

        b2PolygonShape box;
        box.SetAsBox(10.0f, 0.25f);
        body->createFixture(&box, 1.0f);

        b2RevoluteJointDef jd;
        jd.Initialize(ground->body(), body->body(), body->getPosition());
        jd.lowerAngle = -8.0f * b2_pi / 180.0f;
        jd.upperAngle = 8.0f * b2_pi / 180.0f;
        jd.enableLimit = true;
        createJoint(&jd);

        body->applyAngularImpulse(100.0f);
    }

    // Bridge
    {
        int32 N = 20;
        b2PolygonShape shape;
        shape.SetAsBox(1.0f, 0.125f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 1.0f;
        fd.friction = 0.6f;

        b2RevoluteJointDef jd;

        QBox2DBody* prevBody = ground;
        for (int32 i = 0; i < N; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(161.0f + 2.0f * i, -0.125f);
            QBox2DBody* body = createBody(&bd);
            body->createFixture(&fd);

            b2Vec2 anchor(160.0f + 2.0f * i, -0.125f);
            jd.Initialize(prevBody->body(), body->body(), anchor);
            createJoint(&jd);

            prevBody = body;
        }

        b2Vec2 anchor(160.0f + 2.0f * N, -0.125f);
        jd.Initialize(prevBody->body(), ground->body(), anchor);
        createJoint(&jd);
    }

    // Boxes
    {
        b2PolygonShape box;
        box.SetAsBox(0.5f, 0.5f);

        QBox2DBody* body = NULL;
        b2BodyDef bd;
        bd.type = b2_dynamicBody;

        bd.position.Set(230.0f, 0.5f);
        body = createBody(&bd);
        body->createFixture(&box, 0.5f);

        bd.position.Set(230.0f, 1.5f);
        body = createBody(&bd);
        body->createFixture(&box, 0.5f);

        bd.position.Set(230.0f, 2.5f);
        body = createBody(&bd);
        body->createFixture(&box, 0.5f);

        bd.position.Set(230.0f, 3.5f);
        body = createBody(&bd);
        body->createFixture(&box, 0.5f);

        bd.position.Set(230.0f, 4.5f);
        body = createBody(&bd);
        body->createFixture(&box, 0.5f);
    }

    // Car
    {
        b2PolygonShape chassis;
        b2Vec2 vertices[8];
        vertices[0].Set(-1.5f, -0.5f);
        vertices[1].Set(1.5f, -0.5f);
        vertices[2].Set(1.5f, 0.0f);
        vertices[3].Set(0.0f, 0.9f);
        vertices[4].Set(-1.15f, 0.9f);
        vertices[5].Set(-1.5f, 0.2f);
        chassis.Set(vertices, 6);

        b2CircleShape circle;
        circle.m_radius = 0.4f;

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(0.0f, 1.0f);
        m_car = createBody(&bd);
        m_car->createFixture(&chassis, 1.0f);

        b2FixtureDef fd;
        fd.shape = &circle;
        fd.density = 1.0f;
        fd.friction = 0.9f;

        bd.position.Set(-1.0f, 0.35f);
        m_wheel1 = createBody(&bd);
        m_wheel1->createFixture(&fd);

        bd.position.Set(1.0f, 0.4f);
        m_wheel2 = createBody(&bd);
        m_wheel2->createFixture(&fd);

        b2WheelJointDef jd;
        b2Vec2 axis(0.0f, 1.0f);

        jd.Initialize(m_car->body(), m_wheel1->body(), m_wheel1->getPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 20.0f;
        jd.enableMotor = true;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        m_spring1 = (b2WheelJoint*)createJoint(&jd)->joint();

        jd.Initialize(m_car->body(), m_wheel2->body(), m_wheel2->getPosition(), axis);
        jd.motorSpeed = 0.0f;
        jd.maxMotorTorque = 10.0f;
        jd.enableMotor = false;
        jd.frequencyHz = m_hz;
        jd.dampingRatio = m_zeta;
        m_spring2 = (b2WheelJoint*)createJoint(&jd)->joint();
    }
}
