#include <iostream>
/*
#include "GerenteLogin.h"

using namespace std;

int main(int argc, char** argv) {
	GerenteLogin gLogin;
	gLogin.Iniciar();
	return 0;
}
*/

#include <opencv2\opencv.hpp>

using cv::VideoCapture;
using cv::Mat;
using cv::imread;
using cv::imshow;
using cv::waitKey;
using cv::namedWindow;

int main(int argc, char** argv){
	//Lenna test, ok =D
	Mat img = imread("Lenna.png"); // Mat trata a imagem aberta como uma matriz
	namedWindow("image", WINDOW_NORMAL);
	imshow("image", img);
	waitKey(0);

	return 0;
}
/*
//Teste de captura de vídeo =D
VideoCapture capturaTeste(0);
if (!capturaTeste.isOpened()) {
	cout << "Nao pode abrir a camera" << endl;
}
char pressed = -1;
while (true) {
	Mat camFrame;
	capturaTeste.read(camFrame);
	imshow("Camera output", camFrame);
	pressed = waitKey(30);
	if (pressed >= 0) {
		cout << pressed << endl;
		break;
	}
}
*/