#pragma once
#include <irrlicht/irrlicht.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "config.h"

enum LAYER{
    NONE,
    FLOOR,
    PLAYER
};

class IBulletObject{
public:
    LAYER m_layer = NONE;
    virtual ~IBulletObject() {}
    virtual void collisionCallback(btVector3&) = 0;
};

