
#include "Vec3.h"
#include <cmath>

// Member functions
Vec3::Vec3(float x0, float y0, float z0) {
	x = x0;
	y = y0;
	z = z0;
}

Vec3::Vec3(float x0, float y0, float z0, bool normalize) {
	float magnitude = sqrt(x0*x0 + y0*y0 + z0*z0);
	x = x0/magnitude;
	y = y0/magnitude;
	z = z0/magnitude;
}

Vec3::Vec3() {}

void Vec3::setCoordinates(float x0, float y0, float z0) {
	x = x0;
	y = y0;
	z = z0;
}

float Vec3::getX() { return x; }
float Vec3::getY() { return y; }
float Vec3::getZ() { return z; }

void Vec3::multiply(float m) {
	x *= m;
	y *= m;
	z *= m;
}

void Vec3::add(Vec3& vec3) {
	x += vec3.x;
	y += vec3.y;
	z += vec3.z;
}

void Vec3::add(Vec3* vec3) {
	x += vec3->x;
	y += vec3->y;
	z += vec3->z;
}

void Vec3::normalize() {
	float magnitude = 1.0 / sqrt (x*x + y*y + z*z);
	x *= magnitude;
	y *= magnitude;
	z *= magnitude;
}


Vec3* Vec3::minus(Vec3& vec3) { return (new Vec3(x - vec3.x, y - vec3.y, z - vec3.z)); }

Vec3* Vec3::minus(Vec3* vec3) { return (new Vec3(x - vec3->x, y - vec3->y, z - vec3->z)); }

Vec3* Vec3::minusNormalized(Vec3& vec3) { return (new Vec3(x - vec3.x, y - vec3.y, z - vec3.z, true)); }

Vec3* Vec3::minusNormalized(Vec3* vec3) { return (new Vec3(x - vec3->x, y - vec3->y, z - vec3->z, true)); }

Vec3* Vec3::multiplied(float m) { return (new Vec3(x*m, y*m, z*m)); }

Vec3* Vec3::plus(Vec3& vec3) { return (new Vec3(x + vec3.x, y + vec3.y, z + vec3.z)); }

Vec3* Vec3::plus(Vec3* vec3) { return (new Vec3(x + vec3->x, y + vec3->y, z + vec3->z)); }

float Vec3::magnitude(void) { return sqrt(x*x + y*y + z*z);  }

float Vec3::squaredMagnitude(void) { return x*x + y*y + z*z; }

float Vec3::dotProduct(Vec3& vec3) { return x*vec3.x + y*vec3.y + z*vec3.z; }

float Vec3::dotProduct(Vec3* vec3) { return x*vec3->x + y*vec3->y + z*vec3->z; }

Vec3* Vec3::crossProduct(Vec3& vec3) { return new Vec3(y*vec3.z - z*vec3.y, z*vec3.x - x*vec3.z, x*vec3.y - y*vec3.x); }

Vec3* Vec3::crossProduct(Vec3* vec3) { return new Vec3(y*vec3->z - z*vec3->y, z*vec3->x - x*vec3->z, x*vec3->y - y*vec3->x); }

// cosine between two vectors
float Vec3::cos(Vec3& vec3) { return dotProduct(vec3) / magnitude() / vec3.magnitude(); }

float Vec3::cos(Vec3* vec3) { return dotProduct(vec3) / magnitude() / vec3->magnitude(); }

void Vec3::printSelf() { printf("(%f,%f,%f)\n", x, y, z); };

Vec3::~Vec3() {}