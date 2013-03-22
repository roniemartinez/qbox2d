#include "verticalstack.h"

VerticalStack::VerticalStack(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    {
        b2BodyDef bd;
        QBox2DBody* ground = createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);

        shape.Set(b2Vec2(20.0f, 0.0f), b2Vec2(20.0f, 20.0f));
        ground->createFixture(&shape, 0.0f);
    }

    float32 xs[5] = {0.0f, -10.0f, -5.0f, 5.0f, 10.0f};

    for (int32 j = 0; j < e_columnCount; ++j)
    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.5f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 1.0f;
        fd.friction = 0.3f;

        for (int i = 0; i < e_rowCount; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;

            int32 n = j * e_rowCount + i;
            b2Assert(n < e_rowCount * e_columnCount);
            m_indices[n] = n;
            bd.userData = m_indices + n;

            float32 x = 0.0f;
            //float32 x = RandomFloat(-0.02f, 0.02f);
            //float32 x = i % 2 == 0 ? -0.025f : 0.025f;
            bd.position.Set(xs[j] + x, 0.752f + 1.54f * i);
            QBox2DBody* body = createBody(&bd);

            m_bodies[n] = body;

            body->createFixture(&fd);
        }
    }

    m_bullet = NULL;
}

void VerticalStack::createBullet()
{
    if (m_bullet != NULL)
    {
        destroyBody(m_bullet);
        m_bullet = NULL;
    }

    {
        b2CircleShape shape;
        shape.m_radius = 0.25f;

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 20.0f;
        fd.restitution = 0.05f;

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.bullet = true;
        bd.position.Set(-31.0f, 5.0f);

        m_bullet = createBody(&bd);
        m_bullet->createFixture(&fd);

        m_bullet->setLinearVelocity(b2Vec2(400.0f, 0.0f));
    }
}
