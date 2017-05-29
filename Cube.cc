// Cube.cc

// Sam Bradley
// CS 5721

#include "Cube.H"

Cube::Cube( void ) {
	triangles = 12;
	vertices = 12*3;
	t = new Triangle[triangles];
	Vector4D p0( 1, 1, 1, 1), p1( -1, 1, 1, 1 ), p2( -1, -1, 1, 1 ), p3( 1, -1, 1, 1 ),
		     p4( 1, 1, -1, 1 ), p5( -1, 1, -1, 1 ), p6( -1, -1, -1, 1 ), p7( 1, -1, -1, 1 );
	//front
	t[0].set( p0, p1, p2 );
	t[1].set( p2, p3, p0 );
	
	// top
	t[2].set( p0, p4, p5 );
	t[3].set( p5, p1, p0 );
	
	// right
	t[4].set( p3, p7, p4 );
	t[5].set( p4, p0, p3 );
	
	// left
	t[6].set( p1, p5, p6 );
	t[7].set( p6, p2, p1 );
	
	// bottom
	t[8].set( p3, p7, p6 );
	t[9].set( p6, p2, p3 );
	
	// back
	t[10].set( p4, p5, p6 );
	t[11].set( p6, p7, p4 ); 
}

void Cube::transform(const Matrix4x4& m) {
	for( int i=0; i<triangles; i++ ) {
		t[i].transform( m );
	}
}

void Cube::getLineSegment(int idx, Vector4D& p, Vector4D& q) {
	int triangle = idx/3;
	int index = idx%3;
	t[triangle].getLineSegment( index, p, q );
}

int Cube::getVertices() {
 return vertices;
}

int Cube::getNumTri() {
	return triangles;
}

void Cube::getTri( int idx, Vector4D& p, Vector4D& q, Vector4D& r ) {
	t[idx].get( p, q, r );
}