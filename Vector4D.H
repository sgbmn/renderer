// Vector4D.H

// Sam Bradley
// CS 5721

#ifndef VECTOR4D
#define VECTOR4D

#include "Vector3D.H"

// Vecotor3DInfo is an object that represents a 3-dimentional
// vector represented by an x, y and z corrdinate

class Vector4D {

private:

// private data members
double x, y, z, w; // x, y, z and w coordinates

public:

// public class methods
Vector4D( void );
Vector4D( double x2, double y2, double z2, double w2 ); // ctor
double  getX( void );
double  getY( void );
double  getZ( void );
double  getW( void );
void    setXYZW( double x2, double y2, double z2, double w2	);
void    setX( double x2 );
void    setY( double y2 );
void    setZ( double z2 );
void    setW( double w2 );
double  length( void );
double  dot( Vector4D );

void normalize( void );

// overriden functions
Vector4D operator + ( Vector4D v2 ) const {
	Vector4D v( x+v2.getX(), y+v2.getY(), z+v2.getZ(), 1 );
	return v;
}
Vector4D operator - ( Vector4D v2 ) const {
	Vector4D v( x-v2.getX(), y-v2.getY(), z-v2.getZ(), 1 );
	return v;
}
Vector4D operator * ( Vector4D v2 ) const{
	Vector3D v3d( x, y, z );
	Vector3D v3d2( v2.getX(), v2.getY(), v2.getZ() );
	Vector3D result;
	
	result = v3d*v3d2;
	
	Vector4D v( result.getX(), result.getY(), result.getZ(), 1 );
	return v;
}
Vector4D operator * ( double scalar ) const {
	Vector4D v( x*scalar, y*scalar, z*scalar, w*scalar );
	return v;
}

Vector4D operator / ( double scalar ) const {
	Vector4D v( x/scalar, y/scalar, z/scalar, w/scalar );
	return v;
}
};

#endif