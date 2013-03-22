#ifndef CHARACTERCOLLISION_H
#define CHARACTERCOLLISION_H

#include <qbox2dtest.h>

class CharacterCollision : public QBox2DTest
{
    Q_OBJECT
public:
    explicit CharacterCollision(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);

    void step() {
        //custom codes you want to call every "step"
        b2Vec2 v = m_character->getLinearVelocity();
        v.x = -5.0f;
        m_character->setLinearVelocity(v);

        QBox2DTest::step();
    }

signals:
    
public slots:

private:
    QBox2DBody* m_character;
    
};

#endif // CHARACTERCOLLISION_H
