#include "SistemaLinf.h"

#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
#define DEBUG_PRINT(x)  
#endif


SistemaLinf::SistemaLinf() {


}

void SistemaLinf::Run() {
	while (true) {
		_EfetuaLogin();
		_NavegaConta();
	}
}

void SistemaLinf::LimpaTela() {
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif 
}

void SistemaLinf::_NavegaConta() {
	LimpaTela();
	cout << "/************************************************/" << endl;
	cout << "	Bem vindo ao sistema, " << usuarioLogado.GetNome() << "." << endl;
	cout << "/************************************************/" << endl;
	bool stay = true;
	while (stay) {
		int opcao = _Opcoes();
		switch (opcao) {
		case 1:
			DEBUG_PRINT("Opcao 1");
			break;
		case 2:
			DEBUG_PRINT("Opcao 2");
			break;
		case 3:
			DEBUG_PRINT("Opcao 3");
			stay = false;
			usuarioLogado = Usuario();
			break;
		default:
			cout << "Opcao invalida!" << endl;
		}
	}
}

int SistemaLinf::_Opcoes() {
	int i = 1;
	int opcao;
	cout << "Escolha opcao desejada: " << endl;
	cout << i++ << " - Reserva de laboratorio" << endl;
	cout << i++ << " - Editar dados pessoais" << endl;
	cout << i++ << " - Logout" << endl;
	cin >> opcao;
	return opcao;

}
void SistemaLinf::_EfetuaLogin() {
	string matricula;
	DEBUG_PRINT("Rodando Sistema");
	LimpaTela();
	cout << "/******************************/" << endl;
	cout << "	Tela de Login" << endl;
	cout << "/******************************/" << endl;
	cout << "Insira a matricula: ";
	cin >> matricula;
	Usuario usuario(GLog.Credencia(matricula));
	if (usuario.GetNome() != "") {//usuario cadastrado
		DEBUG_PRINT("Usuario logado com sucesso");
		usuarioLogado = usuario;
	}
	else {//usuario não cadastrado
		cout << "Usuario nao cadastrado" << endl;
		string resposta;
		while (true)
		{
			cout << "Cadastrar novo usuario? S/N: ";
			cin >> resposta;
			if (resposta == "s" || resposta == "S") {
				GLog.NovoUsuario(matricula);
				break;
			}
			else {
				break;
			}
		}
	}
}
#ifdef DEBUG
#undef DEBUG
#endif // DEBUG