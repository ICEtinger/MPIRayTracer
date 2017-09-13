
#include "LightSource.h"

LightSource::LightSource(Vec3* source0, uchar* amb0, uchar* diff0, uchar* spec0) {
	source = source0;
	amb = amb0;
	diff = diff0;
	spec = spec0;
}

LightSource::LightSource(Vec3* source0, uchar ambR, uchar ambG, uchar ambB, uchar diffR, 
				uchar diffG, uchar diffB, uchar specR, uchar specG, uchar specB) {
	source = source0;
	amb = new uchar[3] {ambR, ambG, ambB};
	diff = new uchar[3]{diffR, diffG, diffB};
	spec = new uchar[3]{specR, specG, specB};
}

Vec3* LightSource::getSource() { return source; }
uchar* LightSource::getAmb() { return amb; }
uchar* LightSource::getDiff() { return diff; }
uchar* LightSource::getSpec() { return spec; }