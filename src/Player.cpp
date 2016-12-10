#include "Player.h"

const float MAX_SPEED = 100.f;
const float JUMP_SPEED = 6.0f;
const float ACCELERATION_SPEED = 0.12f;
const float JUMPDOWN_SPEED = 0.06f;
const float COLLISION_COOLDOWN = 200.f;
const float JUMP_COOLDOWN = COLLISION_COOLDOWN;

Player::Player(scene::ISceneManager *p_smgr, Bullet *p_bullet, irr::IEventReceiver* p_event){
    m_smgr = p_smgr;
    m_bullet = p_bullet;
    m_event = (EventReceiver*)p_event;

    m_node = m_smgr->addCubeSceneNode(1.f, 0, -1, core::vector3df(0.f, 0.f, -20.f), core::vector3df(0.f, 0.f, 0.f), core::vector3df(1.f, 3.f, 1.f));

    this->camera = m_smgr->addCameraSceneNodeFPS(0, 100.f, 0.f);

    m_rbody = m_bullet->AddCapsule(m_node, 10.f);
    m_rbody->setLinearFactor(btVector3(1,1,1));
    m_rbody->setSleepingThresholds(0.f, 0.f);
    m_rbody->setAngularFactor(btVector3(0,0,0));
    m_rbody->setFriction(0.8f);

    UserPointer* userPointer = new UserPointer();
    userPointer->node = m_node;
    userPointer->bulletObject = this;

    m_rbody->setUserPointer(userPointer);

    m_layer = PLAYER;
}


Player::~Player(){

}

void Player::drawAll(){

}

void Player::collisionCallback(btVector3& p_obj){
    this->lastCollision = 0.f;
    this->lastCollisionNormal = p_obj;
}

bool Player::isColliding() {
    return this->lastCollision < COLLISION_COOLDOWN;
}

bool Player::canJump() {
    return this->isColliding() && this->lastJump > JUMP_COOLDOWN;
}

void Player::jump(float force) {
    m_rbody->applyCentralImpulse(btVector3(this->lastCollisionNormal.x()/2 * force, force, this->lastCollisionNormal.z()/2 * force));
    this->lastCollision = COLLISION_COOLDOWN;
    this->lastJump = 0.f;
}

core::vector3df Player::getCameraDirection() {
    core::vector3df target = this->camera->getTarget();
    core::vector3df position = this->camera->getPosition();
    target.Y = 0.f;
    position.Y = 0.f;

    return (target - position).normalize();
}

bool previousFrameJumpKeyDown = false;

void Player::update(u32 DeltaTime, GameStates::GAME_STATE &gs){
    btVector3 velocity = m_rbody->getLinearVelocity();
    btScalar speed = velocity.length();
    if(speed > MAX_SPEED) {
        velocity *= MAX_SPEED/speed;
        m_rbody->setLinearVelocity(velocity);
    }

    if(!previousFrameJumpKeyDown && m_event->IsKeyDown(KEY_SPACE) && this->canJump()){
        this->jump(JUMP_SPEED * DeltaTime);
    }

    previousFrameJumpKeyDown = m_event->IsKeyDown(KEY_SPACE);

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

    this->lastCollision += DeltaTime;
    this->lastJump += DeltaTime;

    // do it at the end of the update so body is moved before camera
    // otherwise with very high speed the capsule will be in another location
    core::vector3df cameraPosition = m_node->getPosition();
    this->camera->setPosition(cameraPosition);
}
