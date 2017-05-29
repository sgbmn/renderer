// main.cpp

// Sam Bradley
// CS 5721

#include <iostream>
#include <math.h>
#include "Vector2D.H"
#include "Vector3D.H"
#include "Vector4D.H"
#include "Matrix4x4.H"
#include "FrameBuffer.H"
#include "Triangle.H"
#include "Object3D.H"
#include "Plane.H"
#include "Cube.H"
#include "Pyramid.H"
#include "Sphere.H"
#include "PI.H"

using namespace std;

main() {
	int width, height;
	width = 650;
	height = 650;
	FrameBuffer buff = new FrameBufferInfo( width, height );
	Vector3D scale;
	Vector3D trans;
	Matrix4x4 mr;
	Matrix4x4 ms;
	Matrix4x4 mt;
	mr.makeRotateZ( 10 );
	Color red( 255, 0, 0 );
	Color green( 0, 255, 0 );
	Color blue( 0, 0, 255 );
	
	Vector4D a(-8,-14,-5,1), b(8,5,-1.8,1), c(4, 5, -3, 1);
	Triangle t1(a,b,c);
	a.setXYZW(14,1,-5,1);
	b.setXYZW(-6,5,-1.2,1);
	c.setXYZW(-7,1,-1.8,1);
	Triangle t2(a,b,c);
	a.setXYZW(-1,-9,-2,1);
	b.setXYZW(3,-6,-2,1);
	c.setXYZW(-20,18,-15,1);
	Triangle t3(a,b,c);
	
	buff->rasterizeobject( t1, green, green, green );
	buff->rasterizeobject( t2, blue, blue, blue );
	buff->rasterizeobject( t3, red, green, blue );
	
	buff->saveBuffer( "image1.PPM" );	
	/*Cube cube;
	
	ms.setIdentity();
	mt.setIdentity();
	scale.setXYZ( 5.0, 5.0, 5.0 );
	trans.setXYZ( 0, 0, -20 );
	ms.makeScale( scale );
	mt.makeTranslate( trans );
	cube.transform( mt*ms );
	
	buff->rasterizeobject( cube, green, green, green );
	
	buff->saveBuffer( "image2.PPM" );*/
}