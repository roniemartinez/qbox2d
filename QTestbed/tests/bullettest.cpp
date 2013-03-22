#include "bullettest.h"

BulletTest::BulletTest(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent), m_stepCount(0)
{
    {
        b2BodyDef bd;
        bd.position.Set(0.0f, 0.0f);
        QBox2DBody* body = createBody(&bd);

        b2EdgeShape edge;

        edge.Set(b2Vec2(-10.0f, 0.0f), b2Vec2(10.0f, 0.0f));
        body->createFixture(&edge, 0.0f);

        b2PolygonShape shape;
        shape.SetAsBox(0.2f, 1.0f, b2Vec2(0.5f, 1.0f), 0.0f);
        body->createFixture(&shape, 0.0f);
    }

    {
        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(0.0f, 4.0f);

        b2PolygonShape box;
        box.SetAsBox(2.0f, 0.1f);

        m_body = createBody(&bd);
        m_body->createFixture(&box, 1.0f);

        box.SetAsBox(0.25f, 0.25f);

        //m_x = RandomFloat(-1.0f, 1.0f);
        m_x = 0.20352793f;
        bd.position.Set(m_x, 10.0f);
        bd.bullet = true;

        m_bullet = createBody(&bd);
        m_bullet->createFixture(&box, 100.0f);

        m_bullet->setLinearVelocity(b2Vec2(0.0f, -50.0f));
    }
}

void BulletTest::launch()
{
    m_body->setTransform(b2Vec2(0.0f, 4.0f), 0.0f);
    m_body->setLinearVelocity(b2Vec2_zero);
    m_body->setAngularVelocity(0.0f);


    m_x = randomFloat(-1.0f, 1.0f);
    m_bullet->setTransform(b2Vec2(m_x, 10.0f), 0.0f);
    m_bullet->setLinearVelocity(b2Vec2(0.0f, -50.0f));
    m_bullet->setAngularVelocity(0.0f);
}
