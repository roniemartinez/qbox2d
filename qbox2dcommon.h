#ifndef QBOX2DCOMMON_H
#define QBOX2DCOMMON_H

//QGraphicsScene specifics
static float sizeMultiplier = 10; //use this as a size factor for items in QBox2DWorld

//b2World specifics
static float32 timeStep = 1.0f / 60.0f;
static int32 velocityIterations = 8;
static int32 positionIterations = 3;

#endif // QBOX2DCOMMON_H
