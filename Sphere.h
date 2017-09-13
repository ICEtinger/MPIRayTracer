
#pragma once
#include "Vec3.h"

typedef unsigned char uchar;

class Sphere {

public:
	Sphere(Vec3* center0, float radius0, uchar R0, uchar G0, uchar B0, float ks0, float kd0, float ka0, char alpha0) {
		center = *center0; 
		radius = radius0; 
		R = R0; 
		G = G0; 
		B = B0; 
		ks = ks0; 
		kd = kd0; 
		ka = ka0;
		alpha = alpha0;
	}
	Vec3 getCenter() { return center; }
	float getRadius() { return radius; }
	uchar getR() { return R; }
	uchar getG() { return G; }
	uchar getB() { return B; }
	float getKs() { return ks; }
	float getKd() { return kd; }
	float getKa() { return ka; }
	char getAlpha() { return alpha; }

private:
	Vec3 center;
	float radius;
	// the chars represent respectively Red, Green and Blue. Each colour has an integer value between 0 and 255.
	uchar R, G, B;
	// each materialType has its characteristics defined in the main function. The uchar represents the index identifying each material in an array.
	uchar materialType;
	float ks; // a specular reflection constant, the ratio of reflection of the specular term of incoming light,
	float kd; // a diffuse reflection constant, the ratio of reflection of the diffuse term of incoming light(Lambertian reflectance),
	float ka; // an ambient reflection constant, the ratio of reflection of the ambient term present in all points in the scene rendered, and
	char alpha; // alpha: a shininess constant for this material, which is larger for surfaces that are smoother and more mirror - like. When this constant is large the specular highlight is small.

};