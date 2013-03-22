#ifndef SHAPEEDITING_H
#define SHAPEEDITING_H

#include <qbox2dtest.h>

class ShapeEditing : public QBox2DTest
{
    Q_OBJECT
public:
    explicit ShapeEditing(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    void create() {
        if (m_fixture2 == NULL)
        {
            b2CircleShape shape;
            shape.m_radius = 3.0f;
            shape.m_p.Set(0.5f, -4.0f);
            m_fixture2 = m_body->createFixture(&shape, 10.0f);
            m_body->setAwake(true);
        }
    }
    void destroy() {
        if (m_fixture2 != NULL)
        {
            m_body->destroyFixture(m_fixture2);
            m_fixture2 = NULL;
            m_body->setAwake(true);
        }
    }
    void sensor() {
        if (m_fixture2 != NULL)
        {
            m_sensor = !m_sensor;
            m_fixture2->SetSensor(m_sensor);
        }
    }
signals:
    
public slots:
    
private:
    QBox2DBody* m_body;
    b2Fixture* m_fixture1;
    b2Fixture* m_fixture2;
    bool m_sensor;
};

#endif // SHAPEEDITING_H
