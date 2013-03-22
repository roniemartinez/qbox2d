#include "web.h"

Web::Web(const b2Vec2 &gravity, QObject *parent) :
    QBox2DTest(gravity, parent)
{
    QBox2DBody* ground = NULL;
    {
        b2BodyDef bd;
        ground = createBody(&bd);

        b2EdgeShape shape;
        shape.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
        ground->createFixture(&shape, 0.0f);
    }

    {
        b2PolygonShape shape;
        shape.SetAsBox(0.5f, 0.5f);

        b2BodyDef bd;
        bd.type = b2_dynamicBody;

        bd.position.Set(-5.0f, 5.0f);
        m_bodies[0] = createBody(&bd);
        m_bodies[0]->createFixture(&shape, 5.0f);

        bd.position.Set(5.0f, 5.0f);
        m_bodies[1] = createBody(&bd);
        m_bodies[1]->createFixture(&shape, 5.0f);

        bd.position.Set(5.0f, 15.0f);
        m_bodies[2] = createBody(&bd);
        m_bodies[2]->createFixture(&shape, 5.0f);

        bd.position.Set(-5.0f, 15.0f);
        m_bodies[3] = createBody(&bd);
        m_bodies[3]->createFixture(&shape, 5.0f);

        b2DistanceJointDef jd;
        b2Vec2 p1, p2, d;

        jd.frequencyHz = 2.0f;
        jd.dampingRatio = 0.0f;

        jd.bodyA = ground->body();
        jd.bodyB = m_bodies[0]->body();
        jd.localAnchorA.Set(-10.0f, 0.0f);
        jd.localAnchorB.Set(-0.5f, -0.5f);
        p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
        p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
        d = p2 - p1;
        jd.length = d.Length();
        m_joints[0] = createJoint(&jd);

        jd.bodyA = ground->body();
        jd.bodyB = m_bodies[1]->body();
        jd.localAnchorA.Set(10.0f, 0.0f);
        jd.localAnchorB.Set(0.5f, -0.5f);
        p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
        p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
        d = p2 - p1;
        jd.length = d.Length();
        m_joints[1] = createJoint(&jd);

        jd.bodyA = ground->body();
        jd.bodyB = m_bodies[2]->body();
        jd.localAnchorA.Set(10.0f, 20.0f);
        jd.localAnchorB.Set(0.5f, 0.5f);
        p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
        p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
        d = p2 - p1;
        jd.length = d.Length();
        m_joints[2] = createJoint(&jd);

        jd.bodyA = ground->body();
        jd.bodyB = m_bodies[3]->body();
        jd.localAnchorA.Set(-10.0f, 20.0f);
        jd.localAnchorB.Set(-0.5f, 0.5f);
        p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
        p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
        d = p2 - p1;
        jd.length = d.Length();
        m_joints[3] = createJoint(&jd);

        jd.bodyA = m_bodies[0]->body();
        jd.bodyB = m_bodies[1]->body();
        jd.localAnchorA.Set(0.5f, 0.0f);
        jd.localAnchorB.Set(-0.5f, 0.0f);;
        p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
        p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
        d = p2 - p1;
        jd.length = d.Length();
        m_joints[4] = createJoint(&jd);

        jd.bodyA = m_bodies[1]->body();
        jd.bodyB = m_bodies[2]->body();
        jd.localAnchorA.Set(0.0f, 0.5f);
        jd.localAnchorB.Set(0.0f, -0.5f);
        p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
        p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
        d = p2 - p1;
        jd.length = d.Length();
        m_joints[5] = createJoint(&jd);

        jd.bodyA = m_bodies[2]->body();
        jd.bodyB = m_bodies[3]->body();
        jd.localAnchorA.Set(-0.5f, 0.0f);
        jd.localAnchorB.Set(0.5f, 0.0f);
        p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
        p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
        d = p2 - p1;
        jd.length = d.Length();
        m_joints[6] = createJoint(&jd);

        jd.bodyA = m_bodies[3]->body();
        jd.bodyB = m_bodies[0]->body();
        jd.localAnchorA.Set(0.0f, -0.5f);
        jd.localAnchorB.Set(0.0f, 0.5f);
        p1 = jd.bodyA->GetWorldPoint(jd.localAnchorA);
        p2 = jd.bodyB->GetWorldPoint(jd.localAnchorB);
        d = p2 - p1;
        jd.length = d.Length();
        m_joints[7] = createJoint(&jd);
    }
}
