//#pragma once
//#ifndef __SistemaLinf__
//#define __SistemaLinf__

#include <iostream>

#include "GerenteLogin.h"
//#include "GerenteBD.h"
//#include "Usuario.h"
//#include "Reserva.h"

using std::cout;
using std::endl;
using std::cin;

/*!	\brief Gera ambiente onde classes se comunicam
*
*	As classes do sistema se comunicam no método Run() de SistemaLinf.
*/
class SistemaLinf {
private:
	/*!
	*	\brief Instância de \c GerenteLogin.
	*/
	GerenteLogin GLog;

	/*!
	*	\brief Instância de \c GerenteBD.
	*/
	GerenteBD GBD;

	/*!
	*	\brief Instância de usuário que efetuou login no sistema.
	*/
	Usuario usuarioLogado;

	/*!
	*	\brief Responsavel por resolver o login do usuário.
	*
	*	O login pode ser feito via reconhecimento facial, possibilitado
	*	pela biblioteca OpenCV. Caso o reconhecimento falhe, é exigida
	*	senha do usuário.
	*/
	void _EfetuaLogin();

	/*!
	*	\brief Mensagem padrão para entrada inválida.
	*/
	void _OpcaoInvalida();

	/*!
	*	\brief Fornece os principais conjuntos de operações possiveis no sistema.
	*/
	void _NavegaConta();
	
	/*!
	*	\brief Limpa os caracteres da tela.
	*/
	void _LimpaTela();

	/*!
	*	\brief Gera o cabeçalho principal do sistema.
	*/
	void _Cabecalho();

	/*!
	*	\brief Acessa área de modificação de dados pessoais.
	*/
	void _EditaDadosPessoais();

	/*!
	*	\brief Acessa a área de reserva de salas do laboratório.
	*/
	void _ReservaLaboratorio();

	/*!
	*	\brief Faz requisição das reservas existentes pelo usuário logado.
	*/
	void _VerificaReserva();

	/*!
	*	\brief Faz requisição para reserva de laboratório.
	*/
	void _ReservarLab();

	/*!
	*	\brief Faz requisição para cancelamento de reserva.
	*/
	void _CancelarReserva();

	/*!
	*	\brief Imprime na tela resultado da consulta de reservas.
	*/
	void _ImprimeReservas(vector<Reserva> reservas);
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


//#endif // SistemaLinf
