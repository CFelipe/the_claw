#ifndef CORPO_H
#define CORPO_H

#include <btBulletDynamicsCommon.h>

class Corpo {
    public:
        Corpo(friccao);
        btCollisionShape* formaColisao;
        btDefaultMotionState* estado;
        btRigidBody* corpoRigido;
};

#endif
