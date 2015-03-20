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
	Scalar s = sum(mTemp);

	double mse = s.val[0] + s.val[1] + s.val[2] / (double)(img1.channels() * img1.total());
	
	return 10.0 * log10(pow(255,2) / mse);
}

/*
 * getMSSIM function: return SSIM between img1 and img2
 * @param: Mat, Mat
 * @return: double
 */
double getMSSIM(const Mat& img1, const Mat& img2)
{
	const double C1 = 6.5025, C2 = 58.5225;
	
	int d = CV_32F;

	Mat i1, i2;
	img1.convertTo(i1, d);
	img2.convertTo(i2, d);

	Mat img1_2 = i1.mul(i1);
	Mat img2_2 = i2.mul(i2);
	Mat img1_img2 = i1.mul(i2);

	Mat mu1, mu2;
	GaussianBlur(i1, mu1, Size(11, 11), 1.5);
	GaussianBlur(i2, mu2, Size(11, 11), 1.5);
	
	Mat mu1_2 = mu1.mul(mu1);
	Mat mu2_2 = mu2.mul(mu2);
	Mat mu1_mu2 = mu1.mul(mu2);

	Mat sigma1_2, sigma2_2, sigma12;
	
	GaussianBlur(img1_2, sigma1_2, Size(11, 11), 1.5);
	sigma1_2 -= mu1_2;
	GaussianBlur(img2_2, sigma2_2, Size(11, 11), 1.5);
	sigma2_2 -= mu2_2;
	GaussianBlur(img1_img2, sigma12, Size(11, 11), 1.5);
	sigma12 -= mu1_mu2;

	Mat t1, t2, t3;

	t1 = 2 * mu1_mu2 + C1;
	t2 = 2 * sigma12 + C2;
	t3 = t1.mul(t2);

	t1 = mu1_2 + mu2_2 + C1;
	t2 = sigma1_2 + sigma2_2 + C2;
	t1 = t1.mul(t2);

	Mat ssim_map;
	divide(t3, t1, ssim_map);

	Scalar mssim = mean(ssim_map);	
	return ((mssim.val[0] + mssim.val[1] + mssim.val[2]) / 3);
}

/*
 * Main function
 * @param: string(Path for the images), string (Path for reference image), int(Nb images), string(Name for output)
 * @return: NULL
 */
int main(int argc, char *argv[])
{
	Mat imgRef, imgComp;
	stringstream path_o, path_img;
	// Defining paths (input and output)
	path_o << "/home/bibi/Esir/SIA/output/" << argv[4] << ".csv";
	path_img << argv[2];
	// Making a matrix with the img (for processing)
	imgRef = imread((path_img.str()).c_str(), CV_LOAD_IMAGE_UNCHANGED);
	// Opening a .CSV File
	ofstream excelFile((path_o.str().c_str()));
	if(excelFile.is_open()) cout << "File successfully opened !" << endl;
	// Defining titles
	excelFile <<  "Image, PSNR, SSIM" << endl;
	excelFile << flush;
	int nbImg = atoi(argv[3]);
	int i = 1;
	while (i <= nbImg)
	{
		stringstream pathToRead;
		pathToRead << argv[1] << i << ".exr";
		imgComp = imread(pathToRead.str(), CV_LOAD_IMAGE_UNCHANGED);	
		excelFile << i << "," << getPSNR(imgRef, imgComp) << "," << getMSSIM(imgRef, imgComp) * 100 << endl;
		cout << getPSNR(imgRef, imgComp) << endl;
		i++;
	}
	// Closing file
	excelFile.close();
	cout << "File Closed !" << endl;
	return 0;
}
