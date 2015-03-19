/* #######################
   ### MITSUBA - TESTS ###
	 #### Brieuc DANIEL ####
	 #######################
*/
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace cv;

/*
 * getPSNR function: return PSNR between img1 and img2
 * @param: Mat, Mat
 * @return: double
 */
double getPSNR(const Mat& img1, const Mat& img2)
{
	Mat mTemp = img1 - img2;
	mTemp = mTemp.mul(mTemp);
	Scalar = sum(mTemp);

	double mse = s.val[0] + s.val[1] + s.val[2] / (double)(img1.channels() * img1.total());
	
	return 10.0 * log10(pow(255,2) / mse);
}

/*
 * getSSIM function: return SSIM between img1 and img2
 * @param: Mat, Mat
 * @return: double
 */
double getSSIM(const Mat& img1, const Mat& img2)
{

}

/*
 * Main function
 * @param: string(Path for the images), int(Nb images), string(Name for output)
 * @return: NULL
 */
int main(int argc, char *argv[])
{
	Mat imgRef, imgComp;
	stringstream path_o, path_img;
	// Defining paths (input and output)
	path_o << "/home/bibi/Esir/SIA/output/" << argv[3] << ".csv";
	path_img << argv[1] << argv[2] << ".exr";
	// Making a matrix with the img (for processing)
	imgRef = imread((path_img.str()).c_str(), CV_LOAD_IMAGE_UNCHANGED);
	// Opening a .CSV File
	ofstream excelFile((path_o.str().c_str()));
	if(excelFile.is_open()) cout << "File successfully opened !" << endl;
	// Defining titles
	excelFile <<  "Image, PSNR, SSIM" << endl;
	excelFile << flush;
	int nbImg = atoi(argv[2]);
	int i = 1;
	while (i < nbImg)
	{
		stringstream pathToRead;
		pathToRead << argv[1] << i << ".exr";
		imgComp = imread(pathToRead.str(), CV_LOAD_IMAGE_UNCHANGED);
		excelFile << i << "," << getPSNR(imgRef, imgComp) << endl;
		cout << getPSNR(imgRef, imgComp) << endl;
		i++;
	}
	// Closing file
	excelFile.close();

	return 0;
}
