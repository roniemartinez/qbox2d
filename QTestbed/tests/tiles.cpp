#include "tiles.h"

Tiles::Tiles(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    //modified codes taken from Tile example
    //FIXME: has performance problem when "warm starting" is unchecked due to many repaints
    int32 m_fixtureCount = 0;
    {
        float32 a = 0.5f;
        b2BodyDef bd;
        bd.position.y = -a;
        QBox2DBody* ground  = createBody(&bd);

#if 1
        int32 N = 200;
        int32 M = 10;
        b2Vec2 position;
        position.y = 0.0f;
        for (int32 j = 0; j < M; ++j)
        {
            position.x = -N * a;
            for (int32 i = 0; i < N; ++i)
            {
                b2PolygonShape shape;
                shape.SetAsBox(a, a, position, 0.0f);
                ground->createFixture(&shape, 0.0f);
                ++m_fixtureCount;
                position.x += 2.0f * a;
            }
            position.y -= 2.0f * a;
        }
#else
        int32 N = 200;
        int32 M = 10;
        b2Vec2 position;
        position.x = -N * a;
        for (int32 i = 0; i < N; ++i)
        {
            position.y = 0.0f;
            for (int32 j = 0; j < M; ++j)
            {
                b2PolygonShape shape;
                shape.SetAsBox(a, a, position, 0.0f);
                ground->createFixture(&shape, 0.0f);
                position.y -= 2.0f * a;
            }
            position.x += 2.0f * a;
        }
#endif
    }

    {
        float32 a = 0.5f;
        b2PolygonShape shape;
        shape.SetAsBox(a, a);

        b2Vec2 x(-7.0f, 0.75f);
        b2Vec2 y;
        b2Vec2 deltaX(0.5625f, 1.25f);
        b2Vec2 deltaY(1.125f, 0.0f);

        for (int32 i = 0; i < e_count; ++i)
        {
            y = x;

            for (int32 j = i; j < e_count; ++j)
            {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position = y;

                //if (i == 0 && j == 0)
                //{
                //	bd.allowSleep = false;
                //}
                //else
                //{
                //	bd.allowSleep = true;
                //}

                QBox2DBody* body  = createBody(&bd);
                body->createFixture(&shape, 5.0f);
                ++m_fixtureCount;
                y += deltaY;
            }

            x += deltaX;
        }
    }
}
