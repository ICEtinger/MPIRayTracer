
#pragma once
#include "Sphere.h"
#include <vector>

class Scene {

public:
	Scene();
	Scene(std::vector<Sphere*>& spheres0) { spheres = spheres0; }
	Scene(Sphere* s);
	Scene(Sphere* s, Sphere* s1);
	Scene(Sphere* s, Sphere* s1, Sphere* s2);
	Scene(Sphere* s, Sphere* s1, Sphere* s2, Sphere* s3);
	std::vector<Sphere*> getSpheres(); 
	void push(Sphere* sphere);

private:
	// a vector of the spheres present on the scene.
	std::vector<Sphere*> spheres;

};