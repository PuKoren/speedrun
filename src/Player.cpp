#include "Player.h"

float mMaxSpeed = 10.f;

Player::Player(scene::ISceneManager *p_smgr, Bullet *p_bullet, irr::IEventReceiver* p_event){
    m_smgr = p_smgr;
    m_bullet = p_bullet;
    m_event = (EventReceiver*)p_event;

    m_node = m_smgr->addCameraSceneNode();
    m_rbody = m_bullet->AddCapsule(m_node, 1.f);
    m_rbody->setLinearFactor(btVector3(1,1,1));
    m_rbody->setSleepingThresholds(0.f, 0.f);
    m_rbody->setAngularFactor(btVector3(0,0,0));
    //m_rbody->setUserPointer(this);
    m_layer = PLAYER;
}


Player::~Player(){

}

void Player::drawAll(){

}

void Player::collisionCallback(IBulletObject* p_obj){

}

void Player::update(u32 DeltaTime, GameStates::GAME_STATE &gs){
    btVector3 velocity = m_rbody->getLinearVelocity();
    btScalar speed = velocity.length();
    if(speed > mMaxSpeed) {
        velocity *= mMaxSpeed/speed;
        m_rbody->setLinearVelocity(velocity);
    }

    if(m_event->IsKeyDown(KEY_SPACE)){
        m_rbody->applyCentralImpulse(btVector3(0,3,0));
    }

    if(m_event->IsKeyDown(KEY_LCONTROL)){
        m_rbody->applyCentralImpulse(btVector3(0,-0.5,0));
    }

    if(m_event->IsKeyDown(KEY_KEY_A)){
        m_rbody->applyCentralImpulse(btVector3(-1,0,0));
    }

    if(m_event->IsKeyDown(KEY_KEY_D)){
        m_rbody->applyCentralImpulse(btVector3(1,0,0));
    }

    if(m_event->IsKeyDown(KEY_KEY_W)){
        m_rbody->applyCentralImpulse(btVector3(0,0,1));
    }

    if(m_event->IsKeyDown(KEY_KEY_S)){
        m_rbody->applyCentralImpulse(btVector3(0,0,-1));
    }
}
