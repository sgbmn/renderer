// FrameBuffer.cc

// Sam Bradley
// CS 5721

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "FrameBuffer.H"

using namespace std;

// FrameBufferInfo constructor
FrameBufferInfo::FrameBufferInfo( int x, int y ) {
	hieght = y;
	width = x;
	size = width*hieght;
	
	// allocate memory for bsp tree root
	bsp = 0;
	
	// allocate the lights
	num_lights = 1;
	light = new Vector4D[num_lights];
	light[0].setXYZW( 0.0, 0.0, 1.0, 0 );
	
	diffuse.setXYZ( 1.0, 0.5, 1.0 );
	intensity.setXYZ( 0.5, 0.5, 0.5 );
	ambient.setXYZ( 0.5, 0.5, 0.5 );
	
	// set the initial field of view
	n = -1.0;
	t=tan(70*(PI/180))/abs( (int)n );
	b = -t;
	r = (width/hieght)*t;
	l = -r;
	f = -50;
	
	// set initial eye and gaze
	eye.setXYZ( 0.0, 0.0, 5.0 );
	gaze.setXYZ( 0.0, 0.0, -1.0 );
	
	// set initial mo, mp and mp
	mo.setIdentity();
	mp.setIdentity();
	mv.setIdentity();
	mo.makeOrtho( l, r, t, b, n, f, width, hieght );
	mp.makePerspective( n, f );
	mv.makeEye( eye, gaze );
	
	map = new Color[size];

	setBlank();
	
}

// retuns the width of the buffer
int FrameBufferInfo::getWidth() {
	return width;
}

// return hieght of the buffer
int FrameBufferInfo::getHieght() {
	return hieght;
}

// checks the x and vaulues of a vector to make sure it's in the buffer
bool FrameBufferInfo::checkXY( const Vector2D& v2 ) {
	Vector2D v = v2;
	if( v.getX() > width-1 || v.getX() == 0 ) {
		//cerr << "FRAMEBUFERINFO: You have specified the x coordiate: " << v.getX() 
		//	 << " that is outside the buffer!" << endl;
		return false;
	}
	if( v.getY() > hieght-1 || v.getY() == 0 ) {
		//cerr << "FRAMEBUFERINFO: You have specified a y coordiate not in the buffer!" << endl;
		return false;
	}
	else {
		return true;
	}
} 

// sets the color of a given pixel
void FrameBufferInfo::setColor( int x, int y, int r, int g, int b ) {
	if( y < hieght && y > 0 && x < width && x > 0 )
		map[width*y+x].setColor( r, g, b );
}

// sets the buffer to black
void FrameBufferInfo::setBlank() {
	for( int x=0; x<size; x++ ) {
		map[x].setColor( 255, 255, 255 );
	}
}

// save the buffer as a PPM file
void FrameBufferInfo::saveBuffer( char* filename ) {

	setBlank();
	Vector4D e( eye.getX(), eye.getY(), eye.getZ(), 1 );
	
	draw( bsp, e );
	
	fstream out( filename, ios::out );
	out << "P3\n" << width << " " << hieght << " " << "255" << "\n";
	
	for( int y=hieght-1; y>=0; y-- ) {
		for( int x=0; x<width; x++ ) {
			out << map[width*y+x].getRed();
			out << " ";
			out << map[width*y+x].getGreen();
			out << " ";
			out << map[width*y+x].getBlue();
			out << " ";
		}
		out << "\n";
	}
}

// returns an array of all the colors starting from the origin
float* FrameBufferInfo::bufferData() {
	int size = width*hieght*3;
	float data[size];
	float* r;
	int j = 0;

	for( int y=0; y<hieght; y++ ) {
		for( int x=0; x<width; x++ ) {
			data[j++] = map[width*y+x].getRed();
			data[j++] = map[width*y+x].getGreen();
			data[j++] = map[width*y+x].getBlue();
		}
	}
	
	r = data;
	
	return r;
}

// will draw an implicit line from point p0 to p1 of color c
void FrameBufferInfo::rasterizeline_implicit( const Vector2D& p02, const Vector2D& p12, Color c) {
	Vector2D p0 = p02;
	Vector2D p1 = p12;
	float d;
	int x, y, x0, y0, x1, y1;
	x0 = (int)p0.getX();
	y0 = (int)p0.getY();
	x1 = (int)p1.getX();
	y1 = (int)p1.getY();
	
	// make sure you're drawnig left to right
	if( x0 > x1 ) {
		x0 = (int)p1.getX();
		y0 = (int)p1.getY();
		x1 = (int)p0.getX();
		y1 = (int)p0.getY();
	}
	
	float cx = x1-x0;
	float cy = y1-y0;
	float slope = cy/cx;

	// slope is [0,1) - evaluate in terms of x, possibly incrementing y
	if( slope >= 0 && slope < 1 ) {
		y = y0;
		d = 2*( y0 - y1 )*( x0 + 1 ) + ( x1 - x0 )*( 2*y0 + 1 ) + 2*x0*y1 - 2*x1*y0;
		for( x=x0; x<=x1; x++ ) {
			setColor(x, y, c.getRed(), c.getGreen(), c.getBlue() );
			if( d < 0 ) {
				y++;
				// find f(x+1, y+1)
				d = d + 2*( x1 - x0 ) + 2*( y0 - y1 );
			}
			else {
				// find f(x+1, y)
				d = d + 2*( y0 - y1 );
			}
		}
	}
	// slope is [1,infinity) - evaluate in terms of y, possibly incrementing x
	else if( slope >= 1 ) {
		x = x0;
		d =  ( y0 - y1 )*( 2*x0 + 1 ) + 2*( x1 - x0 )*( y0 + 1 ) + 2*x0*y1 - 2*x1*y0;
		for( y=y0; y<=y1; y++ ) {
			setColor(x, y, c.getRed(), c.getGreen(), c.getBlue() );
			
			if( d > 0 ) {
				x++;
				// find f(x+1, y+1)
				d = d + 2*( x1 - x0 ) + 2*( y0 - y1 );
			}
			else {
				//find f(x, y+1)
				d = d + 2*( x1 - x0 );
			}
		}
	}
	// slope is (-1,0) - evaluate in terms of x, possibly decrementing y
	else if( slope < 0 && slope > -1 ) {
		y = y0;
		d = 2*( y0 - y1 )*( x0 + 1 ) + ( x1 - x0 )*( 2*y0 - 1 ) + 2*x0*y1 - 2*x1*y0;
		for( x=x0; x<=x1; x++ ) {
			setColor(x, y, c.getRed(), c.getGreen(), c.getBlue() );
			if( d > 0 ) {
				y--;
				// find f(x+1, y-1)
				d = d - 2*( x1 - x0 ) + 2*( y0 - y1 );
			}
			else {
				// find f(x+1)
				d = d + 2*( y0 - y1 );
			}
		}
	}
	// slope is (-infinty,-1] - evaluate in terms of y, possibly incrementing x
	else {
		x = x0;
		d = ( y0 - y1 )*( 2*x0 + 1 ) + 2*( x1 - x0 )*( y0 - 1 ) + 2*x0*y1 - 2*x1*y0;
		for( y=y0; y>=y1; y-- ) {
			setColor(x, y, c.getRed(), c.getGreen(), c.getBlue() );
			if( d < 0 ) {
				x++;
				// find f(x+1, y-1)
				d = d - 2*( x1 - x0 ) + 2*( y0 -y1 );
			}
			else {
				// find f(x, y-1)
				d = d - 2*( x1 - x0 );
			}
		}
	}	
}

// will draw a parametric line from point p0 to p1 of color c0 to c1
void FrameBufferInfo::rasterizeline_parametric( const Vector2D& p02, const Vector2D& p12, const Color& c0, const Color& c1) {
	Vector2D p0 = p02;
	Vector2D p1 = p12;
	float x0, y0, x1, y1;
	x0 = p0.getX();
	y0 = p0.getY();
	x1 = p1.getX();
	y1 = p1.getY();
	
	Color start_c = c0;
	Color end_c   = c1;
	
	float cx = x1-x0;
	float cy = y1-y0;
	float slope = cy/cx;	

	if( slope < -1 || slope > 1 ) {
		int y;
		float x, t;
		
		// make sure y is increasing
		if( y0 > y1 ) {
			x0 = p1.getX();
			y0 = p1.getY();
			x1 = p0.getX();
			y1 = p0.getY();
			start_c = c1;
			end_c   = c0;
		}
	
		float cr = ( end_c.getRed() - start_c.getRed() )/( y1-y0 );
		float cg = ( end_c.getGreen() - start_c.getGreen() )/( y1- y0 );
		float cb = ( end_c.getBlue() - start_c.getBlue() )/( y1-y0 );
		
		float r = start_c.getRed();
		float g = start_c.getGreen();
		float b = start_c.getBlue();
	
		for( y=(int)(y0+.5); y<=(int)(y1+.5); y++ ) {
			t = ( y-y0 )/( y1-y0 );
			x = x0 + t*( x1-x0 );
			setColor( (int)(x+.5), y, (int)r, (int)g, (int)b );
			r+=cr;
			g+=cg;
			b+=cb;
		}
	}
	else {
		int x;
		float y, t;
		
		// make sure x is increasing
		if( x0 > x1 ) {
			x0 = p1.getX();
			y0 = p1.getY();
			x1 = p0.getX();
			y1 = p0.getY();
			start_c = c1;
			end_c   = c0;
		}
	
		float cr = ( end_c.getRed() - start_c.getRed() )/( x1-x0 );
		float cg = ( end_c.getGreen() - start_c.getGreen() )/( x1-x0 );
		float cb = ( end_c.getBlue() - start_c.getBlue() )/( x1-x0 );
		
		float r = start_c.getRed();
		float g = start_c.getGreen();
		float b = start_c.getBlue();
		
		for( x=(int)(x0+.5); x<=(int)(x1+.5); x++ ) {
			t = ( x-x0 )/( x1-x0 );
			y = y0 + t*( y1-y0 );
			setColor( x, (int)(y+.5), (int)r, (int)g, (int)b );
			r+=cr;
			g+=cg;
			b+=cb;
		}
	}

}
	
void FrameBufferInfo::rasterizetriangle(const Vector2D& p02, const Vector2D& p12, const Vector2D& p22,
										const Color& c0, const Color& c1, const Color& c2) {
	
	Vector2D p0 = p02;
	Vector2D p1 = p12;
	Vector2D p2 = p22;									
	checkXY( p0 );
	checkXY( p1 );
	checkXY( p2 );
							
	int x, y;
	float alpha, beta, gamma, x0, y0, x1, y1, x2, y2, xmin, xmax, ymin, ymax, alphaoff, betaoff, gammaoff;

	x0 = (float)p0.getX(); y0 = (float)p0.getY();
	x1 = (float)p1.getX(); y1 = (float)p1.getY();
	x2 = (float)p2.getX(); y2 = (float)p2.getY();
	
	// find x and y min and max
	xmin = x0;
	if( x1 < xmin ) xmin = x1;
	if( x2 < xmin ) xmin = x2;
	xmax = x0;
	if( x1 > xmax ) xmax = x1;
	if( x2 > xmax ) xmax = x;
	ymin = y0;
	if( y1 < ymin ) ymin = y1;
	if( y2 < ymin ) ymin = y2;
	ymax = y0;
	if( y1 > ymax ) ymax = y1;
	if( y2 > ymax ) ymax = y2;
	
	float fa = ( y1 - y2 )*x0 + ( x2 - x1 )*y0 + x1*y2 - x2*y1;
	float fb = ( y2 - y0 )*x1 + ( x0 - x2 )*y1 + x2*y0 - x0*y2;
	float fg = ( y0 - y1 )*x2 + ( x1 - x0 )*y2 + x0*y1 - x1*y0;

	for( x=(int)xmin; x<=(int)xmax; x++ ) {
		for( y=(int)ymin; y<=(int)ymax; y++ ) {
			// compute functions
			alpha = ( ( y1 - y2 )*x + ( x2 - x1 )*y + x1*y2 - x2*y1 ) / fa;
			alphaoff = fb*( ( y1 - y2 )*(-1) + ( x2 - x1 )*(-2) + x1*y2 - x2*y1 );
					
			beta = ( ( y2 - y0 )*x + ( x0 - x2 )*y + x2*y0 - x0*y2 ) / fb;
			betaoff = fb*( ( y2 - y0 )*(-1) + ( x0 - x2 )*(-2) + x2*y0 - x0*y2 );
				   
			gamma = ( ( y0 - y1 )*x + ( x1 - x0 )*y + x0*y1 - x1*y0 ) / fg;
			gammaoff = fg*( ( y0 - y1 )*(-1) + ( x1 - x0 )*(-2) + x0*y1 - x1*y0 );
				   
			if( ( alpha > 0.0 || ( alpha == 0.0 && alphaoff > 0.0 ) ) &&
				( beta > 0.0 || ( beta == 0.0 && betaoff > 0.00 ) )&&
				( gamma > 0.0 || ( gamma == 0.0 && gammaoff > 0.0 ) ) ) {
				Color color( ((c0*alpha) + (c1*beta) + (c2*gamma)).getRed(),
							 ((c0*alpha) + (c1*beta) + (c2*gamma)).getGreen(),
							 ((c0*alpha) + (c1*beta) + (c2*gamma)).getBlue() );
				setColor( x, y, color.getRed(), color.getGreen(), color.getBlue() );
			}

		}
	}
							
}

void FrameBufferInfo::rasterizetriangle( Triangle t ) {
	
	Vector4D a, b, c, n0, n1, n2;
	Vector2D p0, p1, p2;
	Color c0, c1, c2;
	t.get( a, b, c, c0, c1, c2, n0, n1, n2 );
	
	a = mo*mp*mv*a;
	b = mo*mp*mv*b;
	c = mo*mp*mv*c;
		
	a = a/a.getW();
	p0.setXY( a.getX(), a.getY() );
	b = b/b.getW();
	p1.setXY( b.getX(), b.getY() );
	c = c/c.getW();
	p2.setXY( c.getX(), c.getY() );
							
	int x, y;
	float alpha, beta, gamma, x0, y0, x1, y1, x2, y2, xmin, xmax, ymin, ymax, alphaoff, betaoff, gammaoff;

	x0 = (float)p0.getX(); y0 = (float)p0.getY();
	x1 = (float)p1.getX(); y1 = (float)p1.getY();
	x2 = (float)p2.getX(); y2 = (float)p2.getY();
	
	// find x and y min and max
	xmin = x0;
	if( x1 < xmin ) xmin = x1;
	if( x2 < xmin ) xmin = x2;
	xmax = x0;
	if( x1 > xmax ) xmax = x1;
	if( x2 > xmax ) xmax = x;
	ymin = y0;
	if( y1 < ymin ) ymin = y1;
	if( y2 < ymin ) ymin = y2;
	ymax = y0;
	if( y1 > ymax ) ymax = y1;
	if( y2 > ymax ) ymax = y2;
	
	float fa = ( y1 - y2 )*x0 + ( x2 - x1 )*y0 + x1*y2 - x2*y1;
	float fb = ( y2 - y0 )*x1 + ( x0 - x2 )*y1 + x2*y0 - x0*y2;
	float fg = ( y0 - y1 )*x2 + ( x1 - x0 )*y2 + x0*y1 - x1*y0;

	for( x=(int)xmin; x<=(int)xmax; x++ ) {
		for( y=(int)ymin; y<=(int)ymax; y++ ) {
			// compute functions
			alpha = ( ( y1 - y2 )*x + ( x2 - x1 )*y + x1*y2 - x2*y1 ) / fa;
			alphaoff = fb*( ( y1 - y2 )*(-1) + ( x2 - x1 )*(-2) + x1*y2 - x2*y1 );
					
			beta = ( ( y2 - y0 )*x + ( x0 - x2 )*y + x2*y0 - x0*y2 ) / fb;
			betaoff = fb*( ( y2 - y0 )*(-1) + ( x0 - x2 )*(-2) + x2*y0 - x0*y2 );
				   
			gamma = ( ( y0 - y1 )*x + ( x1 - x0 )*y + x0*y1 - x1*y0 ) / fg;
			gammaoff = fg*( ( y0 - y1 )*(-1) + ( x1 - x0 )*(-2) + x0*y1 - x1*y0 );
				   
			if( ( alpha > 0.0 || ( alpha == 0.0 && alphaoff > 0.0 ) ) &&
				( beta > 0.0 || ( beta == 0.0 && betaoff > 0.00 ) )&&
				( gamma > 0.0 || ( gamma == 0.0 && gammaoff > 0.0 ) ) ) {
				Color color( ((c0*alpha) + (c1*beta) + (c2*gamma)).getRed(),
							 ((c0*alpha) + (c1*beta) + (c2*gamma)).getGreen(),
							 ((c0*alpha) + (c1*beta) + (c2*gamma)).getBlue() );
				setColor( x, y, color.getRed(), color.getGreen(), color.getBlue() );
			}

		}
	}
							
}
void FrameBufferInfo::rasterizetriangle(const Vector2D& p02, const Vector2D& p12, const Vector2D& p22,
										const Color& color0, const Color& color1, const Color& color2,
										const Vector4D& normal0, const Vector4D& normal1, const Vector4D& normal2 ) {
	
	Color c0 = color0;
	Color c1 = color1;
	Color c2 = color2;
	Vector4D n0 = normal0;
	Vector4D n1 = normal1;
	Vector4D n2 = normal2;
	Vector2D p0 = p02;
	Vector2D p1 = p12;
	Vector2D p2 = p22;									
	checkXY( p0 );
	checkXY( p1 );
	checkXY( p2 );
	
	//for( int dumb=0; dumb<num_lights; dumb++ ) {
	//	;
	//}
	c0 = c0*diffuse*( ambient + intensity*max( 0.0, n0.dot( light[0] ) ) ); 
	c1 = c1*diffuse*( ambient + intensity*max( 0.0, n1.dot( light[0] ) ) );
	c2 = c2*diffuse*( ambient + intensity*max( 0.0, n2.dot( light[0] ) ) );
							
	int x, y;
	float alpha, beta, gamma, x0, y0, x1, y1, x2, y2, xmin, xmax, ymin, ymax, alphaoff, betaoff, gammaoff;

	x0 = (float)p0.getX(); y0 = (float)p0.getY();
	x1 = (float)p1.getX(); y1 = (float)p1.getY();
	x2 = (float)p2.getX(); y2 = (float)p2.getY();
	
	// find x and y min and max
	xmin = x0;
	if( x1 < xmin ) xmin = x1;
	if( x2 < xmin ) xmin = x2;
	xmax = x0;
	if( x1 > xmax ) xmax = x1;
	if( x2 > xmax ) xmax = x;
	ymin = y0;
	if( y1 < ymin ) ymin = y1;
	if( y2 < ymin ) ymin = y2;
	ymax = y0;
	if( y1 > ymax ) ymax = y1;
	if( y2 > ymax ) ymax = y2;
	
	float fa = ( y1 - y2 )*x0 + ( x2 - x1 )*y0 + x1*y2 - x2*y1;
	float fb = ( y2 - y0 )*x1 + ( x0 - x2 )*y1 + x2*y0 - x0*y2;
	float fg = ( y0 - y1 )*x2 + ( x1 - x0 )*y2 + x0*y1 - x1*y0;

	for( x=(int)xmin; x<=(int)xmax; x++ ) {
		for( y=(int)ymin; y<=(int)ymax; y++ ) {
			// compute functions
			alpha = ( ( y1 - y2 )*x + ( x2 - x1 )*y + x1*y2 - x2*y1 ) / fa;
			alphaoff = fb*( ( y1 - y2 )*(-1) + ( x2 - x1 )*(-2) + x1*y2 - x2*y1 );
					
			beta = ( ( y2 - y0 )*x + ( x0 - x2 )*y + x2*y0 - x0*y2 ) / fb;
			betaoff = fb*( ( y2 - y0 )*(-1) + ( x0 - x2 )*(-2) + x2*y0 - x0*y2 );
				   
			gamma = ( ( y0 - y1 )*x + ( x1 - x0 )*y + x0*y1 - x1*y0 ) / fg;
			gammaoff = fg*( ( y0 - y1 )*(-1) + ( x1 - x0 )*(-2) + x0*y1 - x1*y0 );
				   
			if( ( alpha > 0.0 || ( alpha == 0.0 && alphaoff > 0.0 ) ) &&
				( beta > 0.0 || ( beta == 0.0 && betaoff > 0.00 ) )&&
				( gamma > 0.0 || ( gamma == 0.0 && gammaoff > 0.0 ) ) ) {
				Color color( ((c0*alpha) + (c1*beta) + (c2*gamma)).getRed(),
							 ((c0*alpha) + (c1*beta) + (c2*gamma)).getGreen(),
							 ((c0*alpha) + (c1*beta) + (c2*gamma)).getBlue() );
				setColor( x, y, color.getRed(), color.getGreen(), color.getBlue() );
			}

		}
	}
							
}

void FrameBufferInfo::rasterizeobject( Object3D& object, const Color& c0, const Color& c1, const Color& c2 ){
	Vector4D v0, v1, v2;
	Vector2D p0, p1, p2;
	Triangle t;
	int triangles = object.getNumTri();
	for( int i=0; i<triangles; i++ ) {
		object.getTri( i, v0, v1, v2 );
		t.set( v0, v1, v2, c0, c1, c2 );
		if( bsp == 0 ) {
			bsp = new BSPTree( t );
		}
		else {
			bsp->add( t );
		}
	}
}

 void FrameBufferInfo::draw( BSPTree *node, Vector4D e ) {
	if( node == 0 ) {
		return;
	}
	else {
		Color c0, c1, c2;
		Vector4D n, a, b, c, n0, n1, n2;
		Vector2D p0, p1, p2;
		double fe;
		
		node->getTri( a, b, c, c0, c1, c2, n0, n1, n2 );
		Triangle t( a, b, c, c0, c1, c2 );
		node->getTri( t );
		
		n = ( b - a )*( c - a );
		n.normalize();
		fe = n.dot( e - a );
		a = mo*mp*mv*a;
		b = mo*mp*mv*b;
		c = mo*mp*mv*c;
		
		a = a/a.getW();
		p0.setXY( a.getX(), a.getY() );
		b = b/b.getW();
		p1.setXY( b.getX(), b.getY() );
		c = c/c.getW();
		p2.setXY( c.getX(), c.getY() );
		
		if ( fe < 0 ) {
			draw( node->positive, e );
			//rasterizetriangle( p0, p1, p2, c0, c1, c2 );
			/*std::cout << " drawing triangle " << a.getX() << "," << a.getY() << "," << a.getZ()
			  << " " << b.getX() << "," << b.getY() << "," << b.getZ() 
			  << " " << c.getX() << "," << c.getY() << "," << c.getZ() << endl;*/
			rasterizetriangle( p0, p1, p2, c0, c1, c2, n0, n1, n2 );
			//rasterizetriangle( t );
			draw( node->negative, e );
		}
		else {
			draw( node->negative, e );
			//rasterizetriangle( p0, p1, p2, c0, c1, c2 );
			/*std::cout << " drawing triangle " << a.getX() << "," << a.getY() << "," << a.getZ()
			  << " " << b.getX() << "," << b.getY() << "," << b.getZ() 
			  << " " << c.getX() << "," << c.getY() << "," << c.getZ() << endl;*/
			rasterizetriangle( p0, p1, p2, c0, c1, c2, n0, n1, n2 );
			//rasterizetriangle( t );
			draw( node->positive, e );
		}
	}
 }