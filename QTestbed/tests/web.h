#ifndef WEB_H
#define WEB_H

#include <qbox2dtest.h>

class Web : public QBox2DTest
{
    Q_OBJECT
public:
    explicit Web(const b2Vec2& gravity = b2Vec2_zero, QObject *parent = 0);

    void destroyABody() {
        for (int32 i = 0; i < 4; ++i) {
            if (m_bodies[i])
            {
                destroyBody(m_bodies[i]);
                m_bodies[i] = NULL;
                break;
            }
        }
    }
    void destroyAJoint() {
        for (int32 i = 0; i < 8; ++i)
        {
            if (m_joints[i])
            {
                destroyJoint(m_joints[i]);
                m_joints[i] = NULL;
                break;
            }
        }
    }
    void jointDestroyed(b2Joint* joint)
    {
        for (int32 i = 0; i < 8; ++i)
        {
            if (m_joints[i]->joint() == joint)
            {
                m_joints[i] = NULL;
                break;
            }
        }
    }

signals:
    
public slots:
    
private:
    QBox2DBody* m_bodies[4];
    QBox2DJoint* m_joints[8];
};

#endif // WEB_H
