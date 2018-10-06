// Opencvtest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include<fstream>
#include<string.h>
#include <time.h>
#include <math.h>

using namespace cv;
using namespace std;


void GaussianNoise(Mat originimage, Mat gaussianimage, int amplitude);
double Normal(void);
void SaltAndPepperNoise(Mat originimage, Mat saltandpepperimage, double probability);
void BoxFilter(Mat noisedimage, Mat resultimage, int size);
void MedianFilter(Mat noisedimage, Mat resultimage, int size);
void BubbleSort(int list[]);
void Dilation(Mat originimage, Mat resultimage);
void Erosion(Mat originimage, Mat resultimage);
void Opening(Mat originimage, Mat resultimage);
void Closing(Mat originimage, Mat resultimage);
void OpenThenClose(Mat noisedimage, Mat resultimage);
void CloseThenOpen(Mat noisedimage, Mat resultimage);


int _tmain(int argc, _TCHAR* argv[])
{
	Mat image = imread("lena.bmp");
	Mat grayimage;
	int pixel = 0;
	cvtColor(image,grayimage, CV_BGR2GRAY);

	Mat gaussianimage10 = grayimage.clone();
	Mat gaussianimage30 = grayimage.clone();
	Mat saltandpepperimage01 = grayimage.clone();
	Mat saltandpepperimage005 = grayimage.clone();

	Mat boximage3g1 = grayimage.clone();
	Mat boximage3g3 = grayimage.clone();
	Mat boximage5g1 = grayimage.clone();
	Mat boximage5g3 = grayimage.clone();

	Mat boximage3sap005 = grayimage.clone();
	Mat boximage3sap01 = grayimage.clone();
	Mat boximage5sap005 = grayimage.clone();
	Mat boximage5sap01 = grayimage.clone();
	
	Mat medianimage3g1 = grayimage.clone();
	Mat medianimage3g3 = grayimage.clone();
	Mat medianimage5g1 = grayimage.clone();
	Mat medianimage5g3 = grayimage.clone();

	Mat medianimage3sap005 = grayimage.clone();
	Mat medianimage3sap01 = grayimage.clone();
	Mat medianimage5sap005 = grayimage.clone();
	Mat medianimage5sap01 = grayimage.clone();

	Mat openthencloseg1 = grayimage.clone();
	Mat openthencloseg3 = grayimage.clone();
	Mat openthenclosesap005 = grayimage.clone();
	Mat openthenclosesap01 = grayimage.clone();

	Mat closethenopeng1 = grayimage.clone();
	Mat closethenopeng3 = grayimage.clone();
	Mat closethenopensap005 = grayimage.clone();
	Mat closethenopensap01 = grayimage.clone();
	
	// make noise
	GaussianNoise(grayimage, gaussianimage10, 10);
	imwrite("gaussianimage10.jpg",gaussianimage10);
	GaussianNoise(grayimage, gaussianimage30, 30);
	imwrite("gaussianimage30.jpg",gaussianimage30);
	SaltAndPepperNoise(grayimage, saltandpepperimage005, 0.05);
	imwrite("saltandpeppernoise 0.05.jpg",saltandpepperimage005);
	SaltAndPepperNoise(grayimage, saltandpepperimage01, 0.1);
	imwrite("saltandpeppernoise 0.1.jpg",saltandpepperimage01);

	// noise clean

	// Box Filter
	BoxFilter(gaussianimage10,boximage3g1,3);
	imwrite("box3 gau10.jpg",boximage3g1);
	BoxFilter(gaussianimage30,boximage3g3,3);
	imwrite("box3 gau30.jpg",boximage3g3);
	BoxFilter(gaussianimage10,boximage5g1,5);
	imwrite("box5 gau10.jpg",boximage5g1);
	BoxFilter(gaussianimage30,boximage5g3,5);
	imwrite("box5 gau30.jpg",boximage5g3);
	BoxFilter(saltandpepperimage005,boximage3sap005,3);
	imwrite("box3 sap0.05.jpg",boximage3sap005);
	BoxFilter(saltandpepperimage01,boximage3sap01,3);
	imwrite("box3 sap0.1.jpg",boximage3sap01);
	BoxFilter(saltandpepperimage005,boximage5sap005,5);
	imwrite("box5 sap0.05.jpg",boximage5sap005);
	BoxFilter(saltandpepperimage01,boximage5sap01,5);
	imwrite("box5 sap0.1.jpg",boximage5sap01);

	// Median Filter
	MedianFilter(gaussianimage10,medianimage3g1,3);
	imwrite("median3 gau10.jpg",medianimage3g1);
	MedianFilter(gaussianimage30,medianimage3g3,3);
	imwrite("median3 gau30.jpg",medianimage3g3);
	MedianFilter(gaussianimage10,medianimage5g1,5);
	imwrite("median5 gau10.jpg",medianimage5g1);
	MedianFilter(gaussianimage30,medianimage5g3,5);
	imwrite("median5 gau30.jpg",medianimage5g3);
	MedianFilter(saltandpepperimage005,medianimage3sap005,3);
	imwrite("median3 sap0.05.jpg",medianimage3sap005);
	MedianFilter(saltandpepperimage01,medianimage3sap01,3);
	imwrite("median3 sap0.1.jpg",medianimage3sap01);
	MedianFilter(saltandpepperimage005,medianimage5sap005,5);
	imwrite("median5 sap0.05.jpg",medianimage5sap005);
	MedianFilter(saltandpepperimage01,medianimage5sap01,5);
	imwrite("median5 sap0.1.jpg",medianimage5sap01);

	// Opening then Closing Filter
	OpenThenClose(gaussianimage10,openthencloseg1);
	imwrite("openthenclose g1.jpg",openthencloseg1);
	OpenThenClose(gaussianimage30,openthencloseg3);
	imwrite("openthenclose g3.jpg",openthencloseg3);
	OpenThenClose(saltandpepperimage005,openthenclosesap005);
	imwrite("openthenclose sap0.05.jpg",openthenclosesap005);
	OpenThenClose(saltandpepperimage01,openthenclosesap01);
	imwrite("openthenclose sap0.1.jpg",openthenclosesap01);

	// Closing then Opening Filter
	CloseThenOpen(gaussianimage10,closethenopeng1);
	imwrite("closethenopen g1.jpg",closethenopeng1);
	CloseThenOpen(gaussianimage30,closethenopeng3);
	imwrite("closethenopen g3.jpg",closethenopeng3);
	CloseThenOpen(saltandpepperimage005,closethenopensap005);
	imwrite("closethenopen sap0.05.jpg",closethenopensap005);
	CloseThenOpen(saltandpepperimage01,closethenopensap01);
	imwrite("closethenopen sap0.1.jpg",closethenopensap01);


	waitKey(0);
	return 0;
}

void GaussianNoise(Mat originimage, Mat gaussianimage, int amplitude){
	for(int i=0; i<originimage.rows; i++){
		for(int j=0; j<originimage.cols; j++){
			double random = Normal();
			int noise = (int)(amplitude * random);
			int pixel = originimage.at<uchar>(i,j) + noise;

			if(pixel>255){
				gaussianimage.at<uchar>(i,j) = 255;
			}else if(pixel<0){
				gaussianimage.at<uchar>(i,j) = 0;
			}else{
				gaussianimage.at<uchar>(i,j) = pixel;
			}
		}
	}
}

double Normal(void){
	int a;
	double b = 0;
	for(a=0; a<12; a++){
		b += ( ( double ) rand() / RAND_MAX );
	}
	return b-6;
}

void SaltAndPepperNoise(Mat originimage, Mat saltandpepperimage, double probability){
	for(int i=0; i<originimage.rows; i++){
		for(int j=0; j<originimage.cols; j++){
			double val = (double)rand() / RAND_MAX;
			
			if(val<probability){
				saltandpepperimage.at<uchar>(i,j) = 0;
			}else if(val>(1-probability)){
				saltandpepperimage.at<uchar>(i,j) = 255;
			}else{
				saltandpepperimage.at<uchar>(i,j) = originimage.at<uchar>(i,j);
			}
		}
	}
}

void BoxFilter(Mat noisedimage, Mat resultimage, int size){
	for(int i=0; i<noisedimage.rows; i++){
		for(int j=0; j<noisedimage.cols; j++){
			int top = 0;
			int bottom = 0;
			int left = 0;
			int right = 0;
			if(size==3){
				top = i-1;
				bottom = i+2;
				left = j-1;
				right = j+2;
				if(i==0){
					top = i;
				}
				if(i==noisedimage.rows-1){
					bottom = i+1;
				}
				if(j==0){
					left = j;
				}
				if(j==noisedimage.cols-1){
					right = j+1;
				}
			}else{
				// size==5
				top = i-2;
				bottom = i+3;
				left = j-2;
				right = j+3;
				if(i==0){
					top = i;
				}
				if(i==1){
					top = i-1;
				}
				if(i==noisedimage.rows-1){
					bottom = i+1;
				}
				if(i==noisedimage.rows-2){
					bottom = i+2;
				}
				if(j==0){
					left = j;
				}
				if(j==1){
					left = j-1;
				}
				if(j==noisedimage.cols-1){
					right = j+1;
				}
				if(j==noisedimage.cols-2){
					right = j+2;
				}
			}
			
			int countpixel = 0;
			int countnumber = 0;
			for(int k=top; k<bottom; k++){
				for(int l=left;l<right; l++){
					countpixel = countpixel + noisedimage.at<uchar>(k,l);
					countnumber++;
				}
			}
			countpixel = countpixel/countnumber;
			resultimage.at<uchar>(i,j) = countpixel;
		}
	}
}

void MedianFilter(Mat noisedimage, Mat resultimage, int size){
	if(size==3){
		for(int i=1; i<noisedimage.rows-1; i++){
			for(int j=1; j<noisedimage.cols-1; j++){
				int arrayindex = 0;
				int thearray[9] = {0,0,0,0,0,0,0,0,0};
				for(int k=i-1; k<i+2; k++){
					for(int l=j-1; l<j+2; l++){
						thearray[arrayindex] = noisedimage.at<uchar>(k,l);
						arrayindex++;
					}
				}
				BubbleSort(thearray);
				resultimage.at<uchar>(i,j) = thearray[4];
			}
		}
	}else{
		for(int i=2; i<noisedimage.rows-2; i++){
			for(int j=2; j<noisedimage.cols-2; j++){
				int arrayindex = 0;
				int thearray[25] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0};
				for(int k=i-2; k<i+3; k++){
					for(int l=j-2; l<j+3; l++){
						thearray[arrayindex] = noisedimage.at<uchar>(k,l);
						arrayindex++;
					}
				}
				BubbleSort(thearray);
				resultimage.at<uchar>(i,j) = thearray[12];
			}
		}
	}
}

void BubbleSort(int list[]){
	int size = sizeof(list);
	for(int i=0; i<size; i++){
		for(int j=0; j<size-i; j++){
			if(list[j]>list[j+1]){
				int temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
			//cout<<list[j]<<endl;
		}
	}
}

void Dilation(Mat originimage, Mat resultimage){
	for(int i=2; i<originimage.rows-2; i++){
		for(int j=2; j<originimage.cols-2; j++){
			int largest = 0;
			//find largest
			for(int k=0; k<5; k++){
				for(int l=0; l<5; l++){
					if((k==0&&l==0)||(k==0&&l==4)||(k==4&&l==0)||(k==4&&l==4)){

					}else{
						int pixel = originimage.at<uchar>(i-2+k,j-2+l);
						if(pixel>largest){
							largest = pixel;
						}
					}
				}
			}
			resultimage.at<uchar>(i,j) = largest;
		}
	}
}

void Erosion(Mat originimage, Mat resultimage){
	for(int i=2; i<originimage.rows-2; i++){
		for(int j=2; j<originimage.cols-2; j++){
			int smallest = 255;
			//find largest
			for(int k=0; k<5; k++){
				for(int l=0; l<5; l++){
					if((k==0&&l==0)||(k==0&&l==4)||(k==4&&l==0)||(k==4&&l==4)){

					}else{
						int pixel = originimage.at<uchar>(i-2+k,j-2+l);
						if(pixel<smallest){
							smallest = pixel;
						}
					}
				}
			}
			resultimage.at<uchar>(i,j) = smallest;
		}
	}
}

void Opening(Mat originimage, Mat resultimage){
	Mat tempimage = originimage.clone();
	Dilation(originimage,tempimage);
	Erosion(tempimage,resultimage);
}

void Closing(Mat originimage, Mat resultimage){
	Mat tempimage = originimage.clone();
	Erosion(originimage,tempimage);
	Dilation(tempimage,resultimage);
}

void OpenThenClose(Mat noisedimage,Mat resultimage){
	Mat tempimage = noisedimage.clone();
	Opening(noisedimage,tempimage);
	Closing(tempimage,resultimage);
}

void CloseThenOpen(Mat noisedimage, Mat resultimage){
	Mat tempimage = noisedimage.clone();
	Closing(noisedimage,tempimage);
	Opening(tempimage,resultimage);
}