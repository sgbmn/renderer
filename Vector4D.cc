// Vecotor4D.cc

// Sam Bradley
// CS 5721

#include "Vector4D.H"
#include <math.h>
#include <iostream>

using namespace std;

// Vector4D constructor
Vector4D::Vector4D( void ) {
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

// Vector4D constructor
Vector4D::Vector4D( double x2, double y2, double z2, double w2 ) {
	x = x2;
	y = y2;
	z = z2;
	w = w2;
}

// returns the x value
double Vector4D::getX() {
	return x;
}

// returns the y value
double Vector4D::getY() {
	return y;
}

// returns the z value
double Vector4D::getZ() {
	return z;
}

// returns  the w value
double Vector4D::getW() {
	return w;
}

// sets the x, y and z coordinates
void Vector4D::setXYZW( double x2, double y2, double z2, double w2 ) {
	x = x2;
	y = y2;
	z = z2;
	w = w2;
}

// set the x coordinate
void Vector4D::setX( double x2 ) {
	x = x2;
}

// sets the y coordinate
void Vector4D::setY( double y2 ) {
	y = y2;
}

// sets the z coordinate
void Vector4D::setZ( double z2 ) {
	z = z2;
}

// sets the value
void Vector4D::setW( double w2 ) {
	w = w2;
}

// returns the length (magnetude) of the vector
double Vector4D::length() {
	return sqrt( x*x + y*y + z*z );
}

// returns the dot product of two vectors
double Vector4D::dot( Vector4D v2 ) {
	return x*v2.getX() + y*v2.getY() + z*v2.getZ() + w*v2.getW();
}

// normalizes the vector
void Vector4D::normalize( void ) {
	// find the magnetude of the vector
	double magnetude = length();
	
	// find x and y values of normalized vectors
	//std::cout << "__________________________________________________" << std::endl;
	//std::cout << x << " " << y << " " << z << " " << w << std::endl; 
	//x = x / magnetude;
	//y = y / magnetude;
	//z = z / magnetude;
	//w = w / magnetude;
	//std::cout << x << " " << y << " " << z << " " << w << std::endl;
	//std::cout << "__________________________________________________" << std::endl;
	*this = *this/length();
	w = 1.0;
}