// Sphere.cc

// Sam Bradley
// CS 5721

#include "Sphere.H"
#include "PI.H"
#include <math.h>

Sphere::Sphere( void ) {
	sub = 3;
	triangles = 8*(int)pow( 4, sub );
	vertices = triangles*3;
	initial = new Triangle[8];
	t = new Triangle[triangles];
	curr_size = 8;
	count = 0;
 	Vector4D p0, p1, p2, p3, top( 0, 1, 0, 1 ), bottom( 0, -1, 0, 1 ), a, b, c;
	float r = 1;
	float x, z;
	x = r*cos(45*(PI/180));
	z = r*sin(45*(PI/180));
	p0.setXYZW( x, 0, z, 1 );
	x = r*cos(135*(PI/180));
	z = r*sin(135*(PI/180));
	p1.setXYZW( x, 0, z, 1 );
	x = r*cos(225*(PI/180));
	z = r*sin(225*(PI/180));
	p2.setXYZW( x, 0, z, 1 );
	x = r*cos(315*(PI/180));
	z = r*sin(315*(PI/180));
	p3.setXYZW( x, 0, z, 1 );
	
	// face 1
	initial[0].set( p0, p1, top );
	
	// face 2
	initial[1].set( p1, p2, top );
	
	// face 3
	initial[2].set( p2, p3, top );
	
	// face 4
	initial[3].set( p3, p0, top );
	
	// face 5
	initial[4].set( p0, p1, bottom );

	// face 6
	initial[5].set( p1, p2, bottom );
	
	// face 7
	initial[6].set( p2, p3, bottom );
	
	// face 8
	initial[7].set( p3, p0, bottom );
	
	subdivide( initial );

}

void Sphere::transform(const Matrix4x4& m) {
	for( int i=0; i<triangles; i++ ) {
		t[i].transform( m );
	}
}

void Sphere::getLineSegment(int idx, Vector4D& p, Vector4D& q) {
	int triangle = idx/3;
	int index = idx%3;
	t[triangle].getLineSegment( index, p, q );
}

int Sphere::getVertices() {
 return vertices;
}

void Sphere::subdivide( Triangle* tri) {
	Triangle newt[curr_size*4];
	Vector4D a, b, c, d, e, f;
	
	for( int i=0; i<curr_size; i++ ) { 
	// get triangle points
	tri[i].get( a, b, c );
	
	// find subdivisions
	d = (a+b)/2.0;
	e = (b+c)/2.0;
	f = (a+c)/2.0;
	
	// blow up points
	d.normalize();
	e.normalize();
	f.normalize();
	
	// create new triangles
	newt[(i*4)].set( a, d, f );
	newt[(i*4)+1].set( d, e, f );
	newt[(i*4)+2].set( d, b, e );
	newt[(i*4)+3].set( f, e, c );
	
	// also, copy them to the end array
	t[(i*4)].set( a, d, f );
	t[(i*4)+1].set( d, e, f );
	t[(i*4)+2].set( d, b, e );
	t[(i*4)+3].set( f, e, c );

	}
	
	curr_size *= 4;
	count++;
	
	if( count < sub ) {
		subdivide( newt );
	}
		
}

int Sphere::getNumTri() {
	return triangles;
}

void Sphere::getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r ) {
	t[idx].get( p, q, r );
}