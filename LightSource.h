
#pragma once
#include "Vec3.h"
typedef unsigned char uchar;

class LightSource {

public:

	LightSource(Vec3* source0, uchar* amb0, uchar* diff0, uchar* spec0);
	LightSource(Vec3* source0, uchar ambR, uchar ambG, uchar ambB, uchar diffR, uchar diffG, uchar diffB, uchar specR, uchar specG, uchar specB);
	Vec3* getSource();
	uchar* getAmb();
	uchar* getDiff();
	uchar* getSpec();

private:
	Vec3* source;
	// represents an array of size 3. [0] = Blue, [1] = Green and [2] = Red. Each colour has a value between 0 and 255.
	// ambient light
	uchar* amb;
	// diffused light
	uchar* diff;
	// specular light
	uchar* spec;

};