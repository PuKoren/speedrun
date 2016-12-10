#pragma once
#include <irrlicht/irrlicht.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "IBulletObject.h"

using namespace irr;

/**
 * @brief The Bullet class
 * Wrapper between Bullet and Irrlicht nodes. The Bullet class is used to
 * instanciate objects in the Bullet world, make the ticks, and apply
 * modifications in the 3D world of Irrlicht
 */
class Bullet{
public:
    Bullet();
    ~Bullet();
    void UpdatePhysics(u32 TDeltaTime);
    btRigidBody* AddBox(scene::ISceneNode* node, double mass, bool isKinematic = false);
    btRigidBody* AddCapsule(scene::ISceneNode* node, double mass, bool isKinematic = false);
    btRigidBody* AddSphere(scene::ISceneNode* node, float radius, double mass, bool isKinematic = false);
private:
    btRigidBody* Add(scene::ISceneNode* node, double mass, btCollisionShape *Shape, bool isKinematic);
    btCollisionShape* GetSphereShape(float radius);
    btCollisionShape* GetBoxShape(scene::ISceneNode* node);
    btCollisionShape* GetCapsuleShape(scene::ISceneNode* node);
    void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler);
    void ClearObjects();
    btDiscreteDynamicsWorld *World;
    core::list<btRigidBody *> Objects;
    btBroadphaseInterface *BroadPhase;
    btDefaultCollisionConfiguration *CollisionConfiguration;
    btCollisionDispatcher *Dispatcher;
    btSequentialImpulseConstraintSolver *Solver;
};

/**
 * @brief The UserPointer struct
 * Contains a reference to an Irrlicht node and a bullet object
 */
struct UserPointer {
    scene::ISceneNode* node;
    IBulletObject* bulletObject;
};
