// Vector2D.cc

// Sam Bradley
// CS 5721

#include "Vector2D.H"
#include <math.h>

// Vector2D constructor
Vector2D::Vector2D( void ) {
	xy[0] = 0;
	xy[1] = 0;
}

// Vector2D consructor
Vector2D::Vector2D( double x, double y ) {
	xy[0] = x;
	xy[1] = y;
}

// returns the x value
double Vector2D::getX() {
	return xy[0];
}

// returns the y value
double Vector2D::getY() {
	return xy[1];
}

// sets the x and y coordiates
void Vector2D::setXY( double x, double y ) {
	xy[0] = x;
	xy[1] = y;
}

// sets the x coordinate
void Vector2D::setX( double x ) {
	xy[0] = x;
}

// sets the y coordinate
void Vector2D::setY( double y ) {
	xy[1] = y;
}

// returns the length (magnetude) of the vecrtor
double Vector2D::length() {
	return sqrt( xy[0]*xy[0] + xy[1]*xy[1] );
}

// returns the dot product of two vectors
double Vector2D::dot( Vector2D v2 ) {
	return xy[0]*v2.getX() + xy[1]*v2.getY();
}

// normalizes the vector
void Vector2D::normalize() {
	// find the magnetude of the vector
	double magnetude = length();
	
	// find x and y values of normalized vector
	xy[0] = xy[0] / magnetude;
	xy[1] = xy[1] / magnetude;
}