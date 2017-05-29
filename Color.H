// Color.H

// Sam Bradley
// CS 5721

#ifndef COLOR
#define COLOR

#define RED   0
#define GREEN 1
#define BLUE  2

#include <iostream>
#include "Vector3D.H"

// Color is an object that represents an RGB (red, green, blue)
// color value represnted by 3 integer values

class Color {

private:

// private data members
	int color[3];
	
public:

// public class methods
	Color();
	Color( int r, int g, int b );
	int getRed();
	int getGreen();
	int getBlue();
	void setRed( int c );
	void setGreen( int c );
	void setBlue( int c );
	void setColor( int r, int g, int b );
	int* getColor();
	
// over loaded operators
Color operator + ( Color c2 ) const {
	Color c( color[RED]+c2.getRed(), color[GREEN]+c2.getGreen(), color[BLUE]+c2.getBlue() );
	return c;
}

Color operator - ( Color c2 ) const {
	Color c( color[RED]-c2.getRed(), color[GREEN]-c2.getGreen(), color[BLUE]-c2.getBlue() );
	return c;
}

Color operator * ( Color c2 ) const {
	return Color( color[RED]*c2.getRed(), color[GREEN]*c2.getGreen(), color[BLUE]*c2.getBlue() );
}

Color operator * ( Vector3D c2 ) const {
	return Color( (int)(color[RED]*c2.getX()), (int)(color[GREEN]*c2.getY()), (int)(color[BLUE]*c2.getZ()) );
}

Color operator * ( float scalar ) const {
	float r, g, b;
	r = color[RED]/255.0;
	g = color[GREEN]/255.0;
	b = color[BLUE]/255.0;
	
	r *= scalar;
	g *= scalar;
	b *= scalar;
	
	r *= 255.0;
	g *= 255.0;
	b *= 255.0;
	
	Color c( (int)r, (int)g, (int)b );
	return c;
}
	
};

#endif