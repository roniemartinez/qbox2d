#ifndef TUMBLER_H
#define TUMBLER_H

#include <qbox2dtest.h>

class Tumbler : public QBox2DTest
{
    Q_OBJECT
public:
    explicit Tumbler(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    enum
    {
        e_count = 800
    };
    void step() {
        QBox2DTest::step();

        if (m_count < e_count)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(0.0f, 10.0f);
            QBox2DBody* body = createBody(&bd);

            b2PolygonShape shape;
            shape.SetAsBox(0.125f, 0.125f);
            body->createFixture(&shape, 1.0f);

            ++m_count;
        }
    }

signals:
    
public slots:
    
private:
    b2RevoluteJoint* m_joint;
    int32 m_count;
};

#endif // TUMBLER_H
