
/*
	Caso a instalação do opencv nao tenha sido
	concluida, apague a linha #define OPENCV_INSTALLED
*/
#define OPENCV_INSTALLED
#ifdef OPENCV_INSTALLED
#include <opencv2\opencv.hpp>

using cv::VideoCapture;
using cv::Mat;
using cv::imread;
using cv::imshow;
using cv::waitKey;
using cv::namedWindow;
using cv::WINDOW_NORMAL;

#endif

#include "SistemaLinf.h"



//Função para teste de comunicação com opencv
#ifdef OPENCV_INSTALLED
void lennaTest();
#endif

int main(int argc, char** argv) {
	SistemaLinf sis;
	sis.Run();
	return 0;
}


#ifdef OPENCV_INSTALLED
void lennaTest() {
	//Lenna test, ok =D
	Mat img = imread("resources/Lenna.png"); // Mat trata a imagem aberta como uma matriz
	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);
}
#endif // 

