#include "Player.h"


float mMaxSpeed = 10.f;
const float JUMP_SPEED = 1.f;
const float ACCELERATION_SPEED = 0.2f;
const float JUMPDOWN_SPEED = 0.1;
scene::ICameraSceneNode* camera;

Player::Player(scene::ISceneManager *p_smgr, Bullet *p_bullet, irr::IEventReceiver* p_event){
    m_smgr = p_smgr;
    m_bullet = p_bullet;
    m_event = (EventReceiver*)p_event;

    m_node = m_smgr->addCubeSceneNode(1.f, 0, -1, core::vector3df(0.f, 0.f, -20.f), core::vector3df(0.f, 0.f, 0.f), core::vector3df(1.f, 3.f, 1.f));

    camera = m_smgr->addCameraSceneNodeFPS(0, 100.f, 0.f);

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

    camera->setPosition(m_node->getPosition());

    core::vector3df target = camera->getTarget();
    core::vector3df position = camera->getPosition();
    target.Y = 0.f;
    position.Y = 0.f;

    core::vector3df cameraVectForward = (target - position).normalize();
    core::vector3df cameraVectSteer = cameraVectForward;

    core::matrix4 m;
    m.setRotationDegrees(core::vector3df(0.f, 90.f, 0.f));
    m.rotateVect(cameraVectSteer);

    if(m_event->IsKeyDown(KEY_SPACE)){
        m_rbody->applyCentralImpulse(btVector3(0,JUMP_SPEED,0));
    }

    if(m_event->IsKeyDown(KEY_LCONTROL)){
        m_rbody->applyCentralImpulse(btVector3(0,-JUMPDOWN_SPEED,0));
    }

    if(m_event->IsKeyDown(KEY_KEY_W)){
        m_rbody->applyCentralImpulse(ACCELERATION_SPEED * btVector3(cameraVectForward.X, cameraVectForward.Y, cameraVectForward.Z));
    }

    if(m_event->IsKeyDown(KEY_KEY_S)){
        m_rbody->applyCentralImpulse(-ACCELERATION_SPEED * btVector3(cameraVectForward.X, cameraVectForward.Y, cameraVectForward.Z));
    }

    //steer left
    if(m_event->IsKeyDown(KEY_KEY_A)){
        m_rbody->applyCentralImpulse(-ACCELERATION_SPEED * btVector3(cameraVectSteer.X, cameraVectSteer.Y, cameraVectSteer.Z));
    }

    //steer right
    if(m_event->IsKeyDown(KEY_KEY_D)){
        m_rbody->applyCentralImpulse(ACCELERATION_SPEED * btVector3(cameraVectSteer.X, cameraVectSteer.Y, cameraVectSteer.Z));
    }
}
