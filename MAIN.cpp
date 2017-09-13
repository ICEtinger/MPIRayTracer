
/*
RAY-TRACER
PROGRAM MADE BY ISAK CZERESNIA ETINGER.
Last updated: 27/05/17.
*/

#include "opencv2/highgui.hpp"
#include "Ray.h"
#include "Camera.h"
#include "LightSource.h"
#include "Scene.h"
#include <mpi.h>

using namespace cv;

/* ------------------------------------    PARAMETERS    ------------------------------------ */

int const width = 70; // width of the window to be shown.
int const height = 70; // height of the window to be shown.
Camera* camera = new Camera(Vec3(-50, 0, 0), Vec3(0, 0, 0), width, height);
Scene* spheres = new Scene(std::vector<Sphere*>({
	new Sphere(new Vec3(0, 20, 20), 10.0, 0, 255, 0, 0.3, 0.6, 0.1, 8),
	new Sphere(new Vec3(0, -20, 20), 10.0, 0, 255, 0, 0.6, 0.3, 0.1, 2),
	new Sphere(new Vec3(0, 20, -20), 10.0, 0, 255, 0, 0.0, 0.6, 0.4, 8),
	new Sphere(new Vec3(0, -20, -20), 10.0, 0, 255, 0, 1.0, 0.0, 0.0, 1),
	new Sphere(new Vec3(0, 0, 0), 10.0, 0, 255, 0, 1.0, 0.0, 0.0, 1)
}));
LightSource* lightSource = new LightSource(new Vec3(0, 0, 0), // source point
	new uchar[3]{ 255,255,255 }, new uchar[3]{ 255,255,255 }, new uchar[3]{ 255,255,255 }); // light colors

/* ------------------------------------    MAIN FUNCTION    ------------------------------------ */

void main(int argc, char *argv[]) {

	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	uchar** PMat = new uchar*[width];
	unsigned int triHeight = 3 * height;
	for (unsigned int i = 0; i != width; ++i) {
		PMat[i] = new uchar[triHeight]{ 0 };
	}
	
	uchar** PMatFinal = new uchar*[width];
	camera->BuildImage(PMat, spheres, lightSource, rank * width / size, (rank + 1) * width / size);
	for (unsigned int i = 0; i != width; ++i) {
		PMatFinal[i] = new uchar[triHeight];
		MPI_Reduce(PMat[i], PMatFinal[i], triHeight, MPI_UNSIGNED_CHAR, MPI_SUM, 0, MPI_COMM_WORLD);
	}
	
	if (rank == 0) {
		Mat src = Mat(height, width, CV_8UC3, Scalar(0, 0, 0));
		for (unsigned int i = 0; i != width; ++i) {
			for (unsigned int j = 0; j != height; ++j) {
				unsigned int triJ = j + (j << 1); // = j * 3.
				src.at<Vec3b>(Point(i, j)) = Vec3b(PMatFinal[i][triJ], PMatFinal[i][triJ + 1], PMatFinal[i][triJ + 2]); // (BLUE, Green, RED), (i,j) means i = horizontal, j = vertical.
			}
		}
		/// Create window
		namedWindow("Camera view", WINDOW_AUTOSIZE);
		imshow("Camera view", src);
		waitKey(0);
	}

	MPI_Finalize();
}


