#include "qbox2dbody.h"

QBox2DBody::QBox2DBody(b2Body *qb2Body, QGraphicsItem *parent) :
    QGraphicsItemGroup(parent), q_b2Body(qb2Body)
{
}

void QBox2DBody::processFixture(b2Fixture *qb2Fixture, const QBrush& brush)
{
    b2Shape* qb2Shape = qb2Fixture->GetShape();
    switch (qb2Shape->GetType()) {
    case 0:
    {
        b2CircleShape *qb2CircleShape = dynamic_cast<b2CircleShape*>(qb2Shape);
        float32 qRadius = qb2CircleShape->m_radius*sizeMultiplier;
        const QRect rect(-qRadius,-qRadius,
                         2*qRadius,2*qRadius);
        QGraphicsEllipseItem* item =
                new QGraphicsEllipseItem(rect);
        addToGroup(item);
        item->setBrush(brush);
        q_b2FixtureManager.insertMulti(qb2Fixture, item);
    } break;
    case 1:
    {
        QGraphicsLineItem *item =new QGraphicsLineItem;
        b2EdgeShape *qb2EdgeShape = dynamic_cast<b2EdgeShape*>(qb2Shape);
        b2Vec2 v1 = qb2EdgeShape->m_vertex1;
        b2Vec2 v2 = qb2EdgeShape->m_vertex2;
        item->setLine(v1.x*sizeMultiplier, v1.y*-sizeMultiplier,
                      v2.x*sizeMultiplier, v2.y*-sizeMultiplier);
        addToGroup(item);
        q_b2FixtureManager.insertMulti(qb2Fixture, item);
    } break;
    case 2:
    {
        QGraphicsPolygonItem* item = new QGraphicsPolygonItem;
        item->setFlags(QGraphicsItem::ItemIsSelectable);
        b2PolygonShape *qb2PolygonShape = dynamic_cast<b2PolygonShape*>(qb2Shape);
        int32 vertexCount = qb2PolygonShape->GetVertexCount();
        QPolygonF polygon;
        for (int i=0; i<vertexCount; ++i) {
            b2Vec2 vertex = qb2PolygonShape->GetVertex(i);
            polygon << QPointF(vertex.x*sizeMultiplier, vertex.y*-sizeMultiplier);
        }
        item->setPolygon(polygon);
        addToGroup(item);
        item->setBrush(brush);
        q_b2FixtureManager.insertMulti(qb2Fixture, item);
    } break;
    case 3: //for chain shape
    {
        b2ChainShape *qb2ChainShape = dynamic_cast<b2ChainShape*>(qb2Shape);
        int32 vertexCount = qb2ChainShape->m_count;
        for (int i=0; i< vertexCount-1; ++i) {
            b2Vec2 v1 = qb2ChainShape->m_vertices[i];
            b2Vec2 v2 = qb2ChainShape->m_vertices[i+1];
            QGraphicsLineItem *item =new QGraphicsLineItem;
            item->setLine(v1.x*sizeMultiplier, v1.y*-sizeMultiplier,
                          v2.x*sizeMultiplier, v2.y*-sizeMultiplier);
            addToGroup(item);
            q_b2FixtureManager.insertMulti(qb2Fixture, item);
        }
    } break;
    default:
    {

    } break;
    }
}

b2Fixture* QBox2DBody::createFixture(const b2FixtureDef *def, const QBrush& brush)
{
    b2Fixture* qb2Fixture = q_b2Body->CreateFixture(def);
    processFixture(qb2Fixture, brush);
    return qb2Fixture;
}


b2Fixture* QBox2DBody::createFixture(const b2Shape *shape, float32 density, const QBrush &brush)
{
    b2Fixture* qb2Fixture = q_b2Body->CreateFixture(shape, density);
    processFixture(qb2Fixture, brush);
    return qb2Fixture;
}
