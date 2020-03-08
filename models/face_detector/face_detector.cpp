#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp> 

using namespace std;
using namespace cv;
using namespace cv::dnn;
 
// Set the size of image and meanval
const size_t inWidth = 300;
const size_t inHeight = 300;
const double inScaleFactor = 1.0;
const Scalar meanVal(104.0, 177.0, 123.0);
 
int main(int argc, char** argv)
{
	// Load image
	Mat img;
	// Use commandline
#if 0
	if (argc < 2)
	{
		cerr<< "please input "<< endl;
		cerr << "[Format]face_detector_img.exe image.jpg"<< endl;
		return -1;
	}
	img = imread(argv[1]);
#else
	// Not use commandline
	img = imread("../models/girl.jpg");
#endif
 
	// Initialize Caffe network
	float min_confidence = 0.5;
	String modelConfiguration = "../models/res10-deploy.prototxt";
	String modelBinary = "../models/res10_300_300.caffemodel";
	dnn::Net net = readNetFromCaffe(modelConfiguration, modelBinary);
	if (net.empty())
	{
		cerr << "Can't load network by using the following files: " << endl;
		cerr << "prototxt:   " << modelConfiguration << endl;
		cerr << "caffemodel: " << modelBinary << endl;
		cerr << "Models are available here:" << endl;
		cerr << "<OPENCV_SRC_DIR>/samples/dnn/face_detector" << endl;
		cerr << "or here:" << endl;
		cerr << "https://github.com/opencv/opencv/tree/master/samples/dnn/face_detector" << endl;
		exit(-1);
	}
 
	// Prepare blob
	Mat inputBlob = blobFromImage(img, inScaleFactor, Size(inWidth, inHeight), meanVal, false, false);
	net.setInput(inputBlob, "data");	// set the network input
	Mat detection = net.forward("detection_out");	// compute output
 
	// Calculate and display time and frame rate
	vector<double> layersTimings;
	double freq = getTickFrequency() / 1000;
	double time = net.getPerfProfile(layersTimings) / freq;
 
	Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
 
	ostringstream ss;
	ss << "FPS: " << 1000 / time << " ; time: " << time << "ms" << endl;
	putText(img, ss.str(), Point(20,20), 0, 0.5, Scalar(0, 0, 255));
 
	// 
	float confidenceThreshold = min_confidence;
	for (int i = 0; i < detectionMat.rows; ++i)
	{
		// judge confidence
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > confidenceThreshold)
		{
			int xLeftBottom = static_cast<int>(detectionMat.at<float>(i, 3) * img.cols);
			int yLeftBottom = static_cast<int>(detectionMat.at<float>(i, 4) * img.rows);
			int xRightTop = static_cast<int>(detectionMat.at<float>(i, 5) * img.cols);
			int yRightTop = static_cast<int>(detectionMat.at<float>(i, 6) * img.rows);
 
			Rect object((int)xLeftBottom, (int)yLeftBottom,
				(int)(xRightTop - xLeftBottom),
				(int)(yRightTop - yLeftBottom));
 
			rectangle(img, object, Scalar(0, 255, 0));
 
			ss.str("");
			ss << confidence;
			String conf(ss.str());
			String label = "Face: " + conf;
			int baseLine = 0;
			Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
			rectangle(img, Rect(Point(xLeftBottom, yLeftBottom-labelSize.height), 
				Size(labelSize.width, labelSize.height + baseLine)), 
				Scalar(255, 255, 255), 1, 1, 0);
			putText(img, label, Point(xLeftBottom, yLeftBottom), 
				FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0));
                        imwrite("new_girl.jpg", img);
 
 
		}
	}
 
	namedWindow("Face Detection", WINDOW_NORMAL);
	imshow("Face Detection", img);
	waitKey(0);
 
	return 0;
}
