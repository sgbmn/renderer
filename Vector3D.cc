// Vecotor3D.cc

// Sam Bradley
// CS 5721

#include "Vector3D.H"
#include <math.h>

// Vecotr3DInfo constructor
Vector3D::Vector3D( void ) {
	x = 0;
	y = 0;
	z = 0;
}

// Vector3DInfo constructor
Vector3D::Vector3D( double x2, double y2, double z2 ) {
	x = x2;
	y = y2;
	z = z2;
}

// returns the x value
double Vector3D::getX() {
	if( isnan( x ) ) return 0;
	else return x;
}

// returns the y value
double Vector3D::getY() {
	if( isnan( y ) ) return 0;
	else return y;
}

// returns the z value
double Vector3D::getZ() {
	if( isnan( z ) ) return 0;
	else return z;
}

// sets the x, y and z coordinates
void Vector3D::setXYZ( double x2, double y2, double z2 ) {
	x = x2;
	y = y2;
	z = z2;
}

// set the x coordinate
void Vector3D::setX( double x2 ) {
	x = x2;
}

// sets the y coordinate
void Vector3D::setY( double y2 ) {
	y = y2;
}

// sets the z coordinate
void Vector3D::setZ( double z2 ) {
	z = z2;
}

// returns the length (magnetude) of the vector
double Vector3D::length() {
	return sqrt( x*x + y*y + z*z );
}

// returns the dot product of two vectors
double Vector3D::dot( Vector3D v2 ) {
	return x*v2.getX() + y*v2.getY() + z*v2.getZ();
}

// normalizes the vector
void Vector3D::normalize() {
	// find the magnetude of the vector
	double magnetude = length();
	
	// find x, y and z values of normalized vector
	x = x / magnetude;
	y = y / magnetude;
	z = z / magnetude;
}