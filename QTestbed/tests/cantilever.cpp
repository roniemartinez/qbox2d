#include "cantilever.h"

Cantilever::Cantilever(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    QBox2DBody* ground = NULL;
    {
        b2BodyDef bd;
        ground = createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.125f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 20.0f;

        b2WeldJointDef jd;

        QBox2DBody* prevBody = ground;
        for (int32 i = 0; i < e_count; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-14.5f + 1.0f * i, 5.0f);
            QBox2DBody* body = createBody(&bd);
            body->createFixture(&fd);

            b2Vec2 anchor(-15.0f + 1.0f * i, 5.0f);
            jd.Initialize(prevBody->body(), body->body(), anchor);
            createJoint(&jd);

            prevBody = body;
        }
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(1.0f, 0.125f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 20.0f;

        b2WeldJointDef jd;
        jd.frequencyHz = 5.0f;
        jd.dampingRatio = 0.7f;

        QBox2DBody* prevBody = ground;
        for (int32 i = 0; i < 3; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-14.0f + 2.0f * i, 15.0f);
            QBox2DBody* body = createBody(&bd);
            body->createFixture(&fd);

            b2Vec2 anchor(-15.0f + 2.0f * i, 15.0f);
            jd.Initialize(prevBody->body(), body->body(), anchor);
            createJoint(&jd);

            prevBody = body;
        }
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.125f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 20.0f;

        b2WeldJointDef jd;

        QBox2DBody* prevBody = ground;
        for (int32 i = 0; i < e_count; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-4.5f + 1.0f * i, 5.0f);
            QBox2DBody* body = createBody(&bd);
            body->createFixture(&fd);

            if (i > 0)
            {
                b2Vec2 anchor(-5.0f + 1.0f * i, 5.0f);
                jd.Initialize(prevBody->body(), body->body(), anchor);
                createJoint(&jd);
            }

            prevBody = body;
        }
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.125f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 20.0f;

        b2WeldJointDef jd;
        jd.frequencyHz = 8.0f;
        jd.dampingRatio = 0.7f;

        QBox2DBody* prevBody = ground;
        for (int32 i = 0; i < e_count; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(5.5f + 1.0f * i, 10.0f);
            QBox2DBody* body = createBody(&bd);
            body->createFixture(&fd);

            if (i > 0)
            {
                b2Vec2 anchor(5.0f + 1.0f * i, 10.0f);
                jd.Initialize(prevBody->body(), body->body(), anchor);
                createJoint(&jd);
            }

            prevBody = body;
        }
    }

    for (int32 i = 0; i < 2; ++i)
    {
        b2Vec2 vertices[3];
        vertices[0].Set(-0.5f, 0.0f);
        vertices[1].Set(0.5f, 0.0f);
        vertices[2].Set(0.0f, 1.5f);

        b2PolygonShape shape;
        shape.Set(vertices, 3);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 1.0f;

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(-8.0f + 8.0f * i, 12.0f);
        QBox2DBody* body = createBody(&bd);
        body->createFixture(&fd);
    }

    for (int32 i = 0; i < 2; ++i)
    {
        b2CircleShape shape;
        shape.m_radius = 0.5f;

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 1.0f;

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position.Set(-6.0f + 6.0f * i, 10.0f);
        QBox2DBody* body = createBody(&bd);
        body->createFixture(&fd);
    }
}
