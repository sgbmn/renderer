// Color.cc

// Sam Bradley
// CS 5721

#include "Color.H"
#include <iostream>

// Color constructor (default black)
Color::Color() {
//std::cout << "creating color" << std::endl;
	color[RED] = 0;
	color[GREEN] = 0;
	color[BLUE] = 0;
}

// Color constructor w/ arguments	
Color::Color( int r, int g, int b ) {
	color[RED] = r;
	color[GREEN] = g;
	color[BLUE] = b;
}

// returns the red value of the color
int Color::getRed() {
	return color[RED];
}

// return the green value of the color
int Color::getGreen() {
	return color[GREEN];
}

// returns the blue value of the color
int Color::getBlue() {
	return color[BLUE];
}

// sets the color
void Color::setColor( int r, int g, int b ) {
	color[RED] = r;
	color[GREEN] = g;
	color[BLUE] = b;
}