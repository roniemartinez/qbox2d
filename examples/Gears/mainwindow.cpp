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


    //modified codes taken from Gears example
    b2RevoluteJoint* m_joint1;
    b2RevoluteJoint* m_joint2;
    b2PrismaticJoint* m_joint3;
    b2GearJoint* m_joint4;
    b2GearJoint* m_joint5;

    QBox2DBody* ground = NULL;
    {
        b2BodyDef bd;
        ground = qWorld->createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(50.0f, 0.0f), b2Vec2(-50.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);
    }

    // Gears co
    {
        b2CircleShape circle1;
        circle1.m_radius = 1.0f;

        b2PolygonShape box;
        box.SetAsBox(0.5f, 5.0f);

        b2CircleShape circle2;
        circle2.m_radius = 2.0f;

        b2BodyDef bd1;
        bd1.type = b2_staticBody;
        bd1.position.Set(10.0f, 9.0f);
        QBox2DBody* body1 = qWorld->createBody(&bd1);
        body1->createFixture(&circle1, 0.0f);

        b2BodyDef bd2;
        bd2.type = b2_dynamicBody;
        bd2.position.Set(10.0f, 8.0f);
        QBox2DBody* body2 = qWorld->createBody(&bd2);
        body2->createFixture(&box, 5.0f);

        b2BodyDef bd3;
        bd3.type = b2_dynamicBody;
        bd3.position.Set(10.0f, 6.0f);
        QBox2DBody* body3 = qWorld->createBody(&bd3);
        body3->createFixture(&circle2, 5.0f);

        b2RevoluteJointDef jd1;
        jd1.Initialize(body2->body(), body1->body(), bd1.position);
        b2Joint* joint1 = qWorld->createJoint(&jd1);

        b2RevoluteJointDef jd2;
        jd2.Initialize(body2->body(), body3->body(), bd3.position);
        b2Joint* joint2 = qWorld->createJoint(&jd2);

        b2GearJointDef jd4;
        jd4.bodyA = body1->body();
        jd4.bodyB = body3->body();
        jd4.joint1 = joint1;
        jd4.joint2 = joint2;
        jd4.ratio = circle2.m_radius / circle1.m_radius;
        qWorld->createJoint(&jd4);
    }

    {
        b2CircleShape circle1;
        circle1.m_radius = 1.0f;

        b2CircleShape circle2;
        circle2.m_radius = 2.0f;

        b2PolygonShape box;
        box.SetAsBox(0.5f, 5.0f);

        b2BodyDef bd1;
        bd1.type = b2_dynamicBody;
        bd1.position.Set(-3.0f, 12.0f);
        QBox2DBody* body1 = qWorld->createBody(&bd1);
        body1->createFixture(&circle1, 5.0f);

        b2RevoluteJointDef jd1;
        jd1.bodyA = ground->body();
        jd1.bodyB = body1->body();
        jd1.localAnchorA = ground->getLocalPoint(bd1.position);
        jd1.localAnchorB = body1->getLocalPoint(bd1.position);
        jd1.referenceAngle = body1->getAngle() - ground->getAngle();
        m_joint1 = (b2RevoluteJoint*)qWorld->createJoint(&jd1);

        b2BodyDef bd2;
        bd2.type = b2_dynamicBody;
        bd2.position.Set(0.0f, 12.0f);
        QBox2DBody* body2 = qWorld->createBody(&bd2);
        body2->createFixture(&circle2, 5.0f);

        b2RevoluteJointDef jd2;
        jd2.Initialize(ground->body(), body2->body(), bd2.position);
        m_joint2 = (b2RevoluteJoint*)qWorld->createJoint(&jd2);

        b2BodyDef bd3;
        bd3.type = b2_dynamicBody;
        bd3.position.Set(2.5f, 12.0f);
        QBox2DBody* body3 = qWorld->createBody(&bd3);
        body3->createFixture(&box, 5.0f);

        b2PrismaticJointDef jd3;
        jd3.Initialize(ground->body(), body3->body(), bd3.position, b2Vec2(0.0f, 1.0f));
        jd3.lowerTranslation = -5.0f;
        jd3.upperTranslation = 5.0f;
        jd3.enableLimit = true;

        m_joint3 = (b2PrismaticJoint*)qWorld->createJoint(&jd3);

        b2GearJointDef jd4;
        jd4.bodyA = body1->body();
        jd4.bodyB = body2->body();
        jd4.joint1 = m_joint1;
        jd4.joint2 = m_joint2;
        jd4.ratio = circle2.m_radius / circle1.m_radius;
        m_joint4 = (b2GearJoint*)qWorld->createJoint(&jd4);

        b2GearJointDef jd5;
        jd5.bodyA = body2->body();
        jd5.bodyB = body3->body();
        jd5.joint1 = m_joint2;
        jd5.joint2 = m_joint3;
        jd5.ratio = -1.0f / circle2.m_radius;
        m_joint5 = (b2GearJoint*)qWorld->createJoint(&jd5);
    }

}

MainWindow::~MainWindow()
{
    
}
