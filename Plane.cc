// Plane.cc

// Sam Bradley
// CS 5721

#include "PI.H"
#include "Plane.H"

Plane::Plane( void ) {
	triangles = 2;
	vertices = triangles*3;
	t = new Triangle[triangles];
	Vector4D p0, p1, p2, p3;
	float r = 1;
	float x, y;
	x = r*cos(45*(PI/180));
	y = r*sin(45*(PI/180));
	p0.setXYZW( x, y, 0, 1 );
	x = r*cos(135*(PI/180));
	y = r*sin(135*(PI/180));
	p1.setXYZW( x, y, 0, 1 );
	x = r*cos(225*(PI/180));
	y = r*sin(225*(PI/180));
	p2.setXYZW( x, y, 0, 1 );
	x = r*cos(315*(PI/180));
	y = r*sin(315*(PI/180));
	p3.setXYZW( x, y, 0, 1 );
	t[0].set( p0, p1, p2 );
	t[1].set( p2, p3, p0 );
}

void Plane::transform(const Matrix4x4& m) {
	for( int i=0; i<triangles; i++ ) {
		t[i].transform( m );
	}
}

void Plane::getLineSegment(int idx, Vector4D& p, Vector4D& q) {
	int triangle = idx/3;
	int index = idx%3;
	t[triangle].getLineSegment( index, p, q );
}

int Plane::getVertices() {
	 return vertices;
}

int Plane::getNumTri() {
	return triangles;
}

void Plane::getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r ) {
	t[idx].get( p, q, r );
}