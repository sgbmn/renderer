// Vector2D.H

// Sam Bradley
// CS 5721

#ifndef VECTOR2D
#define VECTOR2D

// Vecotor2DInfo is an object that represents a 2-dimentional
// vector represented by an x and y corrdinate

class Vector2D {

private:

// private data members
double xy[2]; // x and y coordinates

public:

// public class methods
Vector2D( void );
Vector2D( double x, double y); // ctor
double  getX();
double  getY();
void	setXY( double x, double y );
void    setX( double x );
void    setY( double y );
double  length();
double  dot( Vector2D );

void normalize();

// overriden functions
Vector2D operator + ( Vector2D v2 ) const {
	Vector2D v( xy[0]+v2.getX(), xy[1]+v2.getY() );
	return v;
}
Vector2D operator - ( Vector2D v2 ) const {
	Vector2D v( xy[0]-v2.getX(), xy[1]+v2.getY() );
	return v;
}
Vector2D operator * ( Vector2D v2 ) const{
	Vector2D v( xy[0]*v2.getX(), xy[1]*v2.getX() );
	return v;
}
Vector2D operator * ( double scalar ) const {
	Vector2D v( xy[0]*scalar, xy[1]*scalar );
	return v;
}
//Vector2D operator = ( Vector2D v2 ) const {
//	Vector2D v = new Vector2DInfo( v2->getX(), v2->getX() );
//	return v;
//}

};

#endif