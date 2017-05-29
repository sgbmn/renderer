// Triangle.H

// Sam Bradley
// CS 5721

#ifndef TRIANGLE
#define TRIANGLE

#include "Object3D.H"
#include "Matrix4x4.H"
#include "Color.H"

class Triangle : public Object3D{

private:
Vector4D *v;
Vector4D n[3];
Color c[3];

public:
Triangle( void );  // creates unit triangle
Triangle( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2 );
Triangle( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2,
		  const Color& c0, const Color& c1, const Color& c2 );
Triangle( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2,
		  const Color& c0, const Color& c1, const Color& c2,
		  const Vector4D& n0, const Vector4D& n1, const Vector4D& n2 );
void set( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2 );
void set( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2,
		  const Color& c0, const Color& c1, const Color& c2 );
void get( Vector4D& p0, Vector4D& p1, Vector4D& p2 );
void get( Vector4D& p0, Vector4D& p1, Vector4D& p2, Color& c0, Color& c1, Color& c2 );
void get( Vector4D& p0, Vector4D& p1, Vector4D& p2, Color& c0, Color& c1, Color& c2,
		  Vector4D& n0, Vector4D& n1, Vector4D& n2 );
void getColor( Color& c0, Color& c1, Color& c2 );

void transform(const Matrix4x4& m);
void getLineSegment(int idx, Vector4D& p, Vector4D& q);
void getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r );
int getVertices();
int getNumTri();

/*Triangle operator = ( Triangle t2 ) const {
	Vector4D v0, v1, v2, n0, n1, n2;
	Color c0, c1, c2;
	t2.get( v0, v1, v2, c0, c1, c2, n0, n1, n2 );
	return Triangle( v0, v1, v2, c0, c1, c2, n0, n1, n2 );
}*/

};

#endif;