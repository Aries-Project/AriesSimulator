#ifndef PHYSICSMATERIAL_H
#define PHYSICSMATERIAL_H

#include <string>

class PhysicsMaterial
{
public:
    PhysicsMaterial();

    std::string name;

    // Contact friction
    float m_dynamic_friction;
    float m_static_friction;
    float m_bounciness;

    // Air Drag
    float m_dynamic_drag;
    float m_static_drag;
};

#endif // PHYSICSMATERIAL_H
