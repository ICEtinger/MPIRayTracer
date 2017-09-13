
#include "Ray.h"
#include <cmath>

Ray::Ray(Vec3* point0, Vec3* dir0) { point = point0; dir = dir0; }

// Returns the point of the first intersection if any, else returns NULL 
Vec3* Ray::intersect(Sphere& sphere) {
	// equation of the sphere is ||x-c||² = r². c = its center, r = its radius.
	// equation of the ray is x = s + td. s = source point, d = direction vector (not necessarily unitary).
	// let v = s-c for simplicity. The intersection is solved by the equation: 
	// (d²/2)t² + (v*d)t + (v²-r²)/2 = 0.

	Vec3* v = point->minus(sphere.getCenter());
	float delta = pow(v->dotProduct(dir), 2) - (dir->squaredMagnitude() * (v->squaredMagnitude() - sphere.getRadius()*sphere.getRadius()));
	if (delta < 0)
		return NULL;
	else {
		float t = (-v->dotProduct(dir) - sqrt(delta)) / dir->squaredMagnitude();
		if (t < 0) // in this case, the line of the ray intersects the sphere, but the ray would have to be moving "backwards" to do so.
			return NULL;
		else
			return (new Vec3(point->getX() + t * dir->getX(), point->getY() + t * dir->getY(), point->getZ() + t * dir->getZ()));
	}
}

// Returns the point of the first intersection if any, else returns NULL. 
// Also sets indexOfSphere to the index of the first intersected sphere (if any).
Vec3* Ray::intersect(Scene* scene, unsigned int& indexOfSphere)
{
	// equation of the sphere is ||x-c||² = r². c = its center, r = its radius.
	// equation of the ray is x = s + td. s = source point, d = direction vector (not necessarily unitary).
	// let v = s-c for simplicity. The intersection is solved by the equation: 
	// (d²/2)t² + (v*d)t + (v²-r²)/2 = 0.
	Vec3* intersection = NULL; // the intersection point to be returned.
	float min_t = FLT_MAX; // the minimum value of t found.
	for (unsigned int i = 0; i < scene->getSpheres().size(); ++i) {
		Vec3* v = point->minus(scene->getSpheres()[i]->getCenter());
		float delta = pow(v->dotProduct(dir), 2) - (dir->squaredMagnitude() * (v->squaredMagnitude() - scene->getSpheres()[i]->getRadius()*scene->getSpheres()[i]->getRadius()));
		if (delta >= 0) {
			float t = (-v->dotProduct(dir) - sqrt(delta)) / dir->squaredMagnitude();
			// t < 0: the line of the ray intersects the sphere, but the ray would have to be moving "backwards" to do so.
			// t > min_t : the ray will intersect another sphere before the current sphere.
			if (t >= 0 && t < min_t) {
				indexOfSphere = i;
				min_t = t;
				intersection = new Vec3(point->getX() + t * dir->getX(), point->getY() + t * dir->getY(), point->getZ() + t * dir->getZ());
			}
		}
	}
	return intersection;
}

void Ray::RGBcolor(Scene* scene, unsigned int indexOfSphere, Vec3* intersection, Vec3& cameraEye, LightSource* lightSource, uchar** PMat, unsigned int i, unsigned int j) {
	Sphere* sphere = scene->getSpheres()[indexOfSphere];
	
	// checks if the ray from the light source intercects another sphere before the sphere currently considered.
	unsigned int tmp = indexOfSphere;
	(new Ray(lightSource->getSource(), intersection->minus(lightSource->getSource())))->intersect(scene,indexOfSphere);
	if (indexOfSphere != tmp) {
		PMat[i][j]     += (unsigned char)(sphere->getB() / 255.0 * sphere->getKa() * lightSource->getAmb()[0]);
		PMat[i][j + 1] += (unsigned char)(sphere->getG() / 255.0 * sphere->getKa() * lightSource->getAmb()[1]);
		PMat[i][j + 2] += (unsigned char)(sphere->getR() / 255.0 * sphere->getKa() * lightSource->getAmb()[2]);
		return;
	}

	// L: the direction vector from the light source to the point on the surface,
	// N: the normal at this point on the surface,
	// R the direction that a perfectly reflected ray of light would take from this point on the surface, and
	// V: the direction pointing towards the viewer(such as a virtual camera).

	// auxiliary vector created: the normal vector (with magnitude 1) of the sphere surface in the intersection point. 
	Vec3* normal = intersection->minusNormalized(sphere->getCenter());
	// = kd * (L.N)/(||L||*||N||)
	float diffusionComponent = - sphere->getKd() * dir->dotProduct(normal)/dir->magnitude();
	if (diffusionComponent < 0)
		diffusionComponent = 0;
	// = ks * [R.V/(||R||*||V||)]^alpha, where R (the reflection of L by the surface with normal N) is R = L - N(2L.N)/||N||²
	Vec3* R = dir->minus(normal->multiplied(2 * dir->dotProduct(normal)));
	float cos = R->cos(cameraEye.minus(intersection));
	float specularComponent = (cos > 0 ? sphere->getKs() * pow(cos, sphere->getAlpha()) : 0);
	
	// changes the current pixel.
	unsigned char colorChange[3] = {
		(unsigned char)(sphere->getB() / 255.0 * ((sphere->getKa() * lightSource->getAmb()[0]) + (diffusionComponent * lightSource->getDiff()[0])) + (specularComponent * lightSource->getSpec()[0])),
		(unsigned char)(sphere->getG() / 255.0 * ((sphere->getKa() * lightSource->getAmb()[1]) + (diffusionComponent * lightSource->getDiff()[1])) + (specularComponent * lightSource->getSpec()[1])),
		(unsigned char)(sphere->getR() / 255.0 * ((sphere->getKa() * lightSource->getAmb()[2]) + (diffusionComponent * lightSource->getDiff()[2])) + (specularComponent * lightSource->getSpec()[2]))
	};
	PMat[i][j]     += colorChange[0];
	PMat[i][j + 1] += colorChange[1];
	PMat[i][j + 2] += colorChange[2];
	
	// now does a recursive call to change the pixel of a possible point intercepted by the reflected light.
	if ((unsigned short)colorChange[0] + colorChange[1] + colorChange[2] > 300) {
		// multiplies the reflected light by 0.75. This tries to be the fastest possible. 
		// Other viable options are: colorChange[i] >>= 1, or colorChange[i] -= (colorChange[i] >> 3), etc.
		colorChange[0] -= (colorChange[0] >> 2);
		colorChange[1] -= (colorChange[1] >> 2);
		colorChange[2] -= (colorChange[2] >> 2);
		Ray ray(intersection, R);
		unsigned int indexOfSphereReflectedRay;
		Vec3* intersectionPoint = ray.intersect(scene, indexOfSphereReflectedRay);
		if (intersectionPoint) {
			(new Ray(lightSource->getSource(), intersectionPoint->minus(lightSource->getSource())))
				->RGBcolor(scene, indexOfSphereReflectedRay, intersectionPoint, cameraEye, new LightSource(intersection,colorChange,colorChange,colorChange), PMat, i, j);
		}
	}
	
}