#include "Reserva.h"

Reserva::Reserva() {

}
Reserva::~Reserva() {

}

void Reserva::ImprimeReserva() {
	cout << "Matricula do reservante: " << matricula << endl
		<< "Numero: " << numeroReserva << endl
		<< "Laboratorio: " << laboratorio << endl
		<< "Data: " << data;
	switch (stoi(hora)) {
	case 1:
		cout << " Horario: " << "8h-10h" << endl;
		break;
	case 2:
		cout << " Horario: " << "10h-12h" << endl;
		break;
	case 3:
		cout << " Horario: " << "12h-14h" << endl;
		break;
	case 4:
		cout << " Horario: " << "14h-16h" << endl;
		break;
	case 5:
		cout << " Horario: " << "16h-18h" << endl;
		break;
	case 6:
		cout << " Horario: " << "20h-22h" << endl;
		break;
	case 7:
		cout << " Horario: " << "22h-23h" << endl;
		break;
	}
}

ostream& operator<<(ostream& out, const Reserva& r) {
	out << "Matricula do reservante: " << r.matricula << endl
	<< "Numero: " << r.numeroReserva << endl
	<< "Laboratorio: " << r.laboratorio << endl
	<< "Data: " << r.data << " Horario: " << r.hora << endl;
	return out;
}