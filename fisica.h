#ifndef FISICA_H
#define FISICA_H

#include <btBulletDynamicsCommon.h>

class Fisica {
    public:
        Fisica();
        void init();
        void atualizar(float dt);
        void remover();

        btRigidBody* groundRigidBody;
        btRigidBody* fallRigidBody;
        btRigidBody* fallRigidBody2;
        btRigidBody* fallRigidBody3;

    private:
        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;

        btDefaultMotionState* groundMotionState;
        btDefaultMotionState* fallMotionState;
        btDefaultMotionState* fallMotionState2;
        btDefaultMotionState* fallMotionState3;

        btCollisionShape* groundShape;
        btCollisionShape* fallShape;
        btCollisionShape* fallShape2;
        btCollisionShape* fallShape3;
};

#endif
