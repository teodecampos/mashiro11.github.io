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

class Reserva {
public:
	Reserva();
	~Reserva();

	void ImprimeReserva();
	string data;
	string hora;
	string laboratorio;
	string numeroReserva;
	string matricula;
};
#endif // __RESERVA__
