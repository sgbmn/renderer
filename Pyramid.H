// Pyramid.H

// Sam Bradley
// CS 5721

#ifndef PYRAMID
#define PYRAMID

#include "Object3D.H"
#include "Triangle.H"

class Pyramid : public Object3D {

private:
Triangle *t;

public:
Pyramid( void );

void transform(const Matrix4x4& m);
void getLineSegment(int idx, Vector4D& p, Vector4D& q);
void getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r );
int getVertices();
int getNumTri();

};

#endif