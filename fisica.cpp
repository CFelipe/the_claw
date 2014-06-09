#include <iostream>
#include <math.h>
#include "fisica.h"

Fisica::Fisica() {
    broadphase = new btDbvtBroadphase();

    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher = new btCollisionDispatcher(collisionConfiguration);

    solver = new btSequentialImpulseConstraintSolver;

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,
                                                broadphase,
                                                solver,
                                                collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0,-10,0));

    groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
    fallShape = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
    topoShape = new btBoxShape(btVector3(1.2f, 0.2f, 0.4f));
    garraShape = new btBoxShape(btVector3(0.1f, 0.5f, 0.4f));
    ballShape = new btSphereShape(btScalar(0.6));

    btGhostPairCallback* ghostCall = new btGhostPairCallback();
    dynamicsWorld->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(ghostCall);

    // ----------

    groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                             btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    groundRigidBodyCI.m_restitution = 0.5f;
    groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);

    // ----------

    fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0.1f,0,1),
                                                           btVector3(7, 0.5f, -1)));
    btScalar mass = 1.0f;
    btScalar mass2 = 0.5f;
    btVector3 fallInertia;
    btVector3 garraInertia;
    fallShape->calculateLocalInertia(mass,fallInertia);
    garraShape->calculateLocalInertia(mass2,garraInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,
                                                             fallMotionState,
                                                             fallShape,
                                                             fallInertia);

    fallRigidBodyCI.m_friction = 1.7f;
    fallRigidBody = new btRigidBody(fallRigidBodyCI);
    fallRigidBody->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
    dynamicsWorld->addRigidBody(fallRigidBody);

    // ----------

    fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0.5f,0,1),
                                                            btVector3(6,0.5f,2)));

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI2(mass,fallMotionState2,fallShape,fallInertia);
    fallRigidBodyCI2.m_friction = 1.7f;
    fallRigidBody2 = new btRigidBody(fallRigidBodyCI2);

    dynamicsWorld->addRigidBody(fallRigidBody2);

    // ----------

    fallMotionState3 = new btDefaultMotionState(btTransform(btQuaternion(0.2,0.8f,0,1),
                                                            btVector3(4,9.5f,6)));

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI3(mass,fallMotionState3,fallShape,fallInertia);
    fallRigidBodyCI3.m_friction = 1.7f;
    fallRigidBodyCI3.m_restitution = 0.3f;
    fallRigidBody3 = new btRigidBody(fallRigidBodyCI3);

    dynamicsWorld->addRigidBody(fallRigidBody3);

    // ----------

    topoMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                           btVector3(0,0.5f,0)));

    garraLMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                            btVector3(0,0.5f,0)));

    garraLGhost = new btGhostObject();
    garraLGhost->setCollisionShape(garraShape);
    garraLGhost->setCollisionFlags(garraLGhost->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    dynamicsWorld->addCollisionObject(garraLGhost);

    garraRMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                            btVector3(0,0.5f,0)));

    garraRGhost = new btGhostObject();
    garraRGhost->setCollisionShape(garraShape);
    garraRGhost->setCollisionFlags(garraRGhost->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
    dynamicsWorld->addCollisionObject(garraRGhost);


    btRigidBody::btRigidBodyConstructionInfo garraLRigidBodyCI(mass2,garraLMotionState,garraShape,garraInertia);
    btRigidBody::btRigidBodyConstructionInfo garraRRigidBodyCI(mass2,garraRMotionState,garraShape,garraInertia);
    btRigidBody::btRigidBodyConstructionInfo topoRigidBodyCI(mass,topoMotionState,topoShape,garraInertia);

    garraLRigidBodyCI.m_friction = 10.0f;
    garraRRigidBodyCI.m_friction = 10.0f;

    garraLRigidBody = new btRigidBody(garraLRigidBodyCI);
    garraRRigidBody = new btRigidBody(garraRRigidBodyCI);
    topoRigidBody = new btRigidBody(topoRigidBodyCI);

    garraLRigidBody->setCollisionFlags(garraLRigidBody->getCollisionFlags() |
                                      btCollisionObject::CF_KINEMATIC_OBJECT);
    garraRRigidBody->setCollisionFlags(garraRRigidBody->getCollisionFlags() |
                                       btCollisionObject::CF_KINEMATIC_OBJECT);
    topoRigidBody->setCollisionFlags(garraRRigidBody->getCollisionFlags() |
                                       btCollisionObject::CF_KINEMATIC_OBJECT);

    garraLRigidBody->setActivationState(DISABLE_DEACTIVATION);
    garraRRigidBody->setActivationState(DISABLE_DEACTIVATION);
    topoRigidBody->setActivationState(DISABLE_DEACTIVATION);

    dynamicsWorld->addRigidBody(garraLRigidBody);
    dynamicsWorld->addRigidBody(garraRRigidBody);
    dynamicsWorld->addRigidBody(topoRigidBody);

    // ----------

    ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                            btVector3(5,10.5f,0)));


    btVector3 ballInertia;
    ballShape->calculateLocalInertia(0.5f, ballInertia);
    btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(0.5f, ballMotionState,ballShape,ballInertia);
    ballRigidBodyCI.m_friction = 1.7f;
    ballRigidBodyCI.m_restitution = 0.7f;
    ballRigidBody = new btRigidBody(ballRigidBodyCI);
    ballRigidBody->setDamping(0.3, 0.5f);

    dynamicsWorld->addRigidBody(ballRigidBody);

    ballEsq = false;
    ballDir = false;
}

void Fisica::atualizar(float dt, Braco* braco) {
    btTransform garraLTrans;
    btTransform garraRTrans;
    btTransform topoTrans;

    garraLTrans.setFromOpenGLMatrix(braco->esq);
    garraLRigidBody->getMotionState()->setWorldTransform(garraLTrans);
    garraLGhost->setWorldTransform(garraLTrans);

    garraRTrans.setFromOpenGLMatrix(braco->dir);
    garraRRigidBody->getMotionState()->setWorldTransform(garraRTrans);
    garraRGhost->setWorldTransform(garraRTrans);

    topoTrans.setFromOpenGLMatrix(braco->topo);
    topoRigidBody->getMotionState()->setWorldTransform(topoTrans);

    dynamicsWorld->stepSimulation(dt, 10);

    // -----------------------

    /*
    int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();

    for (int i=0;i<numManifolds;i++) {
        btPersistentManifold* contactManifold =  dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
        const btCollisionObject* obA = contactManifold->getBody0();
        const btCollisionObject* obB = contactManifold->getBody1();

        int numContacts = contactManifold->getNumContacts();

        for (int j=0;j<numContacts;j++) {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);

            if (pt.getDistance()<0.f) {
                if(obA == ballRigidBody) {
                    //std::cout << "bola bateu!" << std::endl;
                }

                const btVector3& ptA = pt.getPositionWorldOnA();
                const btVector3& ptB = pt.getPositionWorldOnB();
                const btVector3& normalOnB = pt.m_normalWorldOnB;
            }
        }
    }
    */

    ballEsq = false;
    ballDir = false;

    for(int i = 0; i < garraRGhost->getNumOverlappingObjects(); i++) {
        btRigidBody *rigidBody = static_cast<btRigidBody *>(garraRGhost->getOverlappingObject(i));
        if (rigidBody == fallRigidBody) {
            ballDir = true;
        }
        if (rigidBody == fallRigidBody2) {
        }
        if (rigidBody == fallRigidBody3) {
        }
        if (rigidBody == ballRigidBody) {
        }
    }

    for(int i = 0; i < garraLGhost->getNumOverlappingObjects(); i++) {
        btRigidBody *rigidBody = static_cast<btRigidBody *>(garraLGhost->getOverlappingObject(i));
        if (rigidBody == fallRigidBody) {
            ballEsq = true;
        }
        if (rigidBody == fallRigidBody2) {
        }
        if (rigidBody == fallRigidBody3) {
        }
        if (rigidBody == ballRigidBody) {
        }
    }

    if(ballEsq && ballDir) {
        //braco->garraLock = true;
        //fallRigidBody->setWorldTransform(topoTrans);
        fallRigidBody->setGravity(btVector3(0, 0, 0));
    } else {
        //braco->garraLock = false;
        fallRigidBody->setGravity(btVector3(0, -10, 0));
    }
}

void Fisica::remover() {
    dynamicsWorld->removeRigidBody(fallRigidBody);
    delete fallRigidBody->getMotionState();
    delete fallRigidBody;

    dynamicsWorld->removeRigidBody(fallRigidBody2);
    delete fallRigidBody2->getMotionState();
    delete fallRigidBody2;

    dynamicsWorld->removeRigidBody(fallRigidBody3);
    delete fallRigidBody3->getMotionState();
    delete fallRigidBody3;

    dynamicsWorld->removeRigidBody(groundRigidBody);

    delete fallShape;

    delete groundShape;

    delete dynamicsWorld;
    delete solver;
    delete collisionConfiguration;
    delete dispatcher;
    delete broadphase;
}
