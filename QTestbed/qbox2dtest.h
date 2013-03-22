#ifndef QBOX2DTEST_H
#define QBOX2DTEST_H

#include <qbox2dworld.h>

class QBox2DTest;

#define	RAND_LIMIT	32767

/// Random number in range [-1,1]
inline float32 randomFloat()
{
    float32 r = (float32)(qrand() & (RAND_LIMIT));
    r /= RAND_LIMIT;
    r = 2.0f * r - 1.0f;
    return r;
}

/// Random floating point number in range [lo, hi]
inline float32 randomFloat(float32 lo, float32 hi)
{
    float32 r = (float32)(qrand() & (RAND_LIMIT));
    r /= RAND_LIMIT;
    r = (hi - lo) * r + lo;
    return r;
}


class DestructionListener : public b2DestructionListener
{
public:
    void SayGoodbye(b2Fixture* fixture) { B2_NOT_USED(fixture); }
    void SayGoodbye(b2Joint* joint);

    QBox2DTest* test;
};

class QBox2DTest : public QBox2DWorld
{
    Q_OBJECT
public:
    explicit QBox2DTest(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);

    virtual void jointDestroyed(b2Joint* joint) { B2_NOT_USED(joint); }
signals:
    
public slots:
    
protected:
    friend class DestructionListener;

    DestructionListener q_destructionListener;
};

#endif // QBOX2DTEST_H
