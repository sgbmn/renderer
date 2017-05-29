// Cube.H

// Sam Bradley
// CS 5721

#ifndef CUBE
#define CUBE

#include "Object3D.H"
#include "Triangle.H"

class Cube : public Object3D {

private:
Triangle *t;

public:
Cube( void );

void transform(const Matrix4x4& m);
void getLineSegment(int idx, Vector4D& p, Vector4D& q);
void getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r );
int getVertices();
int getNumTri();

};

#endif