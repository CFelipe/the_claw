#ifndef FISICA_H
#define FISICA_H

#include <BulletCollision/CollisionDispatch/btGhostObject.h>
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
        btRigidBody* topoRigidBody;
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
        btDefaultMotionState* topoMotionState;
        btDefaultMotionState* garraLMotionState;
        btDefaultMotionState* garraRMotionState;

        btCollisionShape* groundShape;
        btCollisionShape* fallShape;
        btCollisionShape* garraShape;
        btCollisionShape* topoShape;
        btCollisionShape* ballShape;

        btGhostPairCallback* ghostCall;
        btGhostObject* garraLGhost;
        btGhostObject* garraRGhost;

        btVector3* consVector();

        bool ballEsq, ballDir;

};

#endif
