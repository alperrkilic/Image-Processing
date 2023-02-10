#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <string>

using namespace cv;
using namespace std;

void getContours(Mat imgDil, Mat img);

int main(int argc, char **argv)
{
  string path = "C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\test.png";
  Mat img = imread(path);

  CascadeClassifier faceCascade;
  faceCascade.load("C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\haarcascade_frontalface_default.xml");

  if (faceCascade.empty())
  {
    cout << "XML file couldn't loaded." << endl;
  }

  vector<Rect> faces;

  faceCascade.detectMultiScale(img, faces, 1.1, 10);

  for (size_t i = 0; i < faces.size(); i++)
  {
    rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
  }

  imshow("Image", img);
  waitKey(0);

  return 0;
}

/*
  Displaying Image:
    string path = "C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\test.png";
    Mat img = imread(path);

    imshow("Image", img);
    waitKey(0);
*/

/*
  Displaying Video:
    string path = "C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\test_video.mp4";
    VideoCapture cap(path);
    Mat img;

    while (true)
    {
      cap.read(img);
      imshow("Image", img);
      waitKey(1); // delay for 1 ms between frames
    }
*/

/*
  Webcam:

  VideoCapture cap(0);
  Mat img;

  while (true)
  {
    cap.read(img);

    imshow("Image", img);
    waitKey(1);
  }
*/

/*
  Basic Functions:
    string path = "C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\test.png";
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDil, kernel);
    erode(imgDil, imgErode, kernel);

    imshow("Image", img);
    imshow("Image Gray", imgGray);
    imshow("Image Blur", imgBlur);
    imshow("Image Canny", imgCanny);
    imshow("Image Dilation", imgDil);
    imshow("Image Erode", imgErode);
    waitKey(0);
*/

/*
  Resize and Crop:
    string path = "C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\test.png";
    Mat img = imread(path);
    Mat imgResize, imgCrop;

    cout << img.size() << endl;
    resize(img, imgResize, Size(640, 480)); // Or resize(img, imgResize, Size(),0.5,0.5); --> scaling it to half

    Rect roi(200, 100, 300, 300);
    imgCrop = img(roi);

    imshow("Image", img);
    imshow("Image Resize", imgResize);
    imshow("Image Crop", imgCrop);
    waitKey(0);
*/

/*
  Creating Image:

  // Blank Image

  Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); // Blue Green Red

  circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);
  rectangle(img, Point(130, 226), Point(382, 286), Scalar(255, 255, 255), FILLED);
  line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);
  putText(img, "Intro Project", Point(137, 262), FONT_HERSHEY_DUPLEX, 1.25, Scalar(0, 69, 255), 2);

  imshow("Image", img);
  waitKey(0);

*/

/*
  // Image Warping

  string path = "C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\cards.jpg";
  Mat img = imread(path);

  float w = 250, h = 350;

  Point2f src[4] = {{529, 142}, {771, 190}, {405, 395}, {674, 457}};
  Point2f dst[4] = {{0.0f, 0.0f}, {w, 0.0f}, {0.0f, h}, {w, h}};

  Mat matrix, imgWarp;

  matrix = getPerspectiveTransform(src, dst);
  warpPerspective(img, imgWarp, matrix, Point(w, h));

  for (size_t i = 0; i < 4; i++)
  {
    circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
  }

  imshow("Image", img);
  imshow("Image Warp", imgWarp);

  waitKey(0);
*/

/*
  Color Detection:
    string path = "C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\lambo.png";
    Mat img = imread(path);
    Mat imgHSV, mask;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);
    int hmin = 0, smin = 110, vmin = 153;
    int hmax = 90, smax = 240, vmax = 255;

    namedWindow("Trackbars", (640, 200));
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);

    while (true)
    {
      Scalar lower(hmin, smin, vmin);
      Scalar upper(hmax, smax, vmax);
      inRange(imgHSV, lower, upper, mask);

      imshow("Image", img);
      imshow("Image HSV", imgHSV);
      imshow("Image Mask", mask);
      waitKey(1);
    }

    Note: If you want to detect objects by color,
    Val max:255 | Val min:0
    Sat max:255 | Sat min:0

    Change Hue Min and Hue Max

*/

/*
  Object Detection:

  Main:
  string path = "C:\\OPEN-CV Projects\\open-cv-intro\\Image-Processing\\Resources\\shapes.png";
  Mat img = imread(path);
  Mat imgGray, imgBlur, imgCanny, imgDil;

  // Preprocessing
  cvtColor(img, imgGray, COLOR_BGR2GRAY);
  GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
  Canny(imgBlur, imgCanny, 25, 75);
  Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
  dilate(imgCanny, imgDil, kernel);

  getContours(imgDil, img);

  imshow("Image", img);

  waitKey(0);

  return 0;


  Function:

void getContours(Mat imgDil, Mat img)
{

  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;

  findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
  // drawContours(img, contours, -1, Scalar(255, 0, 255), 2); // last parameter is thickness
  vector<vector<Point>> conPoly(contours.size());
  vector<Rect> boundRect(contours.size());
  string objectType;

  for (int i = 0; i < contours.size(); i++)
  {
    int area = contourArea(contours[i]);
    cout << area << endl;

    if (area > 1000)
    {

      float peri = arcLength(contours[i], true);

      approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

      boundRect[i] = boundingRect(conPoly[i]);

      int objCorner = (int)conPoly[i].size();

      if (objCorner == 3)
      {
        objectType = "Tri";
      }
      else if (objCorner == 4)
      {

        float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;

        if (aspRatio > 0.95 && aspRatio < 1.05)
        {
          objectType = "Square";
        }
        else
        {
          objectType = "Rect";
        }
      }
      else if (objCorner > 4)
      {
        objectType = "Circle";
      }

      drawContours(img, conPoly, i, Scalar(255, 0, 255), 2); // last parameter is thickness
      rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
      putText(img, objectType, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_PLAIN, 0.75, Scalar(0, 69, 255), 1);
    }
  }
}
*/