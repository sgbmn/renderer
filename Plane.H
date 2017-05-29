// Plane.H

// Sam Bradley
// CS 5721

#ifndef PLANE
#define PLANE

#include "Object3D.H"
#include "Triangle.H"
#include "Matrix4x4.H"
#include "Vector4D.H"

class Plane : public Object3D {

private:
Triangle *t;

public:
Plane( void );

void transform(const Matrix4x4& m);
void getLineSegment(int idx, Vector4D& p, Vector4D& q);
void getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r );
int getVertices();
int getNumTri();

};

#endif