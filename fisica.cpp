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
    garraShape = new btBoxShape(btVector3(0.1f, 0.5f, 0.4f));
    ballShape = new btSphereShape(btScalar(0.6));

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
    btScalar mass = 30.0f;
    btVector3 fallInertia;
    fallShape->calculateLocalInertia(mass,fallInertia);
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

    garraLMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                            btVector3(0,0.5f,0)));

    garraRMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                            btVector3(0,0.5f,0)));


    btRigidBody::btRigidBodyConstructionInfo garraLRigidBodyCI(mass,garraLMotionState,garraShape,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo garraRRigidBodyCI(mass,garraRMotionState,garraShape,fallInertia);

    // por que não?
    garraLRigidBodyCI.m_friction = 10.0f;
    garraRRigidBodyCI.m_friction = 10.0f;

    garraLRigidBody = new btRigidBody(garraLRigidBodyCI);
    garraRRigidBody = new btRigidBody(garraRRigidBodyCI);

    garraLRigidBody->setCollisionFlags(garraLRigidBody->getCollisionFlags() |
                                      btCollisionObject::CF_KINEMATIC_OBJECT);
    garraRRigidBody->setCollisionFlags(garraRRigidBody->getCollisionFlags() |
                                       btCollisionObject::CF_KINEMATIC_OBJECT);

    garraLRigidBody->setActivationState(DISABLE_DEACTIVATION);
    garraRRigidBody->setActivationState(DISABLE_DEACTIVATION);


    dynamicsWorld->addRigidBody(garraLRigidBody);
    dynamicsWorld->addRigidBody(garraRRigidBody);

    // ----------

    ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                            btVector3(5,10.5f,0)));


    btVector3 ballInertia;
    ballShape->calculateLocalInertia(30.0f, ballInertia);
    btRigidBody::btRigidBodyConstructionInfo ballRigidBodyCI(30.0f, ballMotionState,ballShape,ballInertia);
    ballRigidBodyCI.m_friction = 1.7f;
    ballRigidBodyCI.m_restitution = 0.7f;
    ballRigidBody = new btRigidBody(ballRigidBodyCI);
    ballRigidBody->setDamping(0.3, 0.5f);

    dynamicsWorld->addRigidBody(ballRigidBody);
}

void Fisica::atualizar(float dt, Braco* braco) {
    //std::cout << dynamicsWorld->getNumCollisionObjects() << std::endl;

    btTransform garraLTrans;
    btTransform garraRTrans;

    garraLTrans.setFromOpenGLMatrix(braco->esq);
    garraLRigidBody->getMotionState()->setWorldTransform(garraLTrans);

    garraRTrans.setFromOpenGLMatrix(braco->dir);
    garraRRigidBody->getMotionState()->setWorldTransform(garraRTrans);

    dynamicsWorld->stepSimulation(dt, 10);
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
