#pragma once
#ifndef __SistemaLinf__
#define __SistemaLinf__

#include <iostream>

#include "GerenteLogin.h"
#include "GerenteBD.h"


using std::cout;
using std::endl;
using std::cin;

/*!	\brief Gera ambiente onde classes se comunicam
*
*	As classes do sistema se comunicam no método Run() de SistemaLinf.
*/
class SistemaLinf {
private:
	GerenteLogin GLog;
	GerenteBD GBD;
public:
	/*!
	*	\brief Construtor padrão.
	*/
	SistemaLinf();
	
	/*!
	*	\brief Ambiente de execução dos sistema.
	*/
	void Run();

};


#endif // !SistemaLinf
