// Pyramid.cc

// Sam Bradley
// CS 5721

#include "Pyramid.H"

Pyramid::Pyramid( void ) {
	triangles = 6;
	vertices = triangles*3;
	t = new Triangle[triangles];
	Vector4D p0( 1, 0, 1, 1), p1( -1, 0, 1, 1 ), p2( -1, 0, -1, 1 ), p3( 1, 0, -1, 1 ),
		     p4( 0, 1, 0, 1 );
	t[0].set( p0, p4, p1 );
	t[1].set( p1, p4, p2 );
	t[2].set( p2, p4, p3 );
	t[3].set( p3, p4, p0 );
	t[4].set( p0, p1, p2 );
	t[5].set( p2, p3, p0 );
}

void Pyramid::transform(const Matrix4x4& m) {
	for( int i=0; i<triangles; i++ ) {
		t[i].transform( m );
	}
}

void Pyramid::getLineSegment(int idx, Vector4D& p, Vector4D& q) {
	int triangle = idx/3;
	int index = idx%3;
	t[triangle].getLineSegment( index, p, q );
}

int Pyramid::getVertices() {
 return vertices;
}

int Pyramid::getNumTri() {
	return triangles;
}

void Pyramid::getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r ) {
	t[idx].get( p, q, r );
}