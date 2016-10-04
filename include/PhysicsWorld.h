#ifndef PHYSICSWORLD_H__
#define PHYSICSWORLD_H__

//----------------------------------------------------------------------------------------------------------------------
/// @brief this is a minimal Facade wrapper for the code here
//----------------------------------------------------------------------------------------------------------------------

#include <btBulletDynamicsCommon.h>
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Obj.h>
#include <memory>
#include <vector>
#include <unordered_map>

#include "PhysicsMaterial.h"

class PhysicsWorld
{
    static PhysicsWorld *p_instance;
public :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor, this should really be a singleton as we have quite a few static members and only one world
    //----------------------------------------------------------------------------------------------------------------------
    PhysicsWorld();
    //----------------------------------------------------------------------------------------------------------------------
    // @brief dtor
    //----------------------------------------------------------------------------------------------------------------------
    ~PhysicsWorld();


    /*!
     * \brief  instance of World object.
     * \return pointer to singleton World object.
     */
    static PhysicsWorld *instance();

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief reset the simulation (remove all geo etc)
    //----------------------------------------------------------------------------------------------------------------------
    void reset();

    inline void setGravity(float _x, float _y, float _z)
    {
      m_dynamicsWorld->setGravity(btVector3(_x,_y,_z));
    }
    inline void setGravity(ngl::Vec3 _g)
    {
      m_dynamicsWorld->setGravity(btVector3(_g.m_x,_g.m_y,_g.m_z));
    }

    btRigidBody* addGroundPlane(const ngl::Vec3 &_pos,const ngl::Vec3 &_g);
    btRigidBody* addSphere(const ngl::Vec3 &_pos, float _radius, ngl::Real _mass);
    btRigidBody* addBox(const ngl::Vec3 &_pos, float _width, float _height, float _depth, ngl::Real _mass);

    void step(float _time, float _step);

    inline unsigned int getNumCollisionObjects()const
    {
      return m_dynamicsWorld->getNumCollisionObjects();
    }

    PhysicsMaterial* getMaterial(std::string _material);

private :
    btBroadphaseInterface*	m_broadphase;

    std::unique_ptr<btDefaultCollisionConfiguration>        m_collisionConfiguration;
    std::unique_ptr<btCollisionDispatcher>                  m_dispatcher;
    std::unique_ptr<btBroadphaseInterface>                  m_overlappingPairCache ;
    std::unique_ptr<btSequentialImpulseConstraintSolver>    m_solver;
    std::unique_ptr<btDiscreteDynamicsWorld>                m_dynamicsWorld;

    std::unordered_map <std::string,PhysicsMaterial>        m_materials;
};

#endif

