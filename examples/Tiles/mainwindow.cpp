#include "mainwindow.h"

#include <qbox2dbody.h>
#include <qbox2dworld.h>
#include "../qbox2dview.h"

#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    QMenu* fileMenu = menuBar->addMenu("&File");
    QAction* simulation = new QAction("&Start/Pause",this);
    simulation->setCheckable(true);
    fileMenu->addAction(simulation);

    b2Vec2 gravity(0.0f, -10.0f);
    QBox2DWorld *qWorld = new QBox2DWorld(gravity);
    //qWorld->setSceneRect(-5000, -5000, 10000, 10000);
    QBox2DView *view = new QBox2DView;
    view->setScene(qWorld);
    setCentralWidget(view);
    showMaximized();
    QObject::connect(simulation, SIGNAL(toggled(bool)), qWorld, SLOT(simulate(bool)));


    //modified codes taken from Tile example
    int32 m_fixtureCount = 0;
    {
        float32 a = 0.5f;
        b2BodyDef bd;
        bd.position.y = -a;
        QBox2DBody* ground = qWorld->createBody(&bd);

#if 1
        int32 N = 200;
        int32 M = 10;
        b2Vec2 position;
        position.y = 0.0f;
        for (int32 j = 0; j < M; ++j)
        {
            position.x = -N * a;
            for (int32 i = 0; i < N; ++i)
            {
                b2PolygonShape shape;
                shape.SetAsBox(a, a, position, 0.0f);
                ground->createFixture(&shape, 0.0f);
                ++m_fixtureCount;
                position.x += 2.0f * a;
            }
            position.y -= 2.0f * a;
        }
#else
        int32 N = 200;
        int32 M = 10;
        b2Vec2 position;
        position.x = -N * a;
        for (int32 i = 0; i < N; ++i)
        {
            position.y = 0.0f;
            for (int32 j = 0; j < M; ++j)
            {
                b2PolygonShape shape;
                shape.SetAsBox(a, a, position, 0.0f);
                ground->createFixture(&shape, 0.0f);
                position.y -= 2.0f * a;
            }
            position.x += 2.0f * a;
        }
#endif
    }

    {
        float32 a = 0.5f;
        b2PolygonShape shape;
        shape.SetAsBox(a, a);

        b2Vec2 x(-7.0f, 0.75f);
        b2Vec2 y;
        b2Vec2 deltaX(0.5625f, 1.25f);
        b2Vec2 deltaY(1.125f, 0.0f);

        for (int32 i = 0; i < e_count; ++i)
        {
            y = x;

            for (int32 j = i; j < e_count; ++j)
            {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position = y;

                //if (i == 0 && j == 0)
                //{
                //	bd.allowSleep = false;
                //}
                //else
                //{
                //	bd.allowSleep = true;
                //}

                QBox2DBody* body = qWorld->createBody(&bd);
                body->createFixture(&shape, 5.0f);
                ++m_fixtureCount;
                y += deltaY;
            }

            x += deltaX;
        }
    }
}

MainWindow::~MainWindow()
{
    
}
