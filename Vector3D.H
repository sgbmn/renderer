// Vector3D.H

// Sam Bradley
// CS 5721

#ifndef VECTOR3D
#define VECTOR3D

#include <iostream>
using namespace std;

// Vecotor3DInfo is an object that represents a 3-dimentional
// vector represented by an x, y and z corrdinate

class Vector3D {

private:

// private data members
double x, y, z; // x, y  and z coordinates

public:

// public class methods
Vector3D( void );
Vector3D( double x2, double y2, double z2 ); // ctor
double  getX();
double  getY();
double  getZ();
void    setXYZ( double x2, double y2, double z2 );
void    setX( double x2 );
void    setY( double y2 );
void    setZ( double z2 );
double  length();
double  dot( Vector3D );
void normalize();

// overriden functions
Vector3D operator + ( Vector3D v2 ) const {
	Vector3D v( x+v2.getX(), y+v2.getY(), z+v2.getZ() );
	return v;
}
Vector3D operator - ( Vector3D v2 ) const {
	Vector3D v( x-v2.getX(), y-v2.getY(), z-v2.getZ() );
	return v;
}
Vector3D operator * ( Vector3D v2 ) const{
	double i, j, k;
	i = y*v2.getZ() - v2.getY()*z;
	j = (x*v2.getZ() - v2.getX()*z)*(-1);
	k = x*v2.getY() - v2.getX()*y;
	
	Vector3D v( i, j, k );
	return v;
}
Vector3D operator * ( double scalar ) const {
	Vector3D v( x*scalar, y*scalar, z*scalar );
	return v;
}
Vector3D operator / ( double scalar ) const {
	double i, j, k;
	i = x/scalar;
	j = y/scalar;
	k = z/scalar;
	Vector3D v( i, j, k );
	return v;
}
};

#endif