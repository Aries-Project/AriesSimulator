#include "PhysicsWorld.h"
#include "CollisionShape.h"
#include <ngl/Obj.h>
#include <ngl/Quaternion.h>
#include <ngl/Util.h>
#include <BulletCollision/CollisionDispatch/btSimulationIslandManager.h>

PhysicsWorld *PhysicsWorld::p_instance = 0;

PhysicsWorld* PhysicsWorld::instance()
{
    if (!p_instance)
        p_instance = new PhysicsWorld;
    return p_instance;
}

PhysicsWorld::PhysicsWorld()
{
//    int maxNumOutstandingTasks = 4;

//    PosixThreadSupport::ThreadConstructionInfo constructionInfo("collision",
//                                processCollisionTask,
//                                createCollisionLocalStoreMemory,
//                                maxNumOutstandingTasks);
//    m_threadSupportCollision = new PosixThreadSupport(constructionInfo);


//    m_threadSupportSolver = createSolverThreadSupport(maxNumOutstandingTasks);
//    m_solver = new btParallelConstraintSolver(m_threadSupportSolver);

//    btDefaultCollisionConstructionInfo cci;

//    cci.m_defaultMaxPersistentManifoldPoolSize = 32768;
//    m_collisionConfiguration = new btDefaultCollisionConfiguration(cci);

//    //this solver requires the contacts to be in a contiguous pool, so avoid dynamic allocation
//    m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);

//    m_dispatcher->setDispatcherFlags(btCollisionDispatcher::CD_DISABLE_CONTACTPOOL_DYNAMIC_ALLOCATION);


/*

    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    m_collisionConfiguration = new btDefaultCollisionConfiguration();


    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        btVector3 worldAabbMin(-10,-10,-10);
        btVector3 worldAabbMax(100,100,100);

    const int maxProxies = 32766;


    m_broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);


    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_broadphase,m_solver,m_collisionConfiguration);

    m_dynamicsWorld->getSolverInfo().m_solverMode = SOLVER_USE_WARMSTARTING + SOLVER_SIMD;

    m_dynamicsWorld->getSimulationIslandManager()->setSplitIslands(true);
    m_dynamicsWorld->getSolverInfo().m_numIterations = 4;

    m_dynamicsWorld->getDispatchInfo().m_enableSPU = true;
    m_dynamicsWorld->getDispatchInfo().m_useEpa = false;
*/
    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    m_collisionConfiguration.reset( new btDefaultCollisionConfiguration());

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    m_dispatcher.reset(new btCollisionDispatcher(m_collisionConfiguration.get()));

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    m_overlappingPairCache.reset(new btDbvtBroadphase());

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    m_solver.reset(new btSequentialImpulseConstraintSolver());

    m_dynamicsWorld.reset(new btDiscreteDynamicsWorld(m_dispatcher.get(),
        m_overlappingPairCache.get(),
        m_solver.get(),
        m_collisionConfiguration.get()));
}

PhysicsMaterial* PhysicsWorld::getMaterial(std::string _material)
{
    return & m_materials[_material];
}

btRigidBody * PhysicsWorld::addGroundPlane(const ngl::Vec3 &_pos, const ngl::Vec3 &_size)
{
    btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0,1,0),_pos.m_y);

    btTransform groundTransform;
    groundTransform.setIdentity();
    btScalar mass(0.0f);


    btVector3 localInertia(0,0,0);

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
    rbInfo.m_rollingFriction=0.1f;
    rbInfo.m_friction = 0.5f;
    rbInfo.m_restitution = 1.0f;
    btRigidBody* body = new btRigidBody(rbInfo);
    //add the body to the dynamics world
    m_dynamicsWorld->addRigidBody(body);

    return body;
}

PhysicsWorld::~PhysicsWorld()
{
}

btRigidBody *PhysicsWorld::addSphere(const ngl::Vec3 &_pos, float _radius, ngl::Real _mass)
{
    //create a dynamic rigidbody

    //btCollisionShape* colShape = CollisionShape::instance()->getShape(_shapeName);
    btCollisionShape* colShape = new btSphereShape(btScalar(_radius));

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    btScalar	mass(_mass);

    startTransform.setOrigin(btVector3(_pos.m_x,_pos.m_y,_pos.m_z));
    btVector3 localInertia(0.0f,0.0f,0.0f);
    colShape->calculateLocalInertia(mass,localInertia);

    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
    rbInfo.m_restitution = 0.5f;
    rbInfo.m_friction = 0.1f;
    rbInfo.m_rollingFriction=0.1f;
    rbInfo.m_additionalAngularDampingFactor=0.1;
    rbInfo.m_additionalDamping=true;

    btRigidBody* body = new btRigidBody(rbInfo);
    //body->applyCentralImpulse(btVector3(_dir.m_x, _dir.m_y, _dir.m_z));
    body->setLinearVelocity(btVector3(0.0f,0.0f,0.0f));
    m_dynamicsWorld->addRigidBody(body);

    return body;
}


btRigidBody *PhysicsWorld::addBox(const ngl::Vec3 &_pos, float _width, float _height, float _depth, ngl::Real _mass)
{

    //btCollisionShape* colShape = CollisionShape::instance()->getShape(_shapeName);
    btCollisionShape* colShape = new btBoxShape(btVector3(_width/2.0,_height/2.0,_depth/2.0));

    /// Create Dynamic Objects
    btTransform startTransform;
    startTransform.setIdentity();

    btScalar	mass(1.0f);


    btVector3 localInertia(0,0,0);
    colShape->calculateLocalInertia(mass,localInertia);
    startTransform.setOrigin(btVector3(_pos.m_x,_pos.m_y,_pos.m_z));
    //startTransform.setRotation(btQuaternion(btVector3(_axis.m_x,_axis.m_y,_axis.m_z),ngl::radians(_angle)));
    //using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
    btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
    rbInfo.m_restitution = 0.5f;
    rbInfo.m_friction = 0.1f;
    rbInfo.m_rollingFriction=0.1f;
    rbInfo.m_additionalAngularDampingFactor=0.1;
    rbInfo.m_additionalDamping=true;

    btRigidBody* body = new btRigidBody(rbInfo);

    body->setActivationState(DISABLE_DEACTIVATION);
    m_dynamicsWorld->addRigidBody(body);

    return body;
}

void PhysicsWorld::step(float _time, float _step)
{
    m_dynamicsWorld->stepSimulation(_time,_step);
}

void PhysicsWorld::reset()
{
    // start at 1 to leave the ground plane
//    for(unsigned int i=1; i<m_bodies.size(); ++i)
//    {
//        m_dynamicsWorld->removeRigidBody(m_bodies[i].body);
//    }
//    m_bodies.erase(m_bodies.begin()+1,m_bodies.end());

}

