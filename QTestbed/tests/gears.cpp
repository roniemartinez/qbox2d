#include "gears.h"

Gears::Gears(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    //modified codes taken from Gears example
    b2RevoluteJoint* m_joint1;
    b2RevoluteJoint* m_joint2;
    b2PrismaticJoint* m_joint3;
    b2GearJoint* m_joint4;
    b2GearJoint* m_joint5;

    QBox2DBody* ground = NULL;
    {
        b2BodyDef bd;
        ground = createBody(&bd);

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
        QBox2DBody* body1 = createBody(&bd1);
        body1->createFixture(&circle1, 0.0f);

        b2BodyDef bd2;
        bd2.type = b2_dynamicBody;
        bd2.position.Set(10.0f, 8.0f);
        QBox2DBody* body2 = createBody(&bd2);
        body2->createFixture(&box, 5.0f);

        b2BodyDef bd3;
        bd3.type = b2_dynamicBody;
        bd3.position.Set(10.0f, 6.0f);
        QBox2DBody* body3 = createBody(&bd3);
        body3->createFixture(&circle2, 5.0f);

        b2RevoluteJointDef jd1;
        jd1.Initialize(body2->body(), body1->body(), bd1.position);
        QBox2DJoint* joint1 = createJoint(&jd1);

        b2RevoluteJointDef jd2;
        jd2.Initialize(body2->body(), body3->body(), bd3.position);
        QBox2DJoint* joint2 = createJoint(&jd2);

        b2GearJointDef jd4;
        jd4.bodyA = body1->body();
        jd4.bodyB = body3->body();
        jd4.joint1 = joint1->joint();
        jd4.joint2 = joint2->joint();
        jd4.ratio = circle2.m_radius / circle1.m_radius;
        createJoint(&jd4);
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
        QBox2DBody* body1 = createBody(&bd1);
        body1->createFixture(&circle1, 5.0f);

        b2RevoluteJointDef jd1;
        jd1.bodyA = ground->body();
        jd1.bodyB = body1->body();
        jd1.localAnchorA = ground->getLocalPoint(bd1.position);
        jd1.localAnchorB = body1->getLocalPoint(bd1.position);
        jd1.referenceAngle = body1->getAngle() - ground->getAngle();
        m_joint1 = (b2RevoluteJoint*)createJoint(&jd1)->joint();

        b2BodyDef bd2;
        bd2.type = b2_dynamicBody;
        bd2.position.Set(0.0f, 12.0f);
        QBox2DBody* body2 = createBody(&bd2);
        body2->createFixture(&circle2, 5.0f);

        b2RevoluteJointDef jd2;
        jd2.Initialize(ground->body(), body2->body(), bd2.position);
        m_joint2 = (b2RevoluteJoint*)createJoint(&jd2)->joint();

        b2BodyDef bd3;
        bd3.type = b2_dynamicBody;
        bd3.position.Set(2.5f, 12.0f);
        QBox2DBody* body3 = createBody(&bd3);
        body3->createFixture(&box, 5.0f);

        b2PrismaticJointDef jd3;
        jd3.Initialize(ground->body(), body3->body(), bd3.position, b2Vec2(0.0f, 1.0f));
        jd3.lowerTranslation = -5.0f;
        jd3.upperTranslation = 5.0f;
        jd3.enableLimit = true;

        m_joint3 = (b2PrismaticJoint*)createJoint(&jd3)->joint();

        b2GearJointDef jd4;
        jd4.bodyA = body1->body();
        jd4.bodyB = body2->body();
        jd4.joint1 = m_joint1;
        jd4.joint2 = m_joint2;
        jd4.ratio = circle2.m_radius / circle1.m_radius;
        m_joint4 = (b2GearJoint*)createJoint(&jd4)->joint();

        b2GearJointDef jd5;
        jd5.bodyA = body2->body();
        jd5.bodyB = body3->body();
        jd5.joint1 = m_joint2;
        jd5.joint2 = m_joint3;
        jd5.ratio = -1.0f / circle2.m_radius;
        m_joint5 = (b2GearJoint*)createJoint(&jd5)->joint();
    }
}
