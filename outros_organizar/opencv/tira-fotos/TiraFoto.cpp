//http://docs.opencv.org/3.2.0/db/d28/tutorial_cascade_classifier.html
//https://askubuntu.com/questions/591930/python-h-found-by-locate-but-not-by-gcc
//#include <python2.7/Python.h>
#include <ctime>
#include <sstream>      // std::stringstream
#include <string>       // std::string
#include <sys/stat.h>	// mkdir

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
//#include <stdio.h>
using namespace std;
using namespace cv;

int detectaTiraFoto();

int main( void )
{
	detectaTiraFoto();
    return 0;
}

int detectaTiraFoto()
{
    
	//String dir = "/usr/share/opencv/haarcascades/";
	String face_cascade_name =  "haarcascade_frontalface_alt.xml";
	String eyes_cascade_name =  "haarcascade_eye_tree_eyeglasses.xml";
	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;
	String window_name = "Capture - Face detection";
	    
    std::vector<Rect> faces;
   
    VideoCapture capture;
    Mat frame;
    Mat frame_gray;
    
    cout << "digite o nome da pasta: ";
    std::string pasta;
    cin >> pasta;

    #ifdef __linux__ 
	    const char * c = pasta.c_str();

		char * writable = new char[pasta.size() + 1];
		std::copy(pasta.begin(), pasta.end(), writable);
		writable[pasta.size()] = '\0';

	    int resp = mkdir( writable, 0777 );
		if (resp == 0 ){
			std::cout << "Pasta criada, com sucesso\n";
		} else if (resp == -1) {
			std::cout << "A pasta ja existe. FIM!\n";
			return 1;
		} else {
			std::cout << "Erro desconhecido.\n";
			return -1;
		}
	#else // windows
		int resp = mkdir( pasta );
		if (resp == 0 ){
			std::cout << "Pasta criada, com sucesso\n";
		} else if (resp == -1) {
			std::cout << "A pasta ja existe. FIM!\n";
			return 1;
		} else {
			std::cout << "Erro desconhecido.\n";
			return -1;
		}
	#endif

		    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ cout << "--(!)Error loading face cascade: " << face_cascade_name << endl; return -1; };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ cout << "--(!)Error loading eyes cascade: " << eyes_cascade_name << endl; return -1; };
    //-- 2. Read the video stream
    capture.open( "http://192.168.1.123:4747/mjpegfeed?640x480" );

    if ( ! capture.isOpened() ) { cout << "--(!)Error opening video capture\n"; return -1; }


    int contador_fotos = 0;
    time_t now, later;
	int iniciar_contagem = 0;

    while ( capture.read(frame) )
    {
    	//cout << "entra no loop\niniciar_contagem: " << iniciar_contagem << "\ncontador_fotos: " << contador_fotos << endl;
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
        cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    	equalizeHist( frame_gray, frame_gray );
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$444
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
	        if (eyes.size() > 0 && contador_fotos < 10)
	        {
	   			if ( iniciar_contagem == 0){
		        	time(&now);/* get current time; same as: now = time(NULL)  */
		        	iniciar_contagem = 1;
		        	//cout << "iniciar_contagem 0" << endl;
		        } else if (iniciar_contagem == 1 ){
		        	time(&later);
		        	double seconds = difftime(later, now);
		        	//cout << seconds << " segundos\n";
		        	if (seconds > 1 ){ /* Espera 1 seg*/
		        		std::stringstream ss;
		        		ss << pasta << "/" << contador_fotos << "-foto.png";
		        		imwrite(ss.str(), frame_gray);
		        		iniciar_contagem = 0;
		        		contador_fotos += 1;
		        		cout << "Foto: " << ss.str() << endl; 
		        		if (contador_fotos == 10){
		        			cout << "Capturei 10 fotos. FIM.\n";
		        			return 1;
		        		}
		        	}
		        }
		   	}
   		}
   		imshow( window_name, frame );
        // $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        char c = (char)waitKey(10);
        if( c == 27 ) { return 0; } // escape
    }
}
