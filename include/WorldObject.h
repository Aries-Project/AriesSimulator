#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <btBulletDynamicsCommon.h>
#include <ngl/Camera.h>
#include <ngl/Colour.h>
#include <ngl/Light.h>
#include <ngl/Text.h>
#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Obj.h>

struct vertData
{
    ngl::Real u;
    ngl::Real v;
    ngl::Real nx;
    ngl::Real ny;
    ngl::Real nz;
    ngl::Real x;
    ngl::Real y;
    ngl::Real z;
};

enum ObjectShape_e {
    eBOX_SHAPE,
    eSPHERE_SHAPE,
    eCYLYNDER_SHAPE,
    eCAPSULE_SHAPE,
    eCONE_SHAPE,
    eMESH_SHAPE
};

class WorldObject
{
protected:
    static void fghCircleTable(std::unique_ptr<float []> &io_sint, std::unique_ptr<float []> &io_cost,  int _n  ) noexcept;
    static ngl::VertexArrayObject* createVAO(const std::vector<vertData> &_data, const GLenum _mode) noexcept;
    static ngl::VertexArrayObject* createVAO(const  ngl::Real &_data, unsigned _size, const GLenum _mode) noexcept;
private:
    ObjectShape_e shape_type;

public:
    std::string name;

    std::string  shaderMaterial;
    std::shared_ptr<ngl::VertexArrayObject> vao;

    std::string physicalMaterial;
    btRigidBody *physicalBody;

public:
    WorldObject();

    WorldObject(const std::string _name, ngl::VertexArrayObject* _vao, std::string _shader_material, btRigidBody* _body, std::string _physical_material);

    void draw();

    ngl::Mat4 getTransformMatrix();

    void setShaderMaterial(const std::string _material);
    std::string getShaderMaterial();

    void setPhysicalMaterial(const std::string _material);
    std::string getPhysicalMaterial();

    static ngl::VertexArrayObject* createLineGrid   (float _width,  float _depth, int _steps ) noexcept;
    static ngl::VertexArrayObject* createSphere     (float _radius, int _precision = 20 ) noexcept;
    static ngl::VertexArrayObject* createCapsule    (float _radius, const float _height,  const int _precision = 20 ) noexcept;
    static ngl::VertexArrayObject* createCylinder   (float _radius,const float _height,unsigned int _slices,unsigned int _stacks ) noexcept;
    static ngl::VertexArrayObject* createCone       (float _base, float _height, unsigned int _slices, unsigned int _stacks  ) noexcept;
    static ngl::VertexArrayObject* createBox        (float _width, float _height, float _depth  ) noexcept;

};

#endif // WORLDOBJECT_H
