//#ifndef GERENTE_LOGIN
//#define GERENTE_LOGIN


#include <iostream>
#include <ctime>
#include <sstream>      // std::stringstream
#include <string>       // std::string
#include <sys/stat.h>   // mkdir
#include <fstream>  // ler arquivo csv

#include "opencv2/core.hpp"
#include "opencv2/face.hpp"


#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"

//#include <vector>

//#include "Usuario.h"
#include "GerenteBD.h"

#ifdef __linux__ 
	#include <unistd.h>
	#include <termios.h>
#elif _WIN32
	#include <windows.h>
#endif

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;

using namespace cv;

using namespace cv::face;

/*!
*	\brief Credencia o usuário.
*
*	A primeira classe com quem o usuário irá lidar no sistema é o GerenteLogin.
*	Essa será responsável por validar a entrada do usuário no sistema. A primeira
*	tentativa será requisitando a matrícula do usuario e tentando reconhecimento facial. 
*	Caso falhe, o Gerente irá possibilitar que o usuário insira sua matrícula e senha para fazer login.
*
*	Uma vez credenciado, GerenteLogin gera uma instância de Usuario que irá existir durante a sessão no sistema,
*	encerrando-se a responsabilidade de GerenteLogin.
*/

class GerenteLogin
{
public:
	/*!
	*	\brief Construtor padrão da classe.
	*/
	GerenteLogin();
	virtual ~GerenteLogin();
	
	/*!
	*	\brief Passa o controle para a classe GerenteLogin.
	*	
	*	A tela default de início do sistema é a tela de login. Essa tela aguarda até que
	*	seja feita verificação de um usuário válido.
	*
	*/
	void Iniciar();

	/*!
	*	\brief Gera a instância do usuário que navega no sistema.
	*
	*	O método credencia o usuário tentando de duas formas:
	*	Primeiro, tenta identificar o usuário pela face, utilizando algorítmos de
	*	visão computacional providos pela biblioteca OpenCV.
	*	Caso o reconhecimento falhe, é pedido ao usuário que entre com uma senha.
	*	Nesse caso, o sistema realimenta a base de dados com novas fotos e cria a sessão
	*	daquele usuário.
	*
	*	\param matricula Matrícula do usuário que pretende fazer acesso.
	*	\return Instância com informações do usuário
	*/
	Usuario Credencia(string matricula);

	/*!
	*	\brief Gera uma instância de usuário.
	*
	*	\param matricula Matrícula do usuário.
	*	\return Usuário.
	*/
	Usuario NovoUsuario(string matricula);
	
private:
	/*!
	*	\brief Faz a verificação de usuário via webcam.
	*/
	bool _ReconheceFace(string matricula);
	
	/*!
	*	\brief Faz a captura de novas fotos do usuário via webcam.
	*/
	void _AtualizaBancoDeFotos();

	bool _CriaBancoDeFotos(string matricula);

	void _mySleep(int);

	void _read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';');

	string _digiteSenha();
};

//#endif