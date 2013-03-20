#include "varyingfriction.h"

VaryingFriction::VaryingFriction(const b2Vec2 &gravity, QObject *parent) :
    QBox2DWorld(gravity, parent)
{

    //modified codes taken from Varying Friction example
    {
        b2BodyDef bd;
        QBox2DBody* ground = createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(13.0f, 0.25f);

        b2BodyDef bd;
        bd.position.Set(-4.0f, 22.0f);
        bd.angle = -0.25f;

        QBox2DBody* ground =  createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 1.0f);

        b2BodyDef bd;
        bd.position.Set(10.5f, 19.0f);

        QBox2DBody* ground =  createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(13.0f, 0.25f);

        b2BodyDef bd;
        bd.position.Set(4.0f, 14.0f);
        bd.angle = 0.25f;

        QBox2DBody* ground =  createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 1.0f);

        b2BodyDef bd;
        bd.position.Set(-10.5f, 11.0f);

        QBox2DBody* ground =  createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(13.0f, 0.25f);

        b2BodyDef bd;
        bd.position.Set(-4.0f, 6.0f);
        bd.angle = -0.25f;

        QBox2DBody* ground =  createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.5f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 25.0f;

        float friction[5] = {0.75f, 0.5f, 0.35f, 0.1f, 0.0f};

        for (int i = 0; i < 5; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-15.0f + 4.0f * i, 28.0f);
            QBox2DBody* body = createBody(&bd);

            fd.friction = friction[i];
            body->createFixture(&fd);
        }
    }
}
