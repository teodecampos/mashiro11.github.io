//http://docs.opencv.org/3.2.0/db/d28/tutorial_cascade_classifier.html

#include <opencv2/opencv.hpp>

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;
#include "opencv2/core.hpp"
#include "opencv2/face.hpp"

#include <fstream>
#include <sstream>

using namespace cv::face;



void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';' );
void reconhece();

int main( int argc, const char *argv[] )
{
    
    

    reconhece();

    
    return 0;
}

void reconhece( )
{
    String face_cascade_name = "resources/haarcascade_frontalface_alt.xml";
    String eyes_cascade_name = "resources/haarcascade_eye_tree_eyeglasses.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    String window_name = "Reconhece face";

    VideoCapture capture;
    
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ cout << "--(!)Error loading face cascade\n"; exit (-1); };
    if( !eyes_cascade.load( eyes_cascade_name ) ){ cout << "--(!)Error loading eyes cascade\n"; exit (-1); };
    //-- 2. Read the video stream
    capture.open( "http://192.168.1.123:4747/mjpegfeed?640x480" );
    if ( ! capture.isOpened() ) { cout << "--(!)Error opening video capture\n"; exit (-1); }

    //$$$$$$$$$$$ cria csv
    system("python resources/cria_csv.py resources/fotos/");
    // Get the path to your CSV.
    string path_fotos_csv = "resources/fotos.csv";
    // These vectors hold the images and corresponding labels.
    vector<Mat> images;
    vector<int> labels;
    // Read in the data. This can fail if no valid
    // input filename is given.
    try {
        read_csv(path_fotos_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << path_fotos_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(Error::StsError, error_message);
    }
    int im_width = images[0].cols;
    int im_height = images[0].rows;
    // $$$$$$$ TREINAR FACES
    Ptr<LBPHFaceRecognizer> model = LBPHFaceRecognizer::create();
    model->train(images, labels);

    Mat frame;

    //$$ loop 

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }
        //-- 3. Apply the classifier to the frame

        //$$$$$$$$$$$$$$$$$$$$$$$$$$ reconhece( frame, model ); $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        std::vector<Rect> faces;
        Mat frame_gray;
        Mat original = frame.clone();
        cvtColor( original, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );
        //-- Detect faces
        face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
        for ( size_t i = 0; i < faces.size(); i++ )
        {
            Rect face_i = faces[i];
            // Crop the face from the image. So simple with OpenCV C++:
            Mat face = frame_gray(face_i);
        
            Mat face_resized;
            cv::resize(face, face_resized, Size(im_width, im_height), 1.0, 1.0, INTER_CUBIC);

            //eyes
            Mat faceROI = frame_gray( faces[i] );
            std::vector<Rect> eyes;
            eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
            if (eyes.size() > 0 ){
                // Now perform the prediction, see how easy that is:
                int prediction = model->predict(face_resized);
                // And finally write all we've found out to the original image!
                // First of all draw a green rectangle around the detected face:
                rectangle(original, face_i, CV_RGB(0, 255,0), 1);
                // Create the text we will annotate the box with:
                string box_text = format("Prediction = %d", prediction);
                // Calculate the position for annotated text (make sure we don't
                // put illegal values in there):
                int pos_x = std::max(face_i.tl().x - 10, 0);
                int pos_y = std::max(face_i.tl().y - 10, 0);
                // And now put it into the image:
                putText(original, box_text, Point(pos_x, pos_y), FONT_HERSHEY_PLAIN, 1.0, CV_RGB(0,255,0), 2.0);
            }
        }
        //-- Show what you got
        imshow( window_name, original );

        //$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
        char c = (char)waitKey(10);
        if( c == 27 ) { break; } // escape
    }

    //$$ fim loop
}
void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator) {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(Error::StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}
