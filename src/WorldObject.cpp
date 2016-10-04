#include "WorldObject.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for 2*PI convert to float to suppress windows warning as well
//----------------------------------------------------------------------------------------------------------------------
constexpr float TWO_PI= float(2*M_PI); //6.28318530717958647692   //360
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI based on system M_PI
//----------------------------------------------------------------------------------------------------------------------
constexpr float PI=float(M_PI); //3.14159265358979323846       //180
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI/2.0
//----------------------------------------------------------------------------------------------------------------------
constexpr float PI2=float(M_PI/2.0); //1.57079632679489661923      //90
//----------------------------------------------------------------------------------------------------------------------
/// @brief  pre-compute the value for value for PI/4.0
//----------------------------------------------------------------------------------------------------------------------
constexpr float PI4=float(M_PI/4.0); //0.785398163397448309615     //45
//----------------------------------------------------------------------------------------------------------------------

WorldObject::WorldObject()
{

}

WorldObject::WorldObject(const std::string _name, ngl::VertexArrayObject* _vao, std::string _shader_material, btRigidBody* _body, std::string _physical_material)
{
    name = _name;
    shaderMaterial = _shader_material;
    physicalMaterial = _physical_material;
    vao.reset(_vao);
    physicalBody = _body;
}

void WorldObject::draw()
{
    vao->bind();
    vao->draw();
    vao->unbind();
}

ngl::Mat4 WorldObject::getTransformMatrix()
{
    //btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[_index];
    //btRigidBody* body = btRigidBody::upcast(obj);
    if (physicalBody && physicalBody->getMotionState())
    {
        btTransform trans;

        physicalBody->getMotionState()->getWorldTransform(trans);
        float matrix[16];
        trans.getOpenGLMatrix(matrix);
        return ngl::Mat4( matrix[0],matrix[1],matrix[2],matrix[3],
                                             matrix[4],matrix[5],matrix[6],matrix[7],
                                             matrix[8],matrix[9],matrix[10],matrix[11],
                                             matrix[12],matrix[13],matrix[14],matrix[15]
                );
    }
    else return ngl::Mat4();
}

void WorldObject::setShaderMaterial(const std::string _material)
{
    this->shaderMaterial = _material;
}

void WorldObject::setPhysicalMaterial(const std::string _material)
{
    this->physicalMaterial = _material;
}

std::string WorldObject::getShaderMaterial()
{
    return this->shaderMaterial;
}

std::string WorldObject::getPhysicalMaterial()
{
    return this->physicalMaterial;
}

ngl::VertexArrayObject* WorldObject::createLineGrid(float _width,  float _depth, int _steps ) noexcept
{
  // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
  vertData vert;
    // claculate the step size for each grid value
  float wstep=_width/static_cast<float>(_steps);
  // pre-calc the offset for speed
  float ws2=_width/2.0f;
  // assign v as our value to change each vertex pair
  float v1=-ws2;

    // claculate the step size for each grid value
  float dstep=_depth/static_cast<float>(_steps);
  // pre-calc the offset for speed
  float ds2=_depth/2.0f;
  // assign v as our value to change each vertex pair
  float v2=-ds2;

    for(int i=0; i<=_steps; ++i)
    {
      // vertex 1 x,y,z
      vert.x=-ws2; // x
      vert.z=v1; // y
      vert.y=0.0; // z
      data.push_back(vert);
      // vertex 2 x,y,z
      vert.x=ws2; // x
      vert.z=v1; // y
      data.push_back(vert);


      // vertex 1 x,y,z
      vert.x=v2; // x
      vert.z=ds2; // y
      data.push_back(vert);
      // vertex 2 x,y,z
      vert.x=v2; // x
      vert.z=-ds2; // y
      data.push_back(vert);



      // now change our step value
      v1+=wstep;
      v2+=dstep;
    }

  return createVAO(data,GL_LINES);

}

ngl::VertexArrayObject* WorldObject::createSphere(float _radius, int _precision ) noexcept
{
    //  Sphere code based on a function Written by Paul Bourke.
    //  http://astronomy.swin.edu.au/~pbourke/opengl/sphere/
    // the next part of the code calculates the P,N,UV of the sphere for tri_strips

    float theta1 = 0.0f;
    float theta2 = 0.0f;
    float theta3 = 0.0f;

    // a std::vector to store our verts, remember vector packs contiguously so we can use it
    std::vector <vertData> data;
        // Disallow a negative number for radius.

  if( _radius < 0.0f )
    {
        _radius = -_radius;
    }
    // Disallow a negative number for _precision.
    if( _precision < 4 )
    {
        _precision = 4;
    }
  // now fill in a vertData structure and add to the data list for our sphere
  vertData d;
  for( int i = 0; i < _precision/2; ++i )
  {
    theta1 = i * TWO_PI / _precision - PI2;
    theta2 = (i + 1) * TWO_PI / _precision - PI2;

    for( int j = 0; j <= _precision; ++j )
    {
        theta3 = j * TWO_PI / _precision;

        d.nx = cosf(theta2) * cosf(theta3);
        d.ny = sinf(theta2);
        d.nz = cosf(theta2) * sinf(theta3);
        d.x = _radius * d.nx;
        d.y = _radius * d.ny;
        d.z = _radius * d.nz;

        d.u  = (j/static_cast<float>(_precision));
        d.v  = 2*(i+1)/static_cast<float>(_precision);

        data.push_back(d);

        d.nx = cosf(theta1) * cosf(theta3);
        d.ny = sinf(theta1);
        d.nz = cosf(theta1) * sinf(theta3);
        d.x = _radius * d.nx;
        d.y = _radius * d.ny;
        d.z = _radius * d.nz;

        d.u  = (j/static_cast<float>(_precision));
        d.v  = 2*i/static_cast<float>(_precision);
        data.push_back(d);
      } // end inner loop
  }// end outer loop

  return createVAO(data,GL_TRIANGLE_STRIP);

}


ngl::VertexArrayObject* WorldObject::createCapsule(float _radius, const float _height,  const int _precision ) noexcept

{
  // based on code from here
  // https://code.google.com/p/rgine/source/browse/trunk/RGine/opengl/src/RGLShapes.cpp
  /// @todo add UV's at some stage
  std::vector <vertData> data;
   vertData d;
   float h = _height / 2;
   float s, c, s1, c1, o;
   float sb, cb, sb1, cb1;
   float ang = (1.0f / _precision) * static_cast<float>(M_PI);
   for (int i = 0; i < 2 * _precision; ++i)
   {

     c = _radius * cosf(ang * i);
     c1= _radius * cosf(ang * (i + 1));
     s = _radius * sinf(ang * i);
     s1 =_radius * sinf(ang * (i + 1));
     //side top
     d.x = c1;
     d.y = h;
     d.z = s1;

     d.nx=c1;
     d.ny= 0.0;
     d.nz=s1;
     data.push_back(d);
     d.x = c;
     d.z = s;
     d.nx=c;
     d.nz=s;
     data.push_back(d);
     d.y = -h;
     data.push_back(d);

     //side bot
     data.push_back(d);
     d.x = c1;
     d.z = s1;
     d.nx= c1;
     d.nz=s1;
     data.push_back(d);
     d.x = c1;
     d.y = h;
     d.z = s1;
     d.nx=c1;
     d.nz=s1;
     data.push_back(d);

     for (int j = 0; j <=_precision; ++j)
     {
       if (j < _precision / 2)
       {
         o = h;
       }
       else
       {
         o = -h;
       }
       //longitude
       s = -sinf(ang * i);
       s1 = -sinf(ang * (i + 1));
       c = cosf(ang * i);
       c1 = cosf(ang * (i + 1));
       //latitude
       sb = _radius * sinf(ang * j);
       sb1 = _radius * sinf(ang * (j + 1));
       cb = _radius * cosf(ang * j);
       cb1 = _radius * cosf(ang * (j + 1));
       if (j != _precision - 1)
       {
         d.nx=d.x = sb * c;
         d.ny=d.y = cb + o;
         d.nz=d.z = sb * s;
         data.push_back(d);
         d.nx=d.x = sb1 * c;
         d.ny=d.y = cb1 + o;
         d.nz=d.z = sb1 * s;
         data.push_back(d);
         d.nx=d.x = sb1 * c1;
         d.ny=d.y = cb1 + o;
         d.nz=d.z = sb1 * s1;
         data.push_back(d);
       }
       if (j != 0)
       {
         d.nx=d.x = sb * c;
         d.ny=d.y = cb + o;
         d.nz=d.z = sb * s;
         data.push_back(d);
         d.nx=d.x = sb1 * c1;
         d.ny=d.y = cb1 + o;
         d.nz=d.z = sb1 * s1;
         data.push_back(d);
         d.nx=d.x = sb * c1;
         d.ny=d.y = cb + o;
         d.nz=d.z = sb * s1;
         data.push_back(d);
       }
     }
   }

  return createVAO(data,GL_TRIANGLES);
// end citation

}

ngl::VertexArrayObject* WorldObject::createCylinder(float _radius,const float _height,unsigned int _slices,unsigned int _stacks ) noexcept
{
  /* Step in z and radius as stacks are drawn. */

  float z0,z1;
  const float zStep = _height / ( ( _stacks > 0 ) ? _stacks : 1 );

  /* Pre-computed circle */
  std::unique_ptr<float []> sint;
  std::unique_ptr<float []> cost;


  fghCircleTable(sint,cost,static_cast<int>(-_slices));

  /* Do the stacks */
  // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
  vertData d;
  z0 = 0.0;
  z1 = zStep;
  // texture co-ords start at 0,0
  // texture steps
  float du=1.0f/_stacks;
  float dv=1.0f/_slices;
  /* Cover each stack with a quad strip, except the top stack */
  float u=0.0;
  float v=0.0;

  for(unsigned int i=1; i<=_stacks+1; ++i )
  {
    if(i==_stacks)
    {
        z1 = _height;
    }
    for(unsigned int j=0; j<=_slices-1; ++j)
    {
      // vert 1;
      d.u=u;
      d.v=v;
      d.nx=sint[j];
      d.ny=cost[j];
      d.nz=0;
      d.x=sint[j]*_radius;
      d.y=cost[j]*_radius;
      d.z=-z0/2.0f;
      data.push_back(d);
      // vert 2
      d.u=u;
      d.v=v+dv;
      d.z=-z1/2.0f;
      data.push_back(d);
      // vert 3
      d.u=u+du;
      d.v=v;
      d.nx=sint[j+1];
      d.ny=cost[j+1];
      d.x=sint[j+1]*_radius;
      d.y=cost[j+1]*_radius;
      d.z=-z0/2.0f;
      data.push_back(d);


      // vert 1;
      d.u=u+du;
      d.v=v;
      d.nx=sint[j+1];
      d.ny=cost[j+1];
      d.nz=0;
      d.x=sint[j+1]*_radius;
      d.y=cost[j+1]*_radius;
      d.z=-z0/2.0f;
      data.push_back(d);

      // vert 1;
      d.u=u;
      d.v=v+dv;
      d.nx=sint[j];
      d.ny=cost[j];
      d.nz=0;
      d.x=sint[j]*_radius;
      d.y=cost[j]*_radius;
      d.z=-z1/2.0f;
      data.push_back(d);

      // vert 1;
      d.u=u+du;
      d.v=v+dv;
      d.nx=sint[j+1];
      d.ny=cost[j+1];
      d.nz=0;
      d.x=sint[j+1]*_radius;
      d.y=cost[j+1]*_radius;
      d.z=-z1/2.0f;
      data.push_back(d);

      u+=du;
    }
    v+=dv;
    u=0.0f;
    z0 = z1; z1 += zStep;
   }
    // create VAO
  return createVAO(data,GL_TRIANGLES);

}

void WorldObject::fghCircleTable(std::unique_ptr<float []> &io_sint, std::unique_ptr<float []> &io_cost,  int _n  ) noexcept
{
  unsigned int i;
  /* Determine the angle between samples */
  const float angle = 2*PI/( ( _n == 0 ) ? 1 : _n );
  /* Table size, the sign of n flips the circle direction */
  int size = abs(_n);

  /* Allocate memory for n samples, plus duplicate of first entry at the end */
  io_sint.reset( new float[size+1]);
  io_cost.reset( new float[size+1]);
  /* Compute cos and sin around the circle */
  io_sint[0] = 0.0;
  io_cost[0] = 1.0;

  for (i=1; i<static_cast<unsigned int>(size); ++i)
  {
    io_sint[i] = sinf(angle*i);
    io_cost[i] = cosf(angle*i);
  }
  /* Last sample is duplicate of the first */
  io_sint[static_cast<unsigned int>(size)] = io_sint[0];
  io_cost[static_cast<unsigned int>(size)] = io_cost[0];
}

ngl::VertexArrayObject* WorldObject::createCone(float _base, float _height, unsigned int _slices, unsigned int _stacks  ) noexcept
{
  /* Step in z and radius as stacks are drawn. */
  float z0,z1;
  float r0,r1;

  const float zStep = _height / ( ( _stacks > 0 ) ? _stacks : 1 );
  const float rStep = _base / ( ( _stacks > 0 ) ? _stacks : 1 );

  /* Scaling factors for vertex normals */

  const float cosn = ( _height / sqrtf ( _height * _height + _base * _base ));
  const float sinn = ( _base   / sqrtf ( _height * _height + _base * _base ));

  /* Pre-computed circle */
  std::unique_ptr<float []> sint;
  std::unique_ptr<float []> cost;
  fghCircleTable(sint,cost,static_cast<int>(-_slices));

  z0 = 0.0f;
  z1 = zStep;

  r0 = _base;
  r1 = r0 - rStep;
  // texture co-ords start at 0,0
  // texture steps
  float du=1.0f/_stacks;
  float dv=1.0f/_slices;
  /* Cover each stack with a quad strip, except the top stack */
  float u=1.0f;
  float v=1.0f;
  // a std::vector to store our verts, remember vector packs contiguously so we can use it
  std::vector <vertData> data;
  vertData d;
  for(unsigned int i=0; i<_stacks; i++ )
  {
    for(unsigned int j=0; j<=_slices; j++)
    {
      d.u=u;
      d.v=v;
      d.nx = cost[j]*cosn; //ctheta;
      d.ny = sint[j] * sinn ;//-stheta;
      d.nz = sinn;// sphi;

      d.x=cost[j]*r0;
      d.y=sint[j]*r0;
      d.z=z0;
      data.push_back(d);
      // now for the next verts
      d.u=u;
      d.v=v-dv;

      d.x=cost[j]*r1;
      d.y=sint[j]*r1;
      d.z=z1;
      data.push_back(d);
      u-=du;
    }
    v-=dv;
    u=1.0;
    z0 = z1; z1 += zStep;
    r0 = r1; r1 -= rStep;

  }
  // create VAO
  return createVAO(data,GL_TRIANGLE_STRIP);
}

ngl::VertexArrayObject* WorldObject::createBox(float _width, float _height, float _depth  ) noexcept
{
    // 1 ----- 2 5
    // |      /  |
    // |     /   |
    // |    /    |
    // |   /     |
    // |  /      |
    // | /       |
    // 3/ 4 ---- 6

    float _w2 = _width / 2.0f;
    float _h2 = _height / 2.0f;
    float _d2 = _depth / 2.0f;

    const float cube[288]={
    // Top
    0.37500f,0.00000f,0.00000f,0.00000f,1.00000f, -_w2,-_h2, _d2, // 1
    0.62500f,0.00000f,0.00000f,0.00000f,1.00000f,  _w2,-_h2, _d2, // 2
    0.37500f,0.25000f,0.00000f,0.00000f,1.00000f, -_w2, _h2, _d2, // 3
    0.37500f,0.25000f,0.00000f,0.00000f,1.00000f, -_w2, _h2, _d2, // 4
    0.62500f,0.00000f,0.00000f,0.00000f,1.00000f,  _w2,-_h2, _d2, // 5
    0.62500f,0.25000f,0.00000f,0.00000f,1.00000f,  _w2, _h2, _d2, // 6
    // Back
    0.37500f,0.25000f,0.00000f,1.00000f,0.00000f, -_w2, _h2, _d2,
    0.62500f,0.25000f,0.00000f,1.00000f,0.00000f,  _w2, _h2, _d2,
    0.37500f,0.50000f,0.00000f,1.00000f,0.00000f, -_w2, _h2,-_d2,
    0.37500f,0.50000f,0.00000f,1.00000f,0.00000f, -_w2, _h2,-_d2,
    0.62500f,0.25000f,0.00000f,1.00000f,0.00000f,  _w2, _h2, _d2,
    0.62500f,0.50000f,0.00000f,1.00000f,0.00000f,  _w2, _h2,-_d2,
    // Bottom
    0.37500f,0.50000f,0.00000f,0.00000f,-1.00000f,-_w2, _h2,-_d2,
    0.62500f,0.50000f,0.00000f,0.00000f,-1.00000f, _w2, _h2,-_d2,
    0.37500f,0.75000f,0.00000f,0.00000f,-1.00000f,-_w2,-_h2,-_d2,
    0.37500f,0.75000f,0.00000f,0.00000f,-1.00000f,-_w2,-_h2,-_d2,
    0.62500f,0.50000f,0.00000f,0.00000f,-1.00000f, _w2, _h2,-_d2,
    0.62500f,0.75000f,0.00000f,0.00000f,-1.00000f, _w2,-_h2,-_d2,
    // Front
    0.37500f,0.75000f,0.00000f,-1.00000f,0.00000f,-_w2,-_h2,-_d2,
    0.62500f,0.75000f,0.00000f,-1.00000f,0.00000f, _w2,-_h2,-_d2,
    0.37500f,1.00000f,0.00000f,-1.00000f,0.00000f,-_w2,-_h2, _d2,
    0.37500f,1.00000f,0.00000f,-1.00000f,0.00000f,-_w2,-_h2, _d2,
    0.62500f,0.75000f,0.00000f,-1.00000f,0.00000f, _w2,-_h2,-_d2,
    0.62500f,1.00000f,0.00000f,-1.00000f,0.00000f, _w2,-_h2, _d2,
    // Right
    0.62500f,0.00000f,1.00000f,0.00000f,0.00000f,  _w2,-_h2, _d2,
    0.87500f,0.00000f,1.00000f,0.00000f,0.00000f,  _w2,-_h2,-_d2,
    0.62500f,0.25000f,1.00000f,0.00000f,0.00000f,  _w2, _h2, _d2,
    0.62500f,0.25000f,1.00000f,0.00000f,0.00000f,  _w2, _h2, _d2,
    0.87500f,0.00000f,1.00000f,0.00000f,0.00000f,  _w2,-_h2,-_d2,
    0.87500f,0.25000f,1.00000f,0.00000f,0.00000f,  _w2, _h2,-_d2,
    // Left
    0.12500f,0.00000f,-1.00000f,0.00000f,0.00000f,-_w2,-_h2,-_d2,
    0.37500f,0.00000f,-1.00000f,0.00000f,0.00000f,-_w2,-_h2, _d2,
    0.12500f,0.25000f,-1.00000f,0.00000f,0.00000f,-_w2, _h2,-_d2,
    0.12500f,0.25000f,-1.00000f,0.00000f,0.00000f,-_w2, _h2,-_d2,
    0.37500f,0.00000f,-1.00000f,0.00000f,0.00000f,-_w2,-_h2, _d2,
    0.37500f,0.25000f,-1.00000f,0.00000f,0.00000f,-_w2, _h2, _d2
    };

    return createVAO(cube[0], 288, GL_TRIANGLE_STRIP);
}

ngl::VertexArrayObject* WorldObject::createVAO(const std::vector<vertData> &_data,	const GLenum _mode) noexcept
{
  return createVAO(_data[0].u, _data.size()*8, _mode);
}

ngl::VertexArrayObject* WorldObject::createVAO(const ngl::Real &_data, unsigned _size, const GLenum _mode) noexcept
{

  ngl::VertexArrayObject *vao = ngl::VertexArrayObject::createVOA(_mode);
  // next we bind it so it's active for setting data
  vao->bind();

  // now we have our data add it to the VAO, we need to tell the VAO the following
  // how much (in bytes) data we are copying
  // a pointer to the first element of data (in this case the address of the first element of the
  // std::vector
  vao->setData(_size*sizeof(ngl::Real), _data);
  // in this case we have packed our data in interleaved format as follows
  // u,v,nx,ny,nz,x,y,z
  // If you look at the shader we have the following attributes being used
  // attribute vec3 inVert; attribute 0
  // attribute vec2 inUV; attribute 1
  // attribute vec3 inNormal; attribure 2
  // so we need to set the vertexAttributePointer so the correct size and type as follows
  // vertex is attribute 0 with x,y,z(3) parts of type GL_FLOAT, our complete packed data is
  // sizeof(vertData) and the offset into the data structure for the first x component is 5 (u,v,nx,ny,nz)..x
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(vertData),5);
  // uv same as above but starts at 0 and is attrib 1 and only u,v so 2
  vao->setVertexAttributePointer(1,2,GL_FLOAT,sizeof(vertData),0);
  // normal same as vertex only starts at position 2 (u,v)-> nx
  vao->setVertexAttributePointer(2,3,GL_FLOAT,sizeof(vertData),2);
  // now we have set the vertex attributes we tell the VAO class how many indices to draw when
  // glDrawArrays is called, in this case we use buffSize (but if we wished less of the sphere to be drawn we could
  // specify less (in steps of 3))
  vao->setNumIndices(_size / 8);
  // finally we have finished for now so time to unbind the VAO
  vao->unbind();
  return vao;
 // std::cout<<_name<<" Num Triangles "<<_data.size()/3<<"\n";

}
