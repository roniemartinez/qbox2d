#include "qbox2dtest.h"

void DestructionListener::SayGoodbye(b2Joint* joint)
{
    /*
    if (test->m_mouseJoint == joint)
    {
        test->m_mouseJoint = NULL;
    }
    else*/
    {
        test->jointDestroyed(joint);
    }
}

QBox2DTest::QBox2DTest(const b2Vec2 &gravity, QObject *parent) :
    QBox2DWorld(gravity, parent)
{
    q_destructionListener.test = this;
    setDestructionListener(&q_destructionListener);
}
