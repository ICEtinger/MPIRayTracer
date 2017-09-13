
#pragma once
#include "Vec3.h"
#include "Sphere.h"
#include "Scene.h"
#include "LightSource.h"
#include <cstdio>

struct Ray {

public:
	Ray(Vec3* point0, Vec3* dir0);
	Vec3* intersect(Sphere& sphere);
	Vec3* intersect(Scene* scene, unsigned int& indexOfSphere);
	// sets the RGB pixel at position i, j at the pixel matrix PMat.
	void RGBcolor(Scene* scene, unsigned int indexOfSphere, Vec3* intersection, Vec3& cameraEye, LightSource* lightSource, uchar** PMat, unsigned int i, unsigned int j);

private:
	// point represents a point passing through the ray.
	Vec3* point;
	// dir represents the direction of the ray.
	Vec3* dir;

};
