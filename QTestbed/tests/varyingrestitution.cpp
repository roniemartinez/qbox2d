#include "varyingrestitution.h"

VaryingRestitution::VaryingRestitution(const b2Vec2 &gravity, QObject *parent) :
    QBox2DWorld(gravity, parent)
{
    //modified codes taken from Varying Restitution example
    {
        b2BodyDef bd;
        QBox2DBody* ground = createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2CircleShape shape;
        shape.m_radius = 1.0f;

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 1.0f;

        float32 restitution[7] = {0.0f, 0.1f, 0.3f, 0.5f, 0.75f, 0.9f, 1.0f};

        for (int32 i = 0; i < 7; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-10.0f + 3.0f * i, 20.0f);

            QBox2DBody* body = createBody(&bd);

            fd.restitution = restitution[i];
            body->createFixture(&fd);
        }
    }
}
