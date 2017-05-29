// Object3D.H

// Sam Bradley
// CS 5721

#ifndef OBJECT3D
#define OBJECT3D

#include "Vector4D.H"
#include "Matrix4x4.H"

class Object3D {

protected:
int vertices;
int triangles;

public:
virtual void transform(const Matrix4x4& m) = 0;
virtual void getLineSegment(int idx, Vector4D& p, Vector4D& q) = 0;
virtual int getVertices() = 0;
virtual int getNumTri() = 0;
virtual void getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r ) = 0;  
   
};

#endif