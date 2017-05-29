// FrameBuffer.H

// Sam Bradley
// CS 5721

#ifndef FRAMEB
#define FRAMEB

#include "Color.H"
#include "Vector2D.H"
#include "Object3D.H"
#include "Matrix4x4.H"
#include "PI.H"
#include "BSP.H"

typedef class FrameBufferInfo * FrameBuffer;

// FrameBufferInfo is an object that repesents an image
// consisting of pixels. map is is a 2D array representing
// the positive xy plane.

class FrameBufferInfo {

private:

// private data members
int hieght, width, size;
Color* map;
Vector4D *light;
Matrix4x4 mo, mv, mp;
double r, l, t, b, n, f;
Vector3D eye, gaze;
BSPTree *bsp;
int num_lights;
Vector3D diffuse, intensity, ambient;
	
public:

// public class methods
FrameBufferInfo( int x, int y );
int getWidth();
int getHieght();
bool checkXY( const Vector2D& v );
void setColor( int x, int y, int r, int g, int b );
void setBlank();
void saveBuffer( char* filename );
float* bufferData();
void rasterizeline_implicit( const Vector2D& p0, const Vector2D& p1, Color c);
void rasterizeline_parametric( const Vector2D& p0, const Vector2D& p1, const Color& c0, const Color& c1);
void rasterizetriangle(const Vector2D& p0, const Vector2D& p1, const Vector2D& p2,
					   const Color& c0, const Color& c1, const Color& c2);
void rasterizetriangle( const Vector2D& p0, const Vector2D& p1, const Vector2D& p2,
					   const Color& color0, const Color& color1, const Color& color2,
					   const Vector4D& normal0, const Vector4D& normal1, const Vector4D& normal2 );
void rasterizetriangle( Triangle t );
void rasterizeobject( Object3D& object, const Color& c0, const Color& c1, const Color& c2 );
void draw( BSPTree *b, Vector4D eye );
					   
};

#endif