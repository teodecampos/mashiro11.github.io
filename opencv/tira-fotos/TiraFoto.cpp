//http://docs.opencv.org/3.2.0/db/d28/tutorial_cascade_classifier.html
//https://askubuntu.com/questions/591930/python-h-found-by-locate-but-not-by-gcc
#include <python2.7/Python.h>

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

#ifdef __linux__ 
#include <unistd.h>
#else
#include <windows.h>
#endif

int num = 0;
void mySleep(int sleepMs);
void detectaTiraFoto( Mat frame );
String dir = "/usr/share/opencv/haarcascades/";
String face_cascade_name = dir + "haarcascade_frontalface_alt.xml";
String eyes_cascade_name = dir + "haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";
int main( void )
{
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ cout << "--(!)Error loading face cascade: " << face_cascade_name << endl; return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ cout << "--(!)Error loading eyes cascade: " << eyes_cascade_name << endl; return -1; };
    //-- 2. Read the video stream
    capture.open( "http://192.168.1.123:4747/mjpegfeed?640x480" );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }
    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectaTiraFoto( frame );
        mySleep(1000);
        char c = (char)waitKey(10);
        if( c == 27 ) { break; } // escape
    }
    return 0;
}
void detectaTiraFoto( Mat frame )
{
    
    std::vector<Rect> faces;
    Mat frame_gray;
    Mat original = frame.clone();
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 150, 0, 255 ), 4, 8, 0 );
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        for ( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
        if (eyes.size() == 2 && num < 10){
            
            char nome[20];
            sprintf ( nome, "%d-alpha.png", num );
            imwrite(nome, frame_gray);
            num++;
            cout << "Sorria! "<< num << endl;
            if (num == 10 ){
                cout << "10 fotos... pronto!" << endl;
            }
        }else if(eyes.size() > 0){
            cout << "achei " << eyes.size() << " olhos no total" << endl;
        }
    }
    //-- Show what you got
    imshow( window_name, frame );
}

void mySleep(int sleepMs)
{
#ifdef __linux__ 
    usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
#else
    Sleep(sleepMs);
#endif
}