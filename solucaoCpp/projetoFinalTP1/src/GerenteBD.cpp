#include "GerenteBD.h"

//#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
	#define DEBUG_PRINT(x) 
#endif

string GerenteBD::dbName("");
string GerenteBD::dbReserva("");
map<string, string> GerenteBD::dadosUsuarios;
map<string, vector<Reserva>> GerenteBD::dadosReservas;
int GerenteBD::codigoReserva = 1;
GerenteBD::GerenteBD()
{
	DEBUG_PRINT("GerenteDB::() - inicio");
	dbName = "resources/myDB";
	string registro;
	string matricula;
	string nome;
	string senha;
	ifstream usuarios(dbName + ".txt");
	while (true) {
		stringstream aux;
		getline(usuarios, registro);
		if (registro == "") break;
		DEBUG_PRINT("Registro: " << registro);
		aux << registro;
		aux >> matricula;	//extraindo informações posicionais de cada registro
		aux >> nome;		//pode ser feito assim
		aux >> senha;
		dadosUsuarios[matricula] = registro;	//como por enquanto só tem o nome, fica só o nome mapeado pela matricula
	}
	usuarios.close();
	for (map<string,string>::iterator it = dadosUsuarios.begin(); it != dadosUsuarios.end(); it++) {
		DEBUG_PRINT("	Chave: " << it->first);
		DEBUG_PRINT("		Valor: " << it->second);
	}
	
	dbReserva = "resources/reservas";

	ifstream reservas(dbReserva + ".txt");
	while (true) {
		stringstream aux;
		Reserva reserva;
		getline(reservas, registro);
		if (registro == "") break;
		DEBUG_PRINT("Registro: " << registro);
		aux << registro;
		aux >> reserva.numeroReserva;
		aux >> reserva.matricula;
		aux >> reserva.laboratorio;
		aux >> reserva.data;
		aux >> reserva.hora;
		if ( stoi(reserva.numeroReserva) >= codigoReserva) {
			codigoReserva = stoi(reserva.numeroReserva) + 1;
		}
		if (dadosReservas.find(reserva.data) == dadosReservas.end()) {
			vector<Reserva> vR;
			vR.push_back(reserva);
			dadosReservas[reserva.data] = vR;

		}
		else {
			dadosReservas[reserva.data].push_back(reserva);
		}
		
	}
	DEBUG_PRINT("GerenteDB::() - fim");
}


GerenteBD::~GerenteBD()
{
	//insere os dados da memoria no arquivo
	ofstream bdFile;
	bdFile.open(dbName + ".txt", std::ofstream::app);
	for (map<string, string>::iterator it = dadosUsuarios.begin(); it != dadosUsuarios.end(); it++) {
		bdFile << it->second << endl;
	}
	bdFile.close();
}

void GerenteBD::InsereUsuario(Usuario &usuario) {
	DEBUG_PRINT("GerenteBD::InsereUsuario() - inicio");
	string aux;
	aux = usuario.GetMatricula() + " " + usuario.GetNome() + " " + usuario.GetSenha() + "\n";
	map<string, string>::iterator it = dadosUsuarios.find(usuario.GetMatricula());
	if (it == dadosUsuarios.end()) {
		dadosUsuarios[usuario.GetMatricula()] = aux;
	}
	else {
		//essa linha vai sair daqui.
		cout << "Usuario ja existe" << endl;
	}
	CommitUsuario();

	DEBUG_PRINT("GerenteBD::InsereUsuario() - fim");
}

void GerenteBD::AtualizaUsuario() {
	DEBUG_PRINT("GerenteBD::AtualizaUsuario() - inicio");

	DEBUG_PRINT("GerenteBD::AtualizaUsuario() - fim");
}

Usuario GerenteBD::BuscaUsuario(string matricula) {
	DEBUG_PRINT("GerenteBD::BuscaUsuario() - inicio");
	Usuario usuario;
	stringstream aux;
	string nome;
	string senha;
	aux << dadosUsuarios[matricula];
	aux >> nome;
	aux >> nome;
	aux >> senha;
	usuario.SetMatricula(matricula);
	usuario.SetNome(nome);
	usuario.SetSenha(senha);
	DEBUG_PRINT("GerenteBD::BuscaUsuario() - fim");
	return usuario;	//como por enquanto é só matricula e nome, td ok
}

bool GerenteBD::ExisteUsuario(string matricula) {
	if (dadosUsuarios.find(matricula) != dadosUsuarios.end())
		return true;
	else return false;
}

bool GerenteBD::ChecaUsuario(string matricula, string senha) {
	DEBUG_PRINT("GerenteBD::ChecaUsuario - inicio");
	map<string, string>::iterator it = dadosUsuarios.find(matricula);
	if (it != dadosUsuarios.end()) {
		stringstream aux;
		string uSenha;
		aux << it->second;
		//descarta matricula, nome
		aux >> uSenha; aux >> uSenha; aux >> uSenha; //a senha é o terceiro elemento da linha
		DEBUG_PRINT("GerenteBD::ChecaUsuario - fim");
		if (uSenha == senha) return true;
		else return false;
	}
	else {
		DEBUG_PRINT("GerenteBD::ChecaUsuario - fim");
		return false;
	}
}

void GerenteBD::RemoveUsuario() {
	DEBUG_PRINT("GerenteBD::RemoveUsuario() - inicio");

	DEBUG_PRINT("GerenteBD::RemoveUsuario() - fim");
}

void GerenteBD::CommitUsuario() {
	ofstream bdFile;
	bdFile.open(dbName + ".txt", std::ofstream::out);
	for (map<string, string>::iterator it = dadosUsuarios.begin(); it != dadosUsuarios.end(); it++) {
			bdFile << it->second << endl;
	}
	bdFile.close();
}


void GerenteBD::InsereReserva(string matricula, Reserva reserva) {
	stringstream aux;
	aux << codigoReserva++;
	aux >> reserva.numeroReserva;
	if(DataComReserva(reserva.data)) dadosReservas[reserva.data].push_back(reserva);
	else {
		vector<Reserva> novoVector;
		novoVector.push_back(reserva);
		dadosReservas[reserva.data] = novoVector;
	}
}

vector<Reserva> GerenteBD::BuscaReserva(string entrada, string campo) {

	if (campo == "data") {
		if (DataComReserva(entrada)) return dadosReservas[entrada];
		return vector<Reserva>();
	}
	else if (campo == "matricula") {
		vector<Reserva> reservas;
		if (!dadosReservas.empty()) {
			for (map<string, vector<Reserva>>::iterator itM = dadosReservas.begin(); itM != dadosReservas.end(); itM++) {
				if (!itM->second.empty()) {
					for (vector<Reserva>::iterator itV = itM->second.begin(); itV != itM->second.end(); itV++) {
						if (itV->matricula == entrada)
							reservas.push_back(*itV);
					}
				}

			}
		}
		return reservas;
	}
}

void GerenteBD::CancelaReserva(string numReserva) {
	//map<string, Reserva>::iterator it = dadosReservas.find(numReserva);
	bool terminou = false;
	for (map<string, vector<Reserva>>::iterator it = dadosReservas.begin(); it != dadosReservas.end(); it++) {
		for (int i = 0; i < it->second.size(); i++) {
			if (it->second[i].numeroReserva == numReserva) {
				it->second.erase(it->second.begin() + i);
				terminou = true;
				break;
			}
		}
		if (terminou) break;
	}

}

void GerenteBD::CommitReserva() {
	ofstream bdFile;
	bdFile.open(dbReserva + ".txt", std::ofstream::out);
	for (map<string, vector<Reserva>>::iterator it = dadosReservas.begin(); it != dadosReservas.end(); it++) {
		for (int i = 0; i < it->second.size(); i++) {
			Reserva reserva = it->second[i];
			bdFile << reserva.numeroReserva << " "
				<< reserva.matricula << " "
				<< reserva.laboratorio << " "
				<< reserva.data << " "
				<< reserva.hora << endl;
		}
	}
	bdFile.close();
}

bool GerenteBD::DataComReserva(string data) {
	map<string, vector<Reserva>>::iterator it = dadosReservas.find(data);
	if (it != dadosReservas.end()) return true;
	else return false;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
