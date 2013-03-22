#ifndef THEOJANSEN_H
#define THEOJANSEN_H

#include <qbox2dtest.h>

class TheoJansen : public QBox2DTest
{
    Q_OBJECT
public:
    explicit TheoJansen(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    void createLeg(float32 s, const b2Vec2& wheelAnchor);
    void setMotorSpeed(float32 s) {
        m_motorJoint->SetMotorSpeed(s);
    }
    float32 getMotorSpeed() {
        return m_motorSpeed;
    }

    void setToggleMotor() {
        m_motorJoint->EnableMotor(!m_motorJoint->IsMotorEnabled());
    }

signals:
    
public slots:
    
private:
    b2Vec2 m_offset;
    QBox2DBody* m_chassis;
    QBox2DBody* m_wheel;
    b2RevoluteJoint* m_motorJoint;
    bool m_motorOn;
    float32 m_motorSpeed;
};

#endif // THEOJANSEN_H
