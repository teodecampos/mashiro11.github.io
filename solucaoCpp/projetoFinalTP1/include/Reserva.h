#pragma once
#ifndef __RESERVA__
#define __RESERVA__

#include <iostream>
#include <string>
#include <ostream>

using std::string;
using std::ostream;
using std::cout;
using std::endl;
using std::stoi;

/*!
*	\brief Classe \c Reserva abstrai o conceito da reserva de uma sala no laboratório.
*/
class Reserva {
public:
	/*!
	*	\brief Construtor padrão.
	*/
	Reserva();

	/*!
	*	Destrutor.
	*/
	~Reserva();

	/*!
	*	\brief Saída formatada das informações da instância da \c Reserva.
	*/
	void ImprimeReserva();

	/*!
	*	\brief Data para o qual foi feita a reserva.
	*/
	string data;

	/*!
	*	\brief Horário reservado.
	*/
	string hora;

	/*!
	*	\brief Numero do laboratório reservado.
	*/
	string laboratorio;

	/*!
	*	\brief Código da reserva.
	*/
	string numeroReserva;

	/*!
	*	\brief Matrícula do usuário que efetuou a reserva.
	*/
	string matricula;
};
#endif // __RESERVA__
