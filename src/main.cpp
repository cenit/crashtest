#define MAJOR_VERSION 0
#define MINOR_VERSION 2


#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <boost/filesystem.hpp>

#include "error_codes.h"


int main(int argc, char* argv[])
{
  using namespace cv;
  using namespace std;

  cout << "crashtest " << MAJOR_VERSION << '.' << MINOR_VERSION << " using OpenCV " << CV_MAJOR_VERSION  << '.' << CV_MINOR_VERSION << endl;

  VideoCapture cap;
  int framecounter = 0; 

#ifdef _WIN32
  std::string filename = "C:\\Users\\sinigard\\Codice\\crashtest\\video\\PrimoCrash.mts";
  //OpenCV cannot use ffmpeg in libraries build by vcpkg, so this software still does not work in Windows...
#else
  std::string filename = "/mnt/c/Users/sinigard/Codice/crashtest/video/PrimoCrash.mts";
#endif

  cap.open(filename);

  if (boost::filesystem::exists(filename))
  {
    cout << "Boost has found the file " << filename << endl;
  }
  else
  {
    cerr << "Boost cannot find the file " << filename << endl;
  }
  if (!cap.isOpened())
  {
    cerr << "OpenCV cannot open the video file" << endl;
    cin.get();
    exit(ERROR_VIDEO_NOT_FOUND);
  }
  cap.set(CV_CAP_PROP_POS_MSEC, 44000);  //start the video at 20000ms (20s)
  double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
  cout << "Frame per seconds : " << fps << endl;
  namedWindow("Video", WINDOW_NORMAL);
  namedWindow("test", WINDOW_NORMAL);
  namedWindow("Grid", WINDOW_NORMAL);
  resizeWindow("Video", 640, 360);
  resizeWindow("test", 640, 360);
  resizeWindow("Grid", 640, 360);
  Mat frame;
  cap >> frame;

  while (!frame.empty())
  {
    Mat grid;
    framecounter++;
    imshow("Video", frame);
    cvtColor( frame, frame, COLOR_BGR2GRAY );
    threshold(frame, grid, 230.0, 255.0, THRESH_BINARY);
    erode(grid, grid, Mat(), Point(-1, -1), 1, 1, 1);
    dilate(grid, grid, Mat(), Point(-1, -1), 12, 1, 1);
    erode(grid, grid, Mat(), Point(-1, -1), 11, 1, 1);
    bitwise_and(frame, frame, grid, grid);
    erode(grid, grid, Mat(), Point(-1, -1), 15, 1, 1);
    dilate(grid, grid, Mat(), Point(-1, -1), 15, 1, 1);
    imshow("test", grid);
    threshold(grid, grid, 180.0, 255.0, THRESH_BINARY);
    printf("Frame #%06d - mask r: %d, c:%d     \t\r", framecounter, grid.rows, grid.cols);
    imshow("Grid", grid);

    if (waitKey(30) == 27)  //wait for 'esc' key press for 30 ms.
    {
      cout << "ESC key is pressed by user, exiting..." << endl;
      break;
    }

    cap >> frame;
    if (frame.empty()) break;

  }

  return 0;
}


