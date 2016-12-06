#include "Player.h"

float mMaxSpeed = 100.f;
const float JUMP_SPEED = 0.25f;
const float ACCELERATION_SPEED = 0.12f;
const float JUMPDOWN_SPEED = 0.10f;
scene::ICameraSceneNode* camera;

Player::Player(scene::ISceneManager *p_smgr, Bullet *p_bullet, irr::IEventReceiver* p_event){
    m_smgr = p_smgr;
    m_bullet = p_bullet;
    m_event = (EventReceiver*)p_event;

    m_node = m_smgr->addCubeSceneNode(1.f, 0, -1, core::vector3df(0.f, 0.f, -20.f), core::vector3df(0.f, 0.f, 0.f), core::vector3df(1.f, 3.f, 1.f));

    camera = m_smgr->addCameraSceneNodeFPS(0, 100.f, 0.f);

    m_rbody = m_bullet->AddCapsule(m_node, 10.f);
    m_rbody->setLinearFactor(btVector3(1,1,1));
    m_rbody->setSleepingThresholds(0.f, 0.f);
    m_rbody->setAngularFactor(btVector3(0,0,0));
    m_rbody->setFriction(0.8f);

    //m_rbody->setUserPointer(this);
    m_layer = PLAYER;
}


Player::~Player(){

}

void Player::drawAll(){

}

void Player::collisionCallback(IBulletObject* p_obj){

}

core::vector3df Player::getCameraDirection() {
    core::vector3df target = camera->getTarget();
    core::vector3df position = camera->getPosition();
    target.Y = 0.f;
    position.Y = 0.f;

    return (target - position).normalize();
}

void Player::update(u32 DeltaTime, GameStates::GAME_STATE &gs){
    btVector3 velocity = m_rbody->getLinearVelocity();
    btScalar speed = velocity.length();
    if(speed > mMaxSpeed) {
        velocity *= mMaxSpeed/speed;
        m_rbody->setLinearVelocity(velocity);
    }

    core::vector3df cameraPosition = m_node->getPosition();
    camera->setPosition(cameraPosition);

    if(m_event->IsKeyDown(KEY_SPACE)){
        this->canJump = false;
        m_rbody->applyCentralImpulse(btVector3(0,JUMP_SPEED * DeltaTime,0));
    }

    if(m_event->IsKeyDown(KEY_LCONTROL)){
        m_rbody->applyCentralImpulse(btVector3(0,-JUMPDOWN_SPEED * DeltaTime,0));
    }

    //forward/backward
    if(m_event->IsKeyDown(KEY_KEY_W) || m_event->IsKeyDown(KEY_KEY_S)){
        core::vector3df cameraVectForward = getCameraDirection();

        float acceleration = 0.f;

        if (m_event->IsKeyDown(KEY_KEY_W)) {
            acceleration += ACCELERATION_SPEED * DeltaTime;
        }
        if(m_event->IsKeyDown(KEY_KEY_S)){
            acceleration -= ACCELERATION_SPEED * DeltaTime;
        }

        m_rbody->applyCentralImpulse(acceleration * btVector3(cameraVectForward.X, cameraVectForward.Y, cameraVectForward.Z));
    }

    //steer
    if(m_event->IsKeyDown(KEY_KEY_A) || m_event->IsKeyDown(KEY_KEY_D)){
        core::vector3df cameraVectForward = getCameraDirection();

        float acceleration = 0.f;
        core::vector3df cameraVectSteer = cameraVectForward;

        core::matrix4 m;
        m.setRotationDegrees(core::vector3df(0.f, 90.f, 0.f));
        m.rotateVect(cameraVectSteer);

        if (m_event->IsKeyDown(KEY_KEY_A)) {
            acceleration -= ACCELERATION_SPEED * DeltaTime;
        }

        if(m_event->IsKeyDown(KEY_KEY_D)) {
            acceleration += ACCELERATION_SPEED * DeltaTime;
        }

        m_rbody->applyCentralImpulse(acceleration * btVector3(cameraVectSteer.X, cameraVectSteer.Y, cameraVectSteer.Z));
    }
}
