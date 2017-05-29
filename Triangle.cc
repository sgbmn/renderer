// Triangle.cc

// Sam Bradley
// CS 5721

#include "Triangle.H"
#include "PI.H"
#include <math.h>
#include <iostream>

using namespace std;

Triangle::Triangle( void ) {
	Vector4D normal;
	vertices = 3;
	triangles = 1;
	v = new Vector4D[vertices];
	
	double r = 1;
	double x, y;
	
	x = (r*cos(90*(PI/180)));
	y = (r*sin(90*(PI/180)));
	v[0].setXYZW( x, y, 0, 1);
	x = (r*cos(210*(PI/180)));
	y = (r*sin(210*(PI/180)));
	v[1].setXYZW( x, y, 0, 1 );
	x = (r*cos(330*(PI/180)));
	y = (r*sin(330*(PI/180)));
	v[2].setXYZW( x, y, 0, 1 );
	
	normal = ( v[1] - v[0] )*( v[2] - v[0] );
	normal.normalize();
	n[0] = normal;
	n[1] = normal;
	n[2] = normal;
	
	c[0].setColor( 255, 255, 255 );
	c[1].setColor( 255, 255, 255 );
	c[2].setColor( 255, 255, 255 ); 

}

Triangle::Triangle( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2 ) {
	Vector4D normal;
	vertices = 3;
	v = new Vector4D[vertices];	
	triangles = 1;
	v[0] = p0;
	v[1] = p1;
	v[2] = p2;
	
	normal = ( v[1] - v[0] )*( v[2] - v[0] );
	normal.normalize();
	n[0] = normal;
	n[1] = normal;
	n[2] = normal;
	
	c[0].setColor( 255, 255, 255 );
	c[1].setColor( 255, 255, 255 );
	c[2].setColor( 255, 255, 255 ); 
}

Triangle::Triangle( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2,
		  const Color& c0, const Color& c1, const Color& c2 ) {
	Vector4D normal;
	vertices = 3;
	v = new Vector4D[vertices];	
	triangles = 1;
	v[0] = p0;
	v[1] = p1;
	v[2] = p2;
	
	normal = ( v[1] - v[0] )*( v[2] - v[0] );
	normal.normalize();
	n[0] = normal;
	n[1] = normal;
	n[2] = normal;
	
	c[0] = c0;
	c[1] = c1;
	c[2] = c2; 
}

Triangle::Triangle( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2,
		  const Color& c0, const Color& c1, const Color& c2,
		  const Vector4D& n0, const Vector4D& n1, const Vector4D& n2) {
	Vector4D normal;
	vertices = 3;
	v = new Vector4D[vertices];	
	triangles = 1;
	v[0] = p0;
	v[1] = p1;
	v[2] = p2;
	
	n[0] = n0;
	n[1] = n1;
	n[2] = n2;
	
	c[0] = c0;
	c[1] = c1;
	c[2] = c2; 
}

void Triangle::transform( const Matrix4x4& m ) {
	v[0] = m*v[0];
	v[1] = m*v[1];
	v[2] = m*v[2];
}

void Triangle::getLineSegment(int idx, Vector4D& p, Vector4D& q){
	if( (idx+1)%3 == 0 ) {
		p = v[idx]; q = v[0];
	}
	else {
		p = v[idx]; q = v[idx+1];
	}
}

int Triangle::getVertices() {
	return vertices;
}

void Triangle::set( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2 ) {
	v[0] = p0;
	v[1] = p1;
	v[2] = p2;
}

void Triangle::set( const Vector4D& p0, const Vector4D& p1, const Vector4D& p2,
					const Color& c0, const Color& c1, const Color& c2 ) {
	v[0] = p0;
	v[1] = p1;
	v[2] = p2;
	
	c[0] = c0;
	c[1] = c2;
	c[2] = c2;
}

void Triangle::get( Vector4D& p0, Vector4D& p1, Vector4D& p2 ) {
	p0 = v[0];
	p1 = v[1];
	p2 = v[2];
}

void Triangle::get( Vector4D& p0, Vector4D& p1, Vector4D& p2, Color& c0, Color& c1, Color& c2 ) {
	p0 = v[0];
	p1 = v[1];
	p2 = v[2];
	
	c0 = c[0];
	c1 = c[0];
	c2 = c[0];
}

void Triangle::get( Vector4D& p0, Vector4D& p1, Vector4D& p2, Color& c0, Color& c1, Color& c2,
					Vector4D& n0, Vector4D& n1, Vector4D& n2 ) {
	p0 = v[0];
	p1 = v[1];
	p2 = v[2];
	
	c0 = c[0];
	c1 = c[1];
	c2 = c[2];
	
	n0 = n[0];
	n1 = n[1];
	n2 = n[2];
	
	/*std::cout << " drawing triangle " << v[0].getX() << "," << v[0].getY() << "," << v[0].getZ()
			  << " " << v[1].getX() << "," << v[1].getY() << "," << v[1].getZ() 
			  << " " << v[2].getX() << "," << v[2].getY() << "," << v[2].getZ() << endl;*/
}

void Triangle::getColor( Color& c0, Color& c1, Color& c2) {
	c0 = c[0];
	c1 = c[0];
	c2 = c[0];
}

int Triangle::getNumTri() {
	return triangles;
}

void Triangle::getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r ) {
	p = v[0];
	q = v[1];
	r = v[2];
}