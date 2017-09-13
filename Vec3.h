
#pragma once
#include <string>

// This class represents a vector in a 3-dimensional space, with coordinates x, y, z.
class Vec3 {
public:
	Vec3(float x0, float y0, float z0);
	Vec3(float x0, float y0, float z0, bool normalize);
	Vec3(void);
	void setCoordinates(float x0, float y0, float z0);
	float getX(void);
	float getY(void);
	float getZ(void);
	void multiply(float m);
	void add(Vec3& vec3);
	void add(Vec3* vec3);
	void normalize();
	Vec3* minus(Vec3& vec3);
	Vec3* minus(Vec3* vec3);
	Vec3* minusNormalized(Vec3& vec3);
	Vec3* minusNormalized(Vec3* vec3);
	Vec3* multiplied(float m);
	Vec3* plus(Vec3& vec3);
	Vec3* plus(Vec3* vec3);
	float magnitude(void);
	float squaredMagnitude(void);
	float dotProduct(Vec3& vec3);
	float dotProduct(Vec3* vec3);
	Vec3* crossProduct(Vec3& vec3);
	Vec3* crossProduct(Vec3* vec3);
	float cos(Vec3& vec3);
	float cos(Vec3* vec3);
	void printSelf();

	~Vec3(void);
private:
	float x, y, z;
};