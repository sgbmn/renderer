// Matrix4x4.H

// Sam Bradley
// CS 5721

#ifndef	MATRIX4X4
#define MATRIX4X4

#include "Vector3D.H"
#include "Vector4D.H"

class Matrix4x4 {

private:
// private data members
double d[4][4];

public:		
// public class methods
Matrix4x4( void );
Matrix4x4( double a1, double a2, double a3, double a4,
		   double b1, double b2, double b3, double b4,
		   double c1, double c2, double c3, double c4,
		   double d1, double d2, double d3, double d4);
void  set( double a1, double a2, double a3, double a4,
		   double b1, double b2, double b3, double b4,
		   double c1, double c2, double c3, double c4,
		   double d1, double d2, double d3, double d4);
void setIdentity( void );
Matrix4x4 transpose( void ); // returns the transpose
Matrix4x4 inverse( void ); // returns the inverse of the matrix
double get( int i, int j ); // returns the value at index i,j
void makeTranslate( Vector3D& v );  // sets the matrix to the translation matrix
void makeRotateZ( double theta_in_deg ); // creates the Z rotation matrix
void makeRotateY( double theta_in_deg ); // creates the Y rotation matrix
void makeRotateX( double theta_in_deg ); // creates the X rotation matrix
void makeScale( Vector3D& v2 ); // creates the scale matrix
void makeOrtho( double l, double r, double t, double b, double n, double f, int x, int y ); // creates the orthographic viewing matrix
void makePerspective( double n, double f ); //creates the perspective viewing matrix
void makeEye( Vector3D eye, Vector3D gaze ); //creates the eye view matrix
void print( void ); //prints matrix to standard out

// overloaded operators
Matrix4x4 operator * ( Matrix4x4 m ) const {
	double a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4;
	a1 = d[0][0]*m.get(0,0)+d[1][0]*m.get(0,1)+d[2][0]*m.get(0,2)+d[3][0]*m.get(0,3);
	a2 = d[0][0]*m.get(1,0)+d[1][0]*m.get(1,1)+d[2][0]*m.get(1,2)+d[3][0]*m.get(1,3);
	a3 = d[0][0]*m.get(2,0)+d[1][0]*m.get(2,1)+d[2][0]*m.get(2,2)+d[3][0]*m.get(2,3);
	a4 = d[0][0]*m.get(3,0)+d[1][0]*m.get(3,1)+d[2][0]*m.get(3,2)+d[3][0]*m.get(3,3);
	b1 = d[0][1]*m.get(0,0)+d[1][1]*m.get(0,1)+d[2][1]*m.get(0,2)+d[3][1]*m.get(0,3);
	b2 = d[0][1]*m.get(1,0)+d[1][1]*m.get(1,1)+d[2][1]*m.get(1,2)+d[3][1]*m.get(1,3);
	b3 = d[0][1]*m.get(2,0)+d[1][1]*m.get(2,1)+d[2][1]*m.get(2,2)+d[3][1]*m.get(2,3);
	b4 = d[0][1]*m.get(3,0)+d[1][1]*m.get(3,1)+d[2][1]*m.get(3,2)+d[3][1]*m.get(3,3);
	c1 = d[0][2]*m.get(0,0)+d[1][2]*m.get(0,1)+d[2][2]*m.get(0,2)+d[3][2]*m.get(0,3);
	c2 = d[0][2]*m.get(1,0)+d[1][2]*m.get(1,1)+d[2][2]*m.get(1,2)+d[3][2]*m.get(1,3);
	c3 = d[0][2]*m.get(2,0)+d[1][2]*m.get(2,1)+d[2][2]*m.get(2,2)+d[3][2]*m.get(2,3);
	c4 = d[0][2]*m.get(3,0)+d[1][2]*m.get(3,1)+d[2][2]*m.get(3,2)+d[3][2]*m.get(3,3);;
	d1 = d[0][3]*m.get(0,0)+d[1][3]*m.get(0,1)+d[2][3]*m.get(0,2)+d[3][3]*m.get(0,3);
	d2 = d[0][3]*m.get(1,0)+d[1][3]*m.get(1,1)+d[2][3]*m.get(1,2)+d[3][3]*m.get(1,3);
	d3 = d[0][3]*m.get(2,0)+d[1][3]*m.get(2,1)+d[2][3]*m.get(2,2)+d[3][3]*m.get(2,3);
	d4 = d[0][3]*m.get(3,0)+d[1][3]*m.get(3,1)+d[2][3]*m.get(3,2)+d[3][3]*m.get(3,3);
	
	return Matrix4x4(a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4);
}

Vector4D operator * ( Vector4D v ) const {
	double a,b,c,e;
	a = d[0][0]*v.getX()+d[1][0]*v.getY()+d[2][0]*v.getZ()+d[3][0]*v.getW();
	b = d[0][1]*v.getX()+d[1][1]*v.getY()+d[2][1]*v.getZ()+d[3][1]*v.getW();
	c = d[0][2]*v.getX()+d[1][2]*v.getY()+d[2][2]*v.getZ()+d[3][2]*v.getW();
	e = d[0][3]*v.getX()+d[1][3]*v.getY()+d[2][3]*v.getZ()+d[3][3]*v.getW();
	
	return Vector4D( a, b, c, e );
}

Matrix4x4 operator * ( double scalar ) const {
	return Matrix4x4( d[0][0]/scalar, d[1][0]/scalar, d[2][0]/scalar, d[3][0]/scalar,
					  d[0][1]/scalar, d[1][1]/scalar, d[2][1]/scalar, d[3][1]/scalar,
					  d[0][2]/scalar, d[1][2]/scalar, d[2][2]/scalar, d[3][2]/scalar,
					  d[0][3]/scalar, d[1][3]/scalar, d[2][3]/scalar, d[3][3]/scalar);
}
};

#endif;