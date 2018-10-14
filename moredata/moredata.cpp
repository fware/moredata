/**
@file moredata.cpp
@brief this is program reads a folder of jpeg images and flips each images to create double the same of image data.
@modified by Fred Ware
*/

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

static void onMouse(int event, int x, int y, int, void*);
//Mat warping(Mat image, Size warped_image_size, vector< Point2f> srcPoints, vector< Point2f> dstPoints);
std::vector<std::string> split(std::string strToSplit, char delimeter);


int main(int argc, char** argv)
{
    CommandLineParser parser(argc, argv, "{@input| ../data/right.jpg |}");
    string flipDir = parser.get<string>("@input");

	vector<String> fn;
	//glob("/home/fware/Pictures/FlipTest/*.jpeg", fn);
	glob(flipDir + "/*.jpeg", fn);

	int idx = 0;
	for (auto f:fn) 
	{
        std::vector<std::string> filepathvec = split(f, '.');
        string filepathname = filepathvec[0];
        std::vector<std::string> rootvec = split(filepathname, '/');
        //std::cout << "rootname=" << rootvec[5] << std::endl;

        string flipFilename = "/flip_" + rootvec[5];
	    Mat original_img = imread(f);
        Mat new_img;
        cv::flip(original_img, new_img, 1);
        imwrite(flipDir + flipFilename + ".jpeg", new_img);
        idx++;
	}

    return 0;
}


std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}
