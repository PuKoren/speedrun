#include "Bullet.h"

Bullet::Bullet(){
    BroadPhase = new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000));
    CollisionConfiguration = new btDefaultCollisionConfiguration();
    Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
    Solver = new btSequentialImpulseConstraintSolver();
    World = new btDiscreteDynamicsWorld(Dispatcher, BroadPhase, Solver, CollisionConfiguration);
}

Bullet::~Bullet(){
    ClearObjects();
    delete BroadPhase;
    delete CollisionConfiguration;
    delete Dispatcher;
    delete Solver;
    delete World;
}

void Bullet::UpdatePhysics(u32 TDeltaTime) {
    World->stepSimulation(TDeltaTime * 0.001f, 60);

    btRigidBody *TObject;
    // Relay the object's orientation to irrlicht
    for(core::list<btRigidBody *>::Iterator it = Objects.begin(); it != Objects.end(); ++it) {

        if(!(*it)->isKinematicObject()){
            //UpdateRender(*Iterator);
            scene::ISceneNode *Node = static_cast<UserPointer *>((*it)->getUserPointer())->node;
            TObject = *it;

            // Set position
            btVector3 Point = TObject->getCenterOfMassPosition();
            Node->setPosition(core::vector3df((f32)Point[0], (f32)Point[1], (f32)Point[2]));

            // Set rotation
            btVector3 EulerRotation;
            QuaternionToEuler(TObject->getOrientation(), EulerRotation);
            Node->setRotation(core::vector3df(EulerRotation[0], EulerRotation[1], EulerRotation[2]));
        }
    }


    int numManifolds = World->getDispatcher()->getNumManifolds();
    for (int i=0;i<numManifolds;i++)
    {
        btPersistentManifold* contactManifold =  World->getDispatcher()->getManifoldByIndexInternal(i);
        const btCollisionObject* obA = contactManifold->getBody0();
        const btCollisionObject* obB = contactManifold->getBody1();

        int numContacts = contactManifold->getNumContacts();
        for (int j=0;j<numContacts;j++)
        {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);
            if (pt.getDistance()<0.f)
            {
                IBulletObject* objA = ((UserPointer*)obA->getUserPointer())->bulletObject;
                IBulletObject* objB = ((UserPointer*)obB->getUserPointer())->bulletObject;

                if (objA) {
                    objA->collisionCallback(pt.m_normalWorldOnB);
                }
                if (objB) {
                    objB->collisionCallback(pt.m_normalWorldOnB);
                }
            }
        }
    }
}

// Converts a quaternion to an euler angle
void Bullet::QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler) {
    btScalar W = TQuat.getW();
    btScalar X = TQuat.getX();
    btScalar Y = TQuat.getY();
    btScalar Z = TQuat.getZ();
    float WSquared = W * W;
    float XSquared = X * X;
    float YSquared = Y * Y;
    float ZSquared = Z * Z;

    TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
    TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
    TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
    TEuler *= core::RADTODEG;
}

btRigidBody* Bullet::AddBox(scene::ISceneNode* node, double mass, bool isKinematic){
    return Add(node, mass, GetBoxShape(node), isKinematic);
}

btRigidBody* Bullet::AddCapsule(scene::ISceneNode* node, double mass, bool isKinematic){
    return Add(node, mass, GetCapsuleShape(node), isKinematic);
}

btRigidBody* Bullet::AddSphere(scene::ISceneNode* node, float radius, double mass, bool isKinematic){
    return Add(node, mass, GetSphereShape(radius), isKinematic);
}

btRigidBody* Bullet::Add(scene::ISceneNode* node, double mass, btCollisionShape *Shape, bool isKinematic){
    if (isKinematic) {
        mass = 0.f;
    }

    btTransform Transform;
    Transform.setIdentity();
    core::vector3df pos = node->getPosition();
    Transform.setOrigin(btVector3(pos.X, pos.Y, pos.Z));

    btDefaultMotionState *MotionState = new btDefaultMotionState(Transform);

    btVector3 LocalInertia;
    Shape->calculateLocalInertia(mass, LocalInertia);

    btRigidBody *RigidBody = new btRigidBody(mass, MotionState, Shape, LocalInertia);
    RigidBody->applyTorque(btVector3(0., 0., 0.));

    if(isKinematic){
      RigidBody->setCollisionFlags(RigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
      RigidBody->setActivationState(DISABLE_DEACTIVATION);
    }

    UserPointer* userPointer = new UserPointer();
    userPointer->node = node;
    RigidBody->setUserPointer((void *)(userPointer));

    World->addRigidBody(RigidBody);
    Objects.push_back(RigidBody);
    return RigidBody;
}

btCollisionShape* Bullet::GetSphereShape(float radius){
  return new btSphereShape(radius);
}

btCollisionShape* Bullet::GetBoxShape(scene::ISceneNode* node){
    core::vector3df scale = node->getTransformedBoundingBox().getExtent();

    btVector3 HalfExtents(scale.X / 2, scale.Y / 2, scale.Z / 2);
    return new btBoxShape(HalfExtents);
}

btCollisionShape* Bullet::GetCapsuleShape(scene::ISceneNode* node){
    core::vector3df scale = node->getTransformedBoundingBox().getExtent();
    return new btCapsuleShape(scale.X / 2, scale.Y / 2);
}

void Bullet::ClearObjects() {
    for(core::list<btRigidBody *>::Iterator Iterator = Objects.begin(); Iterator != Objects.end(); ++Iterator) {
        btRigidBody *Object = *Iterator;

        // Delete irrlicht node
        scene::ISceneNode *Node = static_cast<UserPointer *>(Object->getUserPointer())->node;
        Node->remove();

        // Remove the object from the world
        World->removeRigidBody(Object);

        // Free memory
        delete Object->getMotionState();
        delete Object->getCollisionShape();
        delete Object;
        delete Object->getUserPointer();
    }

    Objects.clear();
}
