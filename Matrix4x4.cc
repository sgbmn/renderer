// Matrix4x4.cc

// Sam Bradley
// CS 5721

#include "Matrix4x4.H"
#include <math.h>
#include <iostream>

#define PI 3.141592653589793238462643383279502884197169399375105820974944592

using namespace std;

Matrix4x4::Matrix4x4( void ) {
	setIdentity();
}

Matrix4x4::Matrix4x4( double a1, double a2, double a3, double a4,
					  double b1, double b2, double b3, double b4,
					  double c1, double c2, double c3, double c4,
					  double d1, double d2, double d3, double d4) {
	set( a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4 );
}

void  Matrix4x4::set( double a1, double a2, double a3, double a4,
					 double b1, double b2, double b3, double b4,
					 double c1, double c2, double c3, double c4,
					 double d1, double d2, double d3, double d4) {
	d[0][0]=a1;d[1][0]=a2;d[2][0]=a3;d[3][0]=a4;
	d[0][1]=b1;d[1][1]=b2;d[2][1]=b3;d[3][1]=b4;
	d[0][2]=c1;d[1][2]=c2;d[2][2]=c3;d[3][2]=c4;
	d[0][3]=d1;d[1][3]=d2;d[2][3]=d3;d[3][3]=d4;
}

// sets the matrix to the identity
void Matrix4x4::setIdentity( void ) {
	d[0][0]=1;d[1][0]=0;d[2][0]=0;d[3][0]=0;
	d[0][1]=0;d[1][1]=1;d[2][1]=0;d[3][1]=0;
	d[0][2]=0;d[1][2]=0;d[2][2]=1;d[3][2]=0;
	d[0][3]=0;d[1][3]=0;d[2][3]=0;d[3][3]=1;
}

// returns the transpose
Matrix4x4 Matrix4x4::transpose( void ) {
	Matrix4x4 m(d[0][0],d[0][1],d[0][2],d[0][3],d[1][0],d[1][1],d[1][2],d[1][3],
				d[2][0],d[2][1],d[2][2],d[2][3],d[3][0],d[3][1],d[3][2],d[3][3]);
	return m;
}

// returns the inverse of the matrix
Matrix4x4 Matrix4x4::inverse( void ) {
	double det = d[0][0]*
					(d[1][1]*
						(d[2][2]*d[3][3]-d[3][2]*d[2][3]) -
					 d[2][1]*
						(d[1][2]*d[3][3]-d[3][2]*d[1][3]) +
					 d[3][1]*
						(d[1][2]*d[2][3]-d[2][2]*d[1][3])) -
				d[1][0]*
					(d[0][1]*
						(d[2][2]*d[3][3]-d[3][2]*d[2][3]) -
					 d[2][1]*
						(d[0][2]*d[3][3]-d[3][2]*d[0][3]) +
					 d[3][1]*
						(d[0][2]*d[2][3]-d[2][2]*d[0][3])) +
				d[2][0]*
					(d[0][1]*
						(d[1][2]*d[3][3]-d[3][2]*d[1][3]) -
					 d[1][1]*
						(d[0][2]*d[3][3]-d[3][2]*d[0][3]) +
					 d[3][1]*
						(d[0][2]*d[1][3]-d[1][2]*d[0][3])) -
				d[3][0]*
					(d[0][1]*
						(d[1][2]*d[2][3]-d[2][2]-d[1][3]) -
					 d[1][1]*
						(d[0][2]*d[2][3]-d[2][2]-d[0][3]) +
					 d[2][1]*
						(d[0][2]*d[1][3]-d[1][2]-d[0][3]));
		return transpose()*(1/det);
}

// returns the value at index i,j 
double Matrix4x4::get( int i, int j ) {
	return d[i][j];
}

// sets the matrix to the translation matrix
void Matrix4x4::makeTranslate( Vector3D& v ) {
	d[3][0] = v.getX();
	d[3][1] = v.getY();
	d[3][2] = v.getZ();
}

// creates the Z rotation matrix  
void Matrix4x4::makeRotateZ( double theta_in_deg ) {
	double theta_in_rad = theta_in_deg *(PI/180);
	d[0][0] = cos( theta_in_rad );
	d[1][0] = (-1)*sin( theta_in_rad );
	d[0][1] = sin( theta_in_rad );
	d[1][1] = cos( theta_in_rad );
}

// creates the Y rotation matrix 
void Matrix4x4::makeRotateY( double theta_in_deg ) {
	double theta_in_rad = theta_in_deg *(PI/180);
	d[0][0] = cos( theta_in_rad );
	d[2][0] = sin( theta_in_rad );
	d[0][2] = (-1)*sin(  theta_in_rad );
	d[2][2] = cos( theta_in_rad );
} 

// creates the X rotation matrix
void Matrix4x4::makeRotateX( double theta_in_deg ) {
	double theta_in_rad = theta_in_deg *(PI/180);
	d[1][1] = cos( theta_in_rad );
	d[2][1] = (-1)*sin( theta_in_rad );
	d[1][2] = sin( theta_in_rad );
	d[2][2] = cos( theta_in_rad );
}

// creates the scale matrix 
void Matrix4x4::makeScale( Vector3D& v ) {
	d[0][0] = v.getX();
	d[1][1] = v.getY();
	d[2][2] = v.getZ();
}

// creates the orthographic viewing matrix
void Matrix4x4::makeOrtho( double l, double r, double t, double b, double n, double f, int x, int y ) {
	Matrix4x4 mc( x/2.0, 0, 0, (x-1)/2.0, 
	                  0, y/2.0, 0, (y-1)/2.0,
				   0, 0, 1, 0, 0, 0, 0, 1);
	Matrix4x4 ms( 2.0/(r-l), 0, 0, 0, 0, 2.0/(t-b), 0, 0, 0, 0, 2.0/(n-f), 0, 0, 0, 0, 1 );
	Matrix4x4 mo( 1, 0, 0, (-1.0)*((l+r)/2.0), 0, 1, 0, (-1)*((b+t)/2.0), 0, 0, 1, (-1)*((n+f)/2.0), 0, 0, 0, 1);
	Matrix4x4 m = mc*ms*mo;
	*this = mc*ms*mo;
}

//creates the perspective viewing matrix
void Matrix4x4::makePerspective( double n, double f ) {	
	setIdentity();
	d[0][0] = n;
	d[1][1] = n;
	d[2][2] = n+f;
	d[3][2] = -1.0 * f * n;
	d[2][3] = 1.0;
	d[3][3] = 0.0;
}

//creates eye view matrix
void Matrix4x4::makeEye( Vector3D eye, Vector3D gaze ) {
	Matrix4x4 mt;
	Vector3D u, v, w;
	Vector3D up( 0, 1, 0 );
	mt.setIdentity();
	eye = eye*(-1);
	mt.makeTranslate( eye );
	w = gaze*(-1);
	u = ( up*w )/( (up*w).length() );
	v = w*u;
	Matrix4x4 m( u.getX(), u.getY(), u.getZ(), 0,
				 v.getX(), v.getY(), v.getZ(), 0,
				 w.getX(), w.getY(), w.getZ(), 0,
				 0,        0,        0,        1 );
				 
	m = m*mt;
	
	set( m.get( 0, 0 ), m.get( 1, 0 ), m.get( 2, 0 ), m.get( 3, 0 ),
		 m.get( 0, 1 ), m.get( 1, 1 ), m.get( 2, 1 ), m.get( 3, 1 ),
		 m.get( 0, 2 ), m.get( 1, 2 ), m.get( 2, 2 ), m.get( 3, 2 ),
		 m.get( 0, 3 ), m.get( 1, 3 ), m.get( 2, 3 ), m.get( 3, 3 ) );

}

//prints matrix to standard out
void Matrix4x4::print( void ) {
	for( int i=0; i<4; i++ ) {
		for( int j=0; j<4; j++ ) {
			cout << get( j, i ) << " ";
		}
		cout << endl;
	}
	cout << endl;
}