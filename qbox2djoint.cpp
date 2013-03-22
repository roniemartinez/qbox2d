#include "qbox2djoint.h"

QBox2DJoint::QBox2DJoint(b2Joint *qb2Joint, QGraphicsItem *parent) :
    QGraphicsLineItem(parent), q_b2Joint(qb2Joint)
{
}
