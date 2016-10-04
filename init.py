import aries
print 'init file loaded'

world = aries.getWorld()
world.setGravity( (0,-9.81,0) )
world.addGroundPlane( (0,0,0), (50,0.01,50) )

#world.addSphere("test_sphere", [0.0, 2.0, 0.0], 0.5, mass=1.0 )
world.addSphere("test_sphere1", [0.2, 3.0, 0.0], 0.5, mass=1.0 )
world.addSphere("test_sphere2", [0.5, 10.0, 0.0], 1, mass=0.5 )
world.addBox("test_box1", [5,2.5,0], [1,5,1], mass=500)
box1 = world.addBox("test_box2", [7,2.5,0], [1,5,1], mass=500)

box1.setPhysicalMaterial("gold")

#box = aries.createBox()
#world.addObject(box)


obj_list = world.getObjects()

print len(obj_list)

for obj in obj_list:
    print "object:", obj.name
    print "material:", obj.getShaderMaterial(), obj.getPhysicalMaterial()

#obj = aries.createBox( (sizeX, sizeY, sizeZ), (x,y,z), mass)
#world.addObject( obj, (x,y,z) )
