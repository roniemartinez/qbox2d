#ifndef BULLETTEST_H
#define BULLETTEST_H

#include <qbox2dtest.h>

class BulletTest : public QBox2DTest
{
    Q_OBJECT
public:
    explicit BulletTest(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    void step() {
        m_stepCount++;
        if (m_stepCount % 60 == 0)
        {
            launch();
        }
        QBox2DTest::step();
    }
    void launch();
signals:
    
public slots:
    
private:
    QBox2DBody* m_body;
    QBox2DBody* m_bullet;
    float32 m_x;
    int m_stepCount;
};

#endif // BULLETTEST_H
