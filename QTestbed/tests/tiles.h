#ifndef TILES_H
#define TILES_H

#include <qbox2dworld.h>
#include <qbox2dbody.h>

class Tiles : public QBox2DWorld
{
    Q_OBJECT
public:
    explicit Tiles(const b2Vec2 &gravity, QObject *parent = 0);
    enum
    {
        e_count = 20
    };
signals:
    
public slots:
    
};

#endif // TILES_H
