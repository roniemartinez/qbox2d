#ifndef CANTILEVER_H
#define CANTILEVER_H

#include <qbox2dtest.h>

class Cantilever : public QBox2DTest
{
    Q_OBJECT
public:
    explicit Cantilever(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    enum
    {
        e_count = 8
    };
signals:
    
public slots:
    
private:
    QBox2DBody* m_middle;
};

#endif // CANTILEVER_H
