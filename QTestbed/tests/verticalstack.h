#ifndef VERTICALSTACK_H
#define VERTICALSTACK_H

#include <qbox2dtest.h>

class VerticalStack : public QBox2DTest
{
    Q_OBJECT
public:
    explicit VerticalStack(const b2Vec2& gravity = b2Vec2_zero, QObject *parent = 0);
    enum
    {
        e_columnCount = 5,
        e_rowCount = 16
        //e_columnCount = 1,
        //e_rowCount = 1
    };

    void createBullet();

signals:
    
public slots:
    
private:
    QBox2DBody* m_bullet;
    QBox2DBody* m_bodies[e_rowCount * e_columnCount];
    int32 m_indices[e_rowCount * e_columnCount];
};

#endif // VERTICALSTACK_H
