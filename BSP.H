// BSP.H

// Sam Bradley
// CS 5721

#ifndef BSP_H
#define BSP_H

#include "Triangle.H"
#include "Color.H"

class BSPTree {

private:
Triangle triangle;

public:
BSPTree *negative;
BSPTree *positive;
BSPTree( void );
BSPTree( Triangle t );
void add( Triangle t );
void getTri( Vector4D& p, Vector4D& q, Vector4D& r );
void getTri( Vector4D& p, Vector4D& q, Vector4D& r, Color& c0, Color& c1, Color& c2 );
void getTri( Vector4D& p, Vector4D& q, Vector4D& r, Color& c0, Color& c1, Color& c2,
			 Vector4D& n0, Vector4D& n1, Vector4D& n2 );
void getTri( Triangle& t );
};

#endif
