#include "shapeediting.h"

ShapeEditing::ShapeEditing(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    {
        b2BodyDef bd;
        QBox2DBody* ground = createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);
    }

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.position.Set(0.0f, 10.0f);
    m_body = createBody(&bd);

    b2PolygonShape shape;
    shape.SetAsBox(4.0f, 4.0f, b2Vec2(0.0f, 0.0f), 0.0f);
    m_fixture1 = m_body->createFixture(&shape, 10.0f);

    m_fixture2 = NULL;

    m_sensor = false;
}
