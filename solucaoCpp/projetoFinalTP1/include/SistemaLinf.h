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
	Usuario usuarioLogado;

	void _EfetuaLogin();
	int _Opcoes();
	void _OpcaoInvalida();
	void _NavegaConta();
	void _LimpaTela();
	void _Cabecalho();
	void _EditaDadosPessoais();
	void _ReservaLaboratorio();
	void _VerificaReserva();
	void _ReservarLab();
	void _CancelarReserva();
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
