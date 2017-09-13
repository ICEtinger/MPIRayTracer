
#pragma once
#include "Vec3.h"
#include "Sphere.h"
#include "Scene.h"
#include "LightSource.h"

typedef unsigned char uchar;

class Camera {

public:
	Camera(Vec3& eye0, Vec3& target0, Vec3& upVector0, float width0, float height0);
	Camera(Vec3& eye0, Vec3& target0, Vec3& upVector0, float squareDimension);
	// the following 2 constructors make an upVector projecting the vector (0,0,1) in the vector pointing from the camera eye to the target.
	Camera(Vec3& eye0, Vec3& target0, float width0, float height0);
	Camera(Vec3& eye0, Vec3& target0, float squareDimension);
	// Assigns values to the matrix of pixels (specified in the opencv library) to build an image.
	void BuildImage(uchar** PMat, Sphere& sphere, LightSource* lightSource, unsigned int startIndex, unsigned int endIndex);
	void BuildImage(uchar** PMat, Sphere& sphere, LightSource* lightSource);
	void BuildImage(uchar** PMat, Scene* scene, LightSource* lightSource, unsigned int startIndex, unsigned int endIndex);
	void BuildImage(uchar** PMat, Scene* scene, LightSource* lightSource);
	void setTarget(Vec3* newTarget);

private:
	// represents the position of the camera.
	Vec3 eye;
	// represents the target looked by the camera.
	Vec3 target;
	// represents the orientation of the camera.
	Vec3 upVector;
	Vec3 rightVector;
	// represents the dimensions of the screen.
	float width;
	float height;

};