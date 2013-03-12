/*
Copyright (c) 2013, Ronie P. Martinez <ronmarti18@gmail.com>
All rights reserved.

Permission to use, copy, modify, and/or distribute this software for any purpose
with or without fee is hereby granted, provided that the above copyright notice
and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT,
OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA
OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <QtGui>
#include <QObject>
#include <QApplication>
#include "qbox2dworld.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //QBox2DWorld - simulates b2World
    b2Vec2 gravity(0.0f, -10.0f);
    QBox2DWorld qWorld(gravity);
    qWorld.setItemIndexMethod(QGraphicsScene::NoIndex);
    qWorld.setBackgroundBrush(Qt::white);

    //POLYGONS
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);
    b2Body* groundBody = qWorld.createBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(5.0f, 1.0f, b2Vec2(0,2),b2_pi/18);
    groundBody->CreateFixture(&groundBox, 0.0f);
    b2PolygonShape groundBox2;
    groundBox2.SetAsBox(5.0f, 1.0f, b2Vec2(-10,0),-b2_pi/18);
    groundBody->CreateFixture(&groundBox2, 0.0f);
    b2PolygonShape groundBox3;
    groundBox3.SetAsBox(5.0f, 1.0f, b2Vec2(10,2),0);
    groundBody->CreateFixture(&groundBox3, 0.0f);


    for (int i = -2; i<=2; ++i) {
        //CIRCLE
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(i*3, 5.0f);
        b2Body *body = qWorld.createBody(&bodyDef);
        b2CircleShape dynamicBox;
        dynamicBox.m_radius = 1.0f;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.0f;
        fixtureDef.restitution = 0.6f;
        body->CreateFixture(&fixtureDef);
        //BOX
        b2BodyDef bodyDef1;
        bodyDef1.type = b2_dynamicBody;
        bodyDef1.position.Set(i*3, 2.0f);
        b2Body *body1 = qWorld.createBody(&bodyDef1);
        b2PolygonShape dynamicBox1;
        dynamicBox1.SetAsBox(1.0f, 1.0f);
        b2FixtureDef fixtureDef1;
        fixtureDef1.shape = &dynamicBox1;
        fixtureDef1.density = 1.0f;
        fixtureDef1.friction = 0.3f;
        fixtureDef1.restitution = 0.6f;
        body1->CreateFixture(&fixtureDef1);
    }

    //EDGE
    b2BodyDef bd;
    b2Body* ground = qWorld.createBody(&bd);
    b2Vec2 v1(-10.0f, 0.0f), v2(-2.0f, -2.0f);
    b2EdgeShape shape;
    shape.Set(v1, v2);
    ground->CreateFixture(&shape, 1.0f);


    QGraphicsView view(&qWorld);
    view.setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setRenderHint(QPainter::Antialiasing);
    view.setSceneRect(-400,-300,800,600);
    view.showMaximized();
    
    //start QBox2DWorld simulation
    qWorld.start();
    return a.exec();
}
