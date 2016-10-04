 %module aries
 %{
 /* Includes the header in the wrapper code */
 #include "World.h"
 %}


/* Python tuple -> C array coversion for float */
%{
 int convert_float_array(PyObject *input, float *ptr, int size) {
  int i;
  if (!PySequence_Check(input)) {
      PyErr_SetString(PyExc_TypeError,"Expecting a sequence");
      return 0;
  }
  if (PyObject_Length(input) != size) {
      PyErr_SetString(PyExc_ValueError,"Sequence size mismatch");
      return 0;
  }
  for (i =0; i < size; i++) {
      PyObject *o = PySequence_GetItem(input,i);

      if (PyFloat_Check(o)) {
         ptr[i] = PyFloat_AsDouble(o);
         Py_DECREF(o);
      }
      else if(PyInt_Check(o)){
        //ptr[i] = PyFloat_AsDouble(o);
        long v = PyInt_AsLong(o);
        ptr[i] = (double)v;
        Py_DECREF(o);
      }
      else {
        Py_XDECREF(o);
        PyErr_SetString(PyExc_ValueError,"Expecting a sequence of floats");
        return 0;
      }

  }
  return 1;
}
%}

%typemap(in) float [ANY](float temp[$1_dim0]) {
   if (!convert_float_array($input,temp,$1_dim0)) {
      return NULL;
   }
   $1 = &temp[0];
}

/* Include STD::* wrappers */
%include <stl.i>
/* Parse the header file to generate wrappers */

%include "include/WorldObject.h"

namespace std {
%template(ObjectVector) vector<WorldObject*>;
}

%include "include/World.h"
