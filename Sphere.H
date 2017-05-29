// Sphere.H

// Sam Bradley
// CS 5721

#ifndef	SPHERE
#define SPHERE

#include "Object3D.H"
#include "Triangle.H"

class Sphere : public Object3D {

private:
Triangle* initial;
Triangle* t;
int sub;
int curr_size;
int count;

public:
Sphere( void );
void subdivide( Triangle* tri );

void transform(const Matrix4x4& m);
void getLineSegment(int idx, Vector4D& p, Vector4D& q);
void getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r );
int getVertices();
int getNumTri();

};

#endif