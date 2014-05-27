#ifndef FISICA_H
#define FISICA_H

#include "btBulletDynamicsCommon.h"

class Fisica {
    public:
        Fisica();
        void init();
        void remover();

    private:
        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;
};

#endif
