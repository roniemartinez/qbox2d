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


    //modified codes taken from Varying Friction example
    {
        b2BodyDef bd;
        QBox2DBody* ground = qWorld->createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(13.0f, 0.25f);

        b2BodyDef bd;
        bd.position.Set(-4.0f, 22.0f);
        bd.angle = -0.25f;

        QBox2DBody* ground = qWorld->createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 1.0f);

        b2BodyDef bd;
        bd.position.Set(10.5f, 19.0f);

        QBox2DBody* ground = qWorld->createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(13.0f, 0.25f);

        b2BodyDef bd;
        bd.position.Set(4.0f, 14.0f);
        bd.angle = 0.25f;

        QBox2DBody* ground = qWorld->createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.25f, 1.0f);

        b2BodyDef bd;
        bd.position.Set(-10.5f, 11.0f);

        QBox2DBody* ground = qWorld->createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(13.0f, 0.25f);

        b2BodyDef bd;
        bd.position.Set(-4.0f, 6.0f);
        bd.angle = -0.25f;

        QBox2DBody* ground = qWorld->createBody(&bd);
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.5f);

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 25.0f;

        float friction[5] = {0.75f, 0.5f, 0.35f, 0.1f, 0.0f};

        for (int i = 0; i < 5; ++i)
        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-15.0f + 4.0f * i, 28.0f);
            QBox2DBody* body = qWorld->createBody(&bd);

            fd.friction = friction[i];
            body->createFixture(&fd);
        }
    }
}

MainWindow::~MainWindow()
{
    
}
