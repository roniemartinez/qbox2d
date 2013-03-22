#ifndef CAR_H
#define CAR_H

#include <qbox2dtest.h>
#include <QGraphicsView>

class Car : public QBox2DTest
{
    Q_OBJECT
public:
    explicit Car(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    void step()	{
        QList<QGraphicsView*> viewList = views();
        foreach (QGraphicsView* view, viewList) {
            view->centerOn(m_car->x(), 0);
        }
        QBox2DTest::step();
    }
    void setMotorSpeed(float32 s) {
        m_spring1->SetMotorSpeed(s);
    }
    float32 getMotorSpeed() {
        return m_speed;
    }
    float32 getSpringFrequencyHz() {
        return m_hz;
    }
    void setSpringFrequencyHz(float32 f) {
        m_hz = f;
        m_spring1->SetSpringFrequencyHz(f);
        m_spring2->SetSpringFrequencyHz(f);
    }

signals:

public slots:
    
private:
    QBox2DBody* m_car;
    QBox2DBody* m_wheel1;
    QBox2DBody* m_wheel2;

    float32 m_hz;
    float32 m_zeta;
    float32 m_speed;
    b2WheelJoint* m_spring1;
    b2WheelJoint* m_spring2;
};

#endif // CAR_H
