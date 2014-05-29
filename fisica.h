#ifndef FISICA_H
#define FISICA_H

#include <btBulletDynamicsCommon.h>

class Fisica {
    public:
        Fisica();
        void init();
        void atualizar(float dt);
        void remover();

    private:
        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;

        btDefaultMotionState* groundMotionState;
        btDefaultMotionState* fallMotionState;
        btCollisionShape* groundShape;
        btCollisionShape* fallShape;

        btRigidBody* groundRigidBody;
        btRigidBody* fallRigidBody;
};

#endif
