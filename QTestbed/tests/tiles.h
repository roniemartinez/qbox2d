#ifndef TILES_H
#define TILES_H

#include <qbox2dtest.h>

class Tiles : public QBox2DTest
{
    Q_OBJECT
public:
    explicit Tiles(const b2Vec2 &gravity = b2Vec2_zero, QObject *parent = 0);
    enum
    {
        e_count = 20
    };
signals:
    
public slots:
    
};

#endif // TILES_H
