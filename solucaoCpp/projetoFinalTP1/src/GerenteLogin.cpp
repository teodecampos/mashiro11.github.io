#include "GerenteLogin.h"

#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0);
#else
	#define DEBUG_PRINT(x)  
#endif

GerenteLogin::GerenteLogin()
{
}


GerenteLogin::~GerenteLogin()
{
}

void GerenteLogin::Iniciar() {
DEBUG_PRINT("GerenteLogin::Iniciar - inicio")
	//tenta fazer login via _entradaWebcam().
	//se não conseguir, faz via teclado
	_entradaTeclado();
DEBUG_PRINT("GerenteLogin::Iniciar - fim")
}

void GerenteLogin::_entradaTeclado() {
DEBUG_PRINT("GerenteLogin::_entradaTeclado - inicio")
	//pega as informações MATRICULA e SENHA via teclado
	//envia a interface de persistência para tentar efetuar login
	
	string mat;
	cout << "Matricula:";
	cin >> mat;
	cout << "Matricula inserida: " << mat << endl;
	cin >> mat;

DEBUG_PRINT("GerenteLogin::_entradaTeclado - fim")
}

Usuario GerenteLogin::Credencia(string matricula) {
	Usuario usuario("", matricula);
	if (false) { //usuario cadastrado
		cout << "Usuario cadastrado na base de dados" << endl;
		if (ReconheceFace(matricula)) {//reconhece o rosto
			//reconheceu pelo rosto
			//modifica a instância de usuario
			return usuario;
		}
		else {//caso nao reconhecido
			cout << "Usuario nao reconhecido" << endl;
			return usuario;
		}
	}
	else {//Usuario nao cadastrado
		cout << "Usuario nao cadastrado na base de dados" << endl;
		return usuario;
	}
}

bool GerenteLogin::ReconheceFace(string matricula) {
	if (false) {//caso reconheça pelo rosto
		cout << "Usuario reconhecido" << endl;
		return true;
	}
	else {//caso contrario
		cout << "Rosto nao reconhecido" << endl;
		return false;
	}
}

Usuario GerenteLogin::NovoUsuario(string matricula) {
	string nome;
	cout << "Nome: ";
	cin >> nome;
	Usuario usuario(nome, matricula);
	GerenteBD::InsereUsuario(usuario);
	return usuario;
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
