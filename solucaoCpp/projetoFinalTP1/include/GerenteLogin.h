#ifndef GERENTE_LOGIN
#define GERENTE_LOGIN


#include <iostream>
#include <string>
#include <stdio.h>

//#include <vector>


#ifdef __linux__ 
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
	#include "Usuario.h"
	#include "GerenteBD.h"
	#include "opencv2\objdetect\objdetect.hpp"
	#include "opencv2\imgproc\imgproc.hpp"
	#include "opencv2\highgui\highgui.hpp"
	#include "opencv2\videoio\videoio.hpp"
#endif



using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::vector;

using namespace cv;

/*!
*	\brief \c GerenteLogin é aquela que credencia o usuário.
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
	Usuario Credencia(string matricula);
	bool ReconheceFace(string matricula);
	Usuario NovoUsuario(string matricula);
	
private:

	/*!
	*	\brief Faz a verificação de usuário via webcam.
	*/
	void _entradaCamera();
	
	/*!
	*	\brief Faz a verificação de usuário via teclado.
	*/
	void _entradaTeclado();

	/*!
	*	\brief Valida a operação de entrada.
	*/
	int _verificaEntrada();//

	void _mySleep(int);
};

#endif