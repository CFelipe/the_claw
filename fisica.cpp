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

    groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),
                                                             btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo
            groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);


    fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0.1f,0,1),
                                                           btVector3(7, 0.5f, -1)));
    btScalar mass = 1;
    btVector3 fallInertia(0,0,0);
    fallShape->calculateLocalInertia(mass,fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass,
                                                             fallMotionState,
                                                             fallShape,
                                                             fallInertia);

    fallRigidBodyCI.m_friction = 0.7f;
    fallRigidBody = new btRigidBody(fallRigidBodyCI);
    fallRigidBody->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
    dynamicsWorld->addRigidBody(fallRigidBody);

    fallMotionState2 = new btDefaultMotionState(btTransform(btQuaternion(0,0.5f,0,1),
                                                            btVector3(6,0.5f,2)));

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI2(mass,fallMotionState2,fallShape,fallInertia);
    fallRigidBodyCI2.m_friction = 0.7f;
    fallRigidBody2 = new btRigidBody(fallRigidBodyCI2);

    dynamicsWorld->addRigidBody(fallRigidBody2);

    fallMotionState3 = new btDefaultMotionState(btTransform(btQuaternion(0,0.8f,0,1),
                                                            btVector3(6,0.5f,5)));

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI3(mass,fallMotionState3,fallShape,fallInertia);
    fallRigidBodyCI3.m_friction = 0.7f;
    fallRigidBody3 = new btRigidBody(fallRigidBodyCI3);

    dynamicsWorld->addRigidBody(fallRigidBody3);
}

void Fisica::atualizar(float dt) {
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