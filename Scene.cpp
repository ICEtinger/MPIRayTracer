#include "Scene.h"

Scene::Scene() { spheres = std::vector<Sphere*>(); }

Scene::Scene(Sphere* s) { spheres = std::vector<Sphere*>(); push(s); }

Scene::Scene(Sphere* s, Sphere* s1) { spheres = std::vector<Sphere*>(); push(s); push(s1); }

Scene::Scene(Sphere* s, Sphere* s1, Sphere* s2) { spheres = std::vector<Sphere*>(); push(s); push(s1); push(s2); }

Scene::Scene(Sphere* s, Sphere* s1, Sphere* s2, Sphere* s3) { spheres = std::vector<Sphere*>(); push(s); push(s1); push(s2); push(s3); }

std::vector<Sphere*> Scene::getSpheres() { return spheres; }

void Scene::push(Sphere* sphere) { spheres.push_back(sphere); }