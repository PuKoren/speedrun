#pragma once
#include <irrlicht/irrlicht.h>
#include <list>
#include "IGameObject.h"
#include "EventReceiver.h"
#include "Bullet.h"
#include "IBulletObject.h"

class Player: public IGameObject, public IBulletObject {
public:
    Player(irr::scene::ISceneManager* p_smgr, Bullet* p_bullet, irr::IEventReceiver* p_event);
    virtual ~Player();
    virtual void collisionCallback(btVector3& p_obj);
    virtual void drawAll();
    virtual void update(irr::u32 DeltaTime, GameStates::GAME_STATE& gs);
    bool isColliding();
    bool canJump();
    bool canDash();
    void jump(float force);
    void dash(float force);
private:
    core::vector3df getCameraDirection();
    scene::ICameraSceneNode* camera;
    irr::scene::ISceneManager* m_smgr;
    irr::scene::ISceneNode* m_node;
    EventReceiver* m_event;
    btRigidBody* m_rbody;
    Bullet* m_bullet;
    LAYER m_layer;
    float lastCollision = 0.f;
    btVector3 lastCollisionNormal;
    float lastJump = 0.f;
    std::list<float> dashCooldowns;
};
