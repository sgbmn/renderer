outout: main.o Vector2D.o Vector3D.o FrameBuffer.o Color.o Vector4D.o Matrix4x4.o Triangle.o Plane.o Cube.o Pyramid.o Sphere.o BSP.o
	g++ -o output Vector2D.o Vector3D.o main.o FrameBuffer.o Color.o Vector4D.o Matrix4x4.o Triangle.o Plane.o Cube.o Pyramid.o Sphere.o BSP.o

main.o: main.cc Vector2D.H Vector3D.H
	g++ -c -g  main.cc

Sphere.o: Sphere.cc Sphere.H Object3D.H
	g++ -c -g  Sphere.cc

Pyramid.o: Pyramid.cc Pyramid.H Object3D.H
	g++ -c -g  Pyramid.cc

Cube.o: Cube.cc Cube.H Object3D.H
	g++ -c -g  Cube.cc

Plane.o: Plane.cc Plane.H Object3D.H
	g++ -c -g  Plane.cc

Triangle.o: Triangle.cc Triangle.H Object3D.H
	g++ -c -g  Triangle.cc

FrameBuffer.o : FrameBuffer.cc FrameBuffer.H
	g++ -c -g  FrameBuffer.cc

BSP.o: BSP.cc BSP.H
	g++ -c -g  BSP.cc

Color.o : Color.cc Color.H
	g++ -c -g  Color.cc

Matrix4x4.o : Matrix4x4.cc Matrix4x4.H
	g++ -c -g  Matrix4x4.cc

Vector4D.o : Vector4D.cc Vector4D.H
	g++ -c -g  Vector4D.cc

Vector3D.o : Vector3D.cc Vector3D.H
	g++ -c -g  Vector3D.cc

Vector2D.o : Vector2D.cc Vector2D.H
	g++ -c -g  Vector2D.cc
