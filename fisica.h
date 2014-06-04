#ifndef FISICA_H
#define FISICA_H

#include <btBulletDynamicsCommon.h>
#include "braco.h"

class Fisica {
    public:
        Fisica();
        void init();
        void atualizar(float dt, Braco* b);
        void remover();

        btRigidBody* groundRigidBody;
        btRigidBody* fallRigidBody;
        btRigidBody* fallRigidBody2;
        btRigidBody* fallRigidBody3;
        btRigidBody* garraLRigidBody;
        btRigidBody* garraRRigidBody;
        btRigidBody* ballRigidBody;

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
        btDefaultMotionState* ballMotionState;
        btDefaultMotionState* garraLMotionState;
        btDefaultMotionState* garraRMotionState;

        btCollisionShape* groundShape;
        btCollisionShape* fallShape;
        btCollisionShape* garraShape;
        btCollisionShape* ballShape;
};

#endif
