// BSP.cc

// Sam Bradley
// CS 5721

#include "BSP.H"
#include <math.h>

BSPTree::BSPTree() {
	positive = 0;
	negative = 0;
}

BSPTree::BSPTree( Triangle t ) {
	triangle = t;
	positive = 0;
	negative = 0;
	/*Vector4D a, b, c;
	triangle.get( a, b, c );
	std::cout << " added triangle " << a.getX() << "," << a.getY() << "," << a.getZ()
			  << " " << b.getX() << "," << b.getY() << "," << b.getZ() 
			  << " " << c.getX() << "," << c.getY() << "," << c.getZ() << endl;*/
}

void BSPTree::add( Triangle t ) {
	Vector4D a, b, c, pa, pb, pc, A, B, n;
	
	triangle.get( a, b, c );
	t.get( pa, pb, pc );
	
	double D;
	n = ( b - a )*( c - a );
	n.normalize();
	D = (-1.0)*n.dot( a );
	
	double fa, fb, fc;
	fa = n.dot( pa - a );
	fb = n.dot( pb - a );
	fc = n.dot( pc - a );

	if( fabs(fa) < .0001 ) { fa = 0.0; }
	if( fabs(fb) < .0001 ) { fb = 0.0; }
	if( fabs(fc) < .0001 ) { fc = 0.0; }
	 
	if( fa <= 0.0 && fb <= 0.0 && fc <= 0.0 ) {
		if( negative == 0 ) {
			negative = new BSPTree( t );
		}
		else {
			negative->add( t );
		}
	}
	else if( fa >= 0 && fb >= 0 && fc >= 0 ) {
		if( positive == 0 ) {
			positive = new BSPTree( t );
		}
		else {
			positive->add( t );
		}
	}
	else {
		Color ca, cb, cc, cA, cB;
		t.getColor( ca, cb, cc );
		
		if( fa*fc >= 0 ) {
			swap( fb, fc );
			swap( pb, pc );
			swap( cb, cc );
			swap( fa, fb );
			swap( pa, pb );
			swap( ca, cb );
		}
		else if( fb * fc >= 0 ) {
			swap( fa, fc );
			swap( pa, pc );
			swap( ca, cc );
			swap( fa, fb );
			swap( pa, pb );
			swap( ca, cb );
		}
		double ta, tb;
		ta = -1.0 * ((n.dot( pa ) + D) / ( n.dot( pc - pa )));
		A = pa + ( pc - pa )*ta;
		cA= ca + ( cc - ca )*ta;
		
		tb = -1.0 * ((n.dot( pb ) + D) / ( n.dot( pc - pb )));
		B = pb + ( pc - pb )*tb;
		cB= cb + ( cc - cb )*tb; 
		
		Triangle T1( pa, pb, A, ca, cb, cA );
		Triangle T2( pb, B, A, cb, cB, cA );
		Triangle T3( A, B, pc, cA, cB, cc );
		
		if( fc >= 0 ) {
			if( negative == 0 ) {
				negative = new BSPTree( T1 );
			}
			else {
				negative->add( T1 );
			}
			negative->add( T2 );

			if( positive == 0 ) {
				positive = new BSPTree( T3 );
			}
			else {
				positive->add( T3 );
			}
		}
	else {
		if( positive ) {
			positive->add( T1 );
		}
		else {
			positive = new BSPTree( T1 );
		}
		positive->add( T2 );
		
		if( negative == 0 ) {
			negative = new BSPTree( T3 );
		}
		else {
			negative->add( T3 );
		}
	}
	}
}

void BSPTree::getTri( Vector4D& p, Vector4D& q, Vector4D& r ) {
	triangle.get( p, q, r );
}

void BSPTree::getTri( Vector4D& p, Vector4D& q, Vector4D& r, Color& c0, Color& c1, Color& c2 ) {
	triangle.get( p, q, r, c0, c1, c2 );
}

void BSPTree::getTri( Vector4D& p, Vector4D& q, Vector4D& r, Color& c0, Color& c1, Color& c2,
					  Vector4D& n0, Vector4D& n1, Vector4D& n2 ) {
	triangle.get( p, q, r, c0, c1, c2, n0, n1, n2 );
	/*std::cout << " drawing triangle " << p.getX() << "," << p.getY() << "," << p.getZ()
			  << " " << q.getX() << "," << q.getY() << "," << q.getZ() 
			  << " " << r.getX() << "," << r.getY() << "," << r.getZ() << endl;*/
}

void BSPTree::getTri( Triangle& t ) {
	t = triangle;
}