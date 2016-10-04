#include "World.h"
#include "PhysicsWorld.h"
#include "CollisionShape.h"

#include <QtDebug>

#define to_ngl_vec3(_f3) ngl::Vec3(_f3[0], _f3[1], _f3[2])

World *World::p_instance = 0;

World* getWorld()
{
    return World::instance();
}

World::World()
{
    m_physics = PhysicsWorld::instance();

    CollisionShape *shapes=CollisionShape::instance();

    shapes->addBox("box",2.0f,2.0f,2.0f);
    shapes->addSphere("sphere",1.0f);
}

std::vector<WorldObject *> &World::getObjects()
{
    return m_objects;
}

World::~World()
{
    qDebug("World is destroyed.");
}

World* World::instance()
{
    if (!p_instance)
        p_instance = new World;
    return p_instance;
}

void World::setGravity(const float gravity[])
{
    m_physics->setGravity(gravity[0], gravity[1], gravity[2]);
}

void World::addGroundPlane(const float pos[], const float g[])
{
    auto body = m_physics->addGroundPlane( to_ngl_vec3(pos), to_ngl_vec3(g) );
    auto voa = WorldObject::createLineGrid(20,20,20);
    auto wo = new WorldObject("groundPlane", voa, "ground_material", body, "ground_material");

    m_objects.push_back(wo);
}

WorldObject *World::addSphere(std::string name, const float pos[], float radius, float mass)
{
    auto body = m_physics->addSphere( to_ngl_vec3(pos), radius, mass);
    auto voa = WorldObject::createSphere(radius, 20);
    auto wo = new WorldObject(name, voa, "default", body ,"default");

    m_objects.push_back(wo);

    return wo;
}

WorldObject *World::addBox(std::string name, const float pos[], const float dimension[], float mass)
{
    auto body = m_physics->addBox( to_ngl_vec3(pos), dimension[0], dimension[1], dimension[2], mass);
    auto voa = WorldObject::createBox( dimension[0], dimension[1], dimension[2] );
    auto wo = new WorldObject(name, voa, "default", body, "default");

    m_objects.push_back(wo);

    return wo;
}

/*
static void createBox(const std::string &_name, float _width, float _height, float _depth) noexcept;

static void createCapsule(const std::string &_name,const float _radius=1.0f, const float _height=2.0f, const int _precision=20) noexcept;

//----------------------------------------------------------------------------------------------------------------------
/// @brief create a line based grid (like the maya ground plane)
/// @param[in] _name the name of the object created used when drawing
/// @param[in] _width the width of the grid
/// @param[in] _depth the depth of the grid
/// @param[in] _steps the number of steps for the grid
//----------------------------------------------------------------------------------------------------------------------
static void createLineGrid( const std::string &_name, float _width, float _depth,  int _steps ) noexcept;


//----------------------------------------------------------------------------------------------------------------------
/// @brief create a Quad Cylinder as a vbo with auto generated texture cords
/// @param[in] _name the name of the object created used when drawing
/// @param[in] _radius the base radius of the Cylinder
/// @param[in] _height the height of the Cylinder
/// @param[in] _slices the number of quad elements around the Cylinder
/// @param[in] _stacks the number of quad elements along the centeral axis
//----------------------------------------------------------------------------------------------------------------------
static void createCylinder( const std::string &_name,const float _radius,  float _height, unsigned int _slices, unsigned int _stacks) noexcept;
//----------------------------------------------------------------------------------------------------------------------
/// @brief create a Quad Cone as a vao with auto generated texture cords
/// @param[in] _name the name of the object created used when drawing
/// @param[in] _base the base radius of the cone
/// @param[in] _height the height of the cone
/// @param[in] _slices the number of quad elements around the cone
/// @param[in] _stacks the number of quad elements along the centeral axis
//----------------------------------------------------------------------------------------------------------------------
static void createCone(const std::string &_name,  float _base,  float _height,  unsigned int _slices, unsigned int _stacks ) noexcept;
*/
