#ifndef WORLD_H
#define WORLD_H

#include "WorldObject.h"
#include <string>

class PhysicsWorld;

/*!
 * \brief The World class
 */
class World
{
    static World *p_instance;
    PhysicsWorld *m_physics;

    std::vector< WorldObject* > m_objects;
public:
    /*!
     * \brief World contructor.
     */
    World();

    ~World();

    /*!
     * \brief  instance of World object.
     * \return pointer to singleton World object.
     */
    static World *instance();

    std::vector< WorldObject* >& getObjects();
    /*!
     * \brief addGroundPlane
     * \param pos
     * \param g
     */
    void addGroundPlane(const float pos[3], const float g[3]);

    /*!
     * \brief addSphere
     * \param name
     * \param pos
     * \param mass
     * \param inertia
     */
    WorldObject* addSphere(std::string name, const float pos[3], float radius, float mass);

    /*!
     * \brief addBox
     * \param name
     * \param pos
     * \param mass
     */
    WorldObject* addBox(std::string name, const float pos[3], const float dimension[3], float mass);

    /*!
     * \brief setGravity
     * \param gravity
     */
    void setGravity(const float gravity[3]);
};

World* getWorld();

#endif // WORLD_H
