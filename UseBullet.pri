BULLET_ROOT=/home/daniel/Applications/bullet
INCLUDEPATH += $${BULLET_ROOT}/include
LIBS+= -L$${BULLET_ROOT}/lib -lBulletDynamics  -lBulletCollision  -lLinearMath
