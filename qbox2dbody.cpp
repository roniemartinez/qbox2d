#include "qbox2dbody.h"

QBox2DBody::QBox2DBody(b2Body *qb2Body, QGraphicsItem *parent) :
    QGraphicsItemGroup(parent), q_b2Body(qb2Body)
{
}
