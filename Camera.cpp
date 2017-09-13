
#include "Camera.h"
#include "Ray.h"

Camera::Camera(Vec3& eye0, Vec3& target0, Vec3& upVector0, float width0, float height0) {
	eye = eye0;
	target = target0;
	upVector = upVector0;
	upVector.normalize();
	rightVector = *(upVector.crossProduct(*(eye.minus(target))));
	rightVector.normalize();
	width = width0;
	height = height0;
}

Camera::Camera(Vec3& eye0, Vec3& target0, Vec3& upVector0, float squareDimension) {
	Camera(eye0, target0, upVector0, squareDimension, squareDimension);
}

// Makes an upVector projecting the vector (0,0,1) in the vector pointing from the camera eye to the target.
Camera::Camera(Vec3& eye0, Vec3& target0, float width0, float height0) {
	eye = eye0;
	target = target0;
	rightVector = *( (new Vec3(0,0,1))->crossProduct(*(eye.minus(target))) );
	rightVector.normalize();
	upVector = *( eye.minus(target)->crossProduct(rightVector) );
	upVector.normalize();
	width = width0;
	height = height0;
}

// Makes an upVector projecting the vector(0, 0, 1) in the vector pointing from the camera eye to the target.
Camera::Camera(Vec3& eye0, Vec3& target0, float squareDimension) {
	Camera(eye0, target0, squareDimension, squareDimension);
}

void Camera::BuildImage(uchar** PMat, Sphere& sphere, LightSource* lightSource, unsigned int startIndex, unsigned int endIndex) {
	Vec3* downVector = upVector.multiplied(-1.0/3.0);
	Vec3 corner = *(target.minus(rightVector.multiplied(0.5 * width))->minus(downVector->multiplied(1.5 * height)));
	// uncomment the following lines to see the directions of the vectors used as the camera view.
	//downVector->printSelf();
	//rightVector.printSelf();
	//corner.printSelf();
	//printf("---\n");
	unsigned int triHeight = 3 * height;
	for (unsigned int i = startIndex; i < endIndex; ++i) {
		Vec3 Iter = *corner.plus(rightVector.multiplied(i));
		//Iter.printSelf();
		for (unsigned int j = 0; j < triHeight; j += 3) {
			Vec3* intersectionPoint = (new Ray(&eye, Iter.plus(downVector->multiplied(j))->minus(eye)))->intersect(sphere);
			if (intersectionPoint) {
				(new Ray(lightSource->getSource(), intersectionPoint->minus(lightSource->getSource())))
					->RGBcolor(new Scene(&sphere), 0, intersectionPoint, eye, lightSource, PMat, i, j);
			}
			else {
				PMat[i][j]     = 255;
				PMat[i][j + 1] = 255;
				PMat[i][j + 2] = 255;
			}
		}
	}
}

void Camera::BuildImage(uchar** PMat, Sphere& sphere, LightSource* lightSource) {
	BuildImage(PMat, sphere, lightSource, 0, width);
}

void Camera::BuildImage(uchar** PMat, Scene* scene, LightSource* lightSource, unsigned int startIndex, unsigned int endIndex) {
	Vec3* downVector = upVector.multiplied(-1.0/3.0);
	Vec3 corner = *(target.minus(rightVector.multiplied(0.5 * width))->minus(downVector->multiplied(1.5 * height)));
	// uncomment the following lines to see the directions of the vectors used as the camera view.
	//downVector->printSelf();
	//rightVector.printSelf();
	//corner.printSelf();
	//printf("---\n");
	uchar* blankPixel = new uchar[3]{ 255, 255, 255 };
	unsigned int triHeight = 3 * height;
	for (unsigned int i = startIndex; i != endIndex; ++i) {
		Vec3 Iter = *corner.plus(rightVector.multiplied(i));
		//Iter.printSelf();
		for (unsigned int j = 0; j != triHeight; j += 3) {
			unsigned int indexOfSphere;
			Vec3* intersectionPoint = (new Ray(&eye, Iter.plus(downVector->multiplied(j))->minus(eye)))->intersect(scene, indexOfSphere);
			if (intersectionPoint) {
				(new Ray(lightSource->getSource(), intersectionPoint->minus(lightSource->getSource())))
					->RGBcolor(scene, indexOfSphere, intersectionPoint, eye, lightSource, PMat, i, j);
			}
			else {
				PMat[i][j]     = 255;
				PMat[i][j + 1] = 255;
				PMat[i][j + 2] = 255;
			}
		}
	}
}

void Camera::BuildImage(uchar** PMat, Scene* scene, LightSource* lightSource) {
	BuildImage(PMat, scene, lightSource, 0, width);
}

void Camera::setTarget(Vec3* newTarget) {
	target.setCoordinates(newTarget->getX(), newTarget->getY(), newTarget->getZ());
}
