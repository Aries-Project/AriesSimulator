# This file was automatically generated by SWIG (http://www.swig.org).
# Version 3.0.8
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2, 6, 0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_aries', [dirname(__file__)])
        except ImportError:
            import _aries
            return _aries
        if fp is not None:
            try:
                _mod = imp.load_module('_aries', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _aries = swig_import_helper()
    del swig_import_helper
else:
    import _aries
del version_info
try:
    _swig_property = property
except NameError:
    pass  # Python < 2.2 doesn't have 'property'.


def _swig_setattr_nondynamic(self, class_type, name, value, static=1):
    if (name == "thisown"):
        return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name, None)
    if method:
        return method(self, value)
    if (not static):
        if _newclass:
            object.__setattr__(self, name, value)
        else:
            self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)


def _swig_setattr(self, class_type, name, value):
    return _swig_setattr_nondynamic(self, class_type, name, value, 0)


def _swig_getattr_nondynamic(self, class_type, name, static=1):
    if (name == "thisown"):
        return self.this.own()
    method = class_type.__swig_getmethods__.get(name, None)
    if method:
        return method(self)
    if (not static):
        return object.__getattr__(self, name)
    else:
        raise AttributeError(name)

def _swig_getattr(self, class_type, name):
    return _swig_getattr_nondynamic(self, class_type, name, 0)


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object:
        pass
    _newclass = 0


class SwigPyIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, SwigPyIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, SwigPyIterator, name)

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _aries.delete_SwigPyIterator
    __del__ = lambda self: None

    def value(self):
        return _aries.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _aries.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _aries.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _aries.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _aries.SwigPyIterator_equal(self, x)

    def copy(self):
        return _aries.SwigPyIterator_copy(self)

    def next(self):
        return _aries.SwigPyIterator_next(self)

    def __next__(self):
        return _aries.SwigPyIterator___next__(self)

    def previous(self):
        return _aries.SwigPyIterator_previous(self)

    def advance(self, n):
        return _aries.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _aries.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _aries.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _aries.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _aries.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _aries.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _aries.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self
SwigPyIterator_swigregister = _aries.SwigPyIterator_swigregister
SwigPyIterator_swigregister(SwigPyIterator)

class vertData(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, vertData, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, vertData, name)
    __repr__ = _swig_repr
    __swig_setmethods__["u"] = _aries.vertData_u_set
    __swig_getmethods__["u"] = _aries.vertData_u_get
    if _newclass:
        u = _swig_property(_aries.vertData_u_get, _aries.vertData_u_set)
    __swig_setmethods__["v"] = _aries.vertData_v_set
    __swig_getmethods__["v"] = _aries.vertData_v_get
    if _newclass:
        v = _swig_property(_aries.vertData_v_get, _aries.vertData_v_set)
    __swig_setmethods__["nx"] = _aries.vertData_nx_set
    __swig_getmethods__["nx"] = _aries.vertData_nx_get
    if _newclass:
        nx = _swig_property(_aries.vertData_nx_get, _aries.vertData_nx_set)
    __swig_setmethods__["ny"] = _aries.vertData_ny_set
    __swig_getmethods__["ny"] = _aries.vertData_ny_get
    if _newclass:
        ny = _swig_property(_aries.vertData_ny_get, _aries.vertData_ny_set)
    __swig_setmethods__["nz"] = _aries.vertData_nz_set
    __swig_getmethods__["nz"] = _aries.vertData_nz_get
    if _newclass:
        nz = _swig_property(_aries.vertData_nz_get, _aries.vertData_nz_set)
    __swig_setmethods__["x"] = _aries.vertData_x_set
    __swig_getmethods__["x"] = _aries.vertData_x_get
    if _newclass:
        x = _swig_property(_aries.vertData_x_get, _aries.vertData_x_set)
    __swig_setmethods__["y"] = _aries.vertData_y_set
    __swig_getmethods__["y"] = _aries.vertData_y_get
    if _newclass:
        y = _swig_property(_aries.vertData_y_get, _aries.vertData_y_set)
    __swig_setmethods__["z"] = _aries.vertData_z_set
    __swig_getmethods__["z"] = _aries.vertData_z_get
    if _newclass:
        z = _swig_property(_aries.vertData_z_get, _aries.vertData_z_set)

    def __init__(self):
        this = _aries.new_vertData()
        try:
            self.this.append(this)
        except Exception:
            self.this = this
    __swig_destroy__ = _aries.delete_vertData
    __del__ = lambda self: None
vertData_swigregister = _aries.vertData_swigregister
vertData_swigregister(vertData)


_aries.eBOX_SHAPE_swigconstant(_aries)
eBOX_SHAPE = _aries.eBOX_SHAPE

_aries.eSPHERE_SHAPE_swigconstant(_aries)
eSPHERE_SHAPE = _aries.eSPHERE_SHAPE

_aries.eCYLYNDER_SHAPE_swigconstant(_aries)
eCYLYNDER_SHAPE = _aries.eCYLYNDER_SHAPE

_aries.eCAPSULE_SHAPE_swigconstant(_aries)
eCAPSULE_SHAPE = _aries.eCAPSULE_SHAPE

_aries.eCONE_SHAPE_swigconstant(_aries)
eCONE_SHAPE = _aries.eCONE_SHAPE

_aries.eMESH_SHAPE_swigconstant(_aries)
eMESH_SHAPE = _aries.eMESH_SHAPE
class WorldObject(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, WorldObject, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, WorldObject, name)
    __repr__ = _swig_repr
    __swig_setmethods__["name"] = _aries.WorldObject_name_set
    __swig_getmethods__["name"] = _aries.WorldObject_name_get
    if _newclass:
        name = _swig_property(_aries.WorldObject_name_get, _aries.WorldObject_name_set)
    __swig_setmethods__["shaderMaterial"] = _aries.WorldObject_shaderMaterial_set
    __swig_getmethods__["shaderMaterial"] = _aries.WorldObject_shaderMaterial_get
    if _newclass:
        shaderMaterial = _swig_property(_aries.WorldObject_shaderMaterial_get, _aries.WorldObject_shaderMaterial_set)
    __swig_setmethods__["vao"] = _aries.WorldObject_vao_set
    __swig_getmethods__["vao"] = _aries.WorldObject_vao_get
    if _newclass:
        vao = _swig_property(_aries.WorldObject_vao_get, _aries.WorldObject_vao_set)
    __swig_setmethods__["physicalMaterial"] = _aries.WorldObject_physicalMaterial_set
    __swig_getmethods__["physicalMaterial"] = _aries.WorldObject_physicalMaterial_get
    if _newclass:
        physicalMaterial = _swig_property(_aries.WorldObject_physicalMaterial_get, _aries.WorldObject_physicalMaterial_set)
    __swig_setmethods__["physicalBody"] = _aries.WorldObject_physicalBody_set
    __swig_getmethods__["physicalBody"] = _aries.WorldObject_physicalBody_get
    if _newclass:
        physicalBody = _swig_property(_aries.WorldObject_physicalBody_get, _aries.WorldObject_physicalBody_set)

    def __init__(self, *args):
        this = _aries.new_WorldObject(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def draw(self):
        return _aries.WorldObject_draw(self)

    def getTransformMatrix(self):
        return _aries.WorldObject_getTransformMatrix(self)

    def setShaderMaterial(self, _material):
        return _aries.WorldObject_setShaderMaterial(self, _material)

    def getShaderMaterial(self):
        return _aries.WorldObject_getShaderMaterial(self)

    def setPhysicalMaterial(self, _material):
        return _aries.WorldObject_setPhysicalMaterial(self, _material)

    def getPhysicalMaterial(self):
        return _aries.WorldObject_getPhysicalMaterial(self)
    __swig_getmethods__["createLineGrid"] = lambda x: _aries.WorldObject_createLineGrid
    if _newclass:
        createLineGrid = staticmethod(_aries.WorldObject_createLineGrid)
    __swig_getmethods__["createSphere"] = lambda x: _aries.WorldObject_createSphere
    if _newclass:
        createSphere = staticmethod(_aries.WorldObject_createSphere)
    __swig_getmethods__["createCapsule"] = lambda x: _aries.WorldObject_createCapsule
    if _newclass:
        createCapsule = staticmethod(_aries.WorldObject_createCapsule)
    __swig_getmethods__["createCylinder"] = lambda x: _aries.WorldObject_createCylinder
    if _newclass:
        createCylinder = staticmethod(_aries.WorldObject_createCylinder)
    __swig_getmethods__["createCone"] = lambda x: _aries.WorldObject_createCone
    if _newclass:
        createCone = staticmethod(_aries.WorldObject_createCone)
    __swig_getmethods__["createBox"] = lambda x: _aries.WorldObject_createBox
    if _newclass:
        createBox = staticmethod(_aries.WorldObject_createBox)
    __swig_destroy__ = _aries.delete_WorldObject
    __del__ = lambda self: None
WorldObject_swigregister = _aries.WorldObject_swigregister
WorldObject_swigregister(WorldObject)

def WorldObject_createLineGrid(_width, _depth, _steps):
    return _aries.WorldObject_createLineGrid(_width, _depth, _steps)
WorldObject_createLineGrid = _aries.WorldObject_createLineGrid

def WorldObject_createSphere(_radius, _precision=20):
    return _aries.WorldObject_createSphere(_radius, _precision)
WorldObject_createSphere = _aries.WorldObject_createSphere

def WorldObject_createCapsule(_radius, _height, _precision=20):
    return _aries.WorldObject_createCapsule(_radius, _height, _precision)
WorldObject_createCapsule = _aries.WorldObject_createCapsule

def WorldObject_createCylinder(_radius, _height, _slices, _stacks):
    return _aries.WorldObject_createCylinder(_radius, _height, _slices, _stacks)
WorldObject_createCylinder = _aries.WorldObject_createCylinder

def WorldObject_createCone(_base, _height, _slices, _stacks):
    return _aries.WorldObject_createCone(_base, _height, _slices, _stacks)
WorldObject_createCone = _aries.WorldObject_createCone

def WorldObject_createBox(_width, _height, _depth):
    return _aries.WorldObject_createBox(_width, _height, _depth)
WorldObject_createBox = _aries.WorldObject_createBox

class ObjectVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, ObjectVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, ObjectVector, name)
    __repr__ = _swig_repr

    def iterator(self):
        return _aries.ObjectVector_iterator(self)
    def __iter__(self):
        return self.iterator()

    def __nonzero__(self):
        return _aries.ObjectVector___nonzero__(self)

    def __bool__(self):
        return _aries.ObjectVector___bool__(self)

    def __len__(self):
        return _aries.ObjectVector___len__(self)

    def __getslice__(self, i, j):
        return _aries.ObjectVector___getslice__(self, i, j)

    def __setslice__(self, *args):
        return _aries.ObjectVector___setslice__(self, *args)

    def __delslice__(self, i, j):
        return _aries.ObjectVector___delslice__(self, i, j)

    def __delitem__(self, *args):
        return _aries.ObjectVector___delitem__(self, *args)

    def __getitem__(self, *args):
        return _aries.ObjectVector___getitem__(self, *args)

    def __setitem__(self, *args):
        return _aries.ObjectVector___setitem__(self, *args)

    def pop(self):
        return _aries.ObjectVector_pop(self)

    def append(self, x):
        return _aries.ObjectVector_append(self, x)

    def empty(self):
        return _aries.ObjectVector_empty(self)

    def size(self):
        return _aries.ObjectVector_size(self)

    def swap(self, v):
        return _aries.ObjectVector_swap(self, v)

    def begin(self):
        return _aries.ObjectVector_begin(self)

    def end(self):
        return _aries.ObjectVector_end(self)

    def rbegin(self):
        return _aries.ObjectVector_rbegin(self)

    def rend(self):
        return _aries.ObjectVector_rend(self)

    def clear(self):
        return _aries.ObjectVector_clear(self)

    def get_allocator(self):
        return _aries.ObjectVector_get_allocator(self)

    def pop_back(self):
        return _aries.ObjectVector_pop_back(self)

    def erase(self, *args):
        return _aries.ObjectVector_erase(self, *args)

    def __init__(self, *args):
        this = _aries.new_ObjectVector(*args)
        try:
            self.this.append(this)
        except Exception:
            self.this = this

    def push_back(self, x):
        return _aries.ObjectVector_push_back(self, x)

    def front(self):
        return _aries.ObjectVector_front(self)

    def back(self):
        return _aries.ObjectVector_back(self)

    def assign(self, n, x):
        return _aries.ObjectVector_assign(self, n, x)

    def resize(self, *args):
        return _aries.ObjectVector_resize(self, *args)

    def insert(self, *args):
        return _aries.ObjectVector_insert(self, *args)

    def reserve(self, n):
        return _aries.ObjectVector_reserve(self, n)

    def capacity(self):
        return _aries.ObjectVector_capacity(self)
    __swig_destroy__ = _aries.delete_ObjectVector
    __del__ = lambda self: None
ObjectVector_swigregister = _aries.ObjectVector_swigregister
ObjectVector_swigregister(ObjectVector)

class World(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, World, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, World, name)
    __repr__ = _swig_repr

    def __init__(self):
        this = _aries.new_World()
        try:
            self.this.append(this)
        except Exception:
            self.this = this
    __swig_destroy__ = _aries.delete_World
    __del__ = lambda self: None
    __swig_getmethods__["instance"] = lambda x: _aries.World_instance
    if _newclass:
        instance = staticmethod(_aries.World_instance)

    def getObjects(self):
        return _aries.World_getObjects(self)

    def addGroundPlane(self, pos, g):
        return _aries.World_addGroundPlane(self, pos, g)

    def addSphere(self, name, pos, radius, mass):
        return _aries.World_addSphere(self, name, pos, radius, mass)

    def addBox(self, name, pos, dimension, mass):
        return _aries.World_addBox(self, name, pos, dimension, mass)

    def setGravity(self, gravity):
        return _aries.World_setGravity(self, gravity)
World_swigregister = _aries.World_swigregister
World_swigregister(World)

def World_instance():
    return _aries.World_instance()
World_instance = _aries.World_instance


def getWorld():
    return _aries.getWorld()
getWorld = _aries.getWorld
# This file is compatible with both classic and new-style classes.


