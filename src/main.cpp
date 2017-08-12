#define MAJOR_VERSION 0
#define MINOR_VERSION 1


#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <boost/filesystem.hpp>

#include "error_codes.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
  cout << "crashtest v " << MAJOR_VERSION << '.' << MINOR_VERSION << endl;

  VideoCapture cap;

#ifdef _WIN32
  std::string filename = "C:\\Users\\sinigard\\Codice\\crashtest\\video\\PrimoCrash.mts";
  cap.set(CV_CAP_PROP_FOURCC, CV_FOURCC('H', '2', '6', '4'));
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
  //cap.set(CV_CAP_PROP_POS_MSEC, 300);  //start the video at 300ms
  double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
  cout << "Frame per seconds : " << fps << endl;
  namedWindow("CrashTest_Video", CV_WINDOW_AUTOSIZE);

  while (true)
  {
    Mat frame;
    bool bSuccess = cap.read(frame);
    if (!bSuccess)
    {
      cout << "Video is over, exiting..." << endl;
      break;
    }
    imshow("CrashTest_Video", frame);
    if (waitKey(30) == 27)  //wait for 'esc' key press for 30 ms.
    {
      cout << "ESC key is pressed by user, exiting..." << endl;
      break;
    }
  }

  return 0;
}


