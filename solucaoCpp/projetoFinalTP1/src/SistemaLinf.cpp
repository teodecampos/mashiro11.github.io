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

void SistemaLinf::_LimpaTela() {
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif 
}

void SistemaLinf::_OpcaoInvalida() {
	cout << "Opcao invalida!" << endl;
	Sleep(3000);
}

void SistemaLinf::_Cabecalho() {
	_LimpaTela();
	cout << "/************************************************/" << endl;
	cout << "	Bem vindo ao sistema, " << usuarioLogado.GetNome() << "." << endl;
	cout << "/************************************************/" << endl;
}

void SistemaLinf::_NavegaConta() {
	bool stay = true;
	while (stay) {
		_Cabecalho();
		int opcao = _Opcoes();
		switch (opcao) {
		case 1:
			DEBUG_PRINT("Opcao " << opcao);
			_ReservaLaboratorio();
			break;
		case 2:
			DEBUG_PRINT("Opcao " << opcao);
			_EditaDadosPessoais();
			break;
		case 3:
			DEBUG_PRINT("Opcao " << opcao);
			stay = false;
			usuarioLogado = Usuario();
			break;
		default:
			_OpcaoInvalida();
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

void SistemaLinf::_ReservaLaboratorio() {
	bool stay = true;
	while (stay) {
		_Cabecalho();
		cout << "	Reserva de Laboratorio" << endl;
		cout << "/******************************/" << endl;
		_VerificaReserva();//verifica se o usuario ja possui reserva e mostra na tela
		int i = 1;
		int opcao;
		cout << "Escolha opcao desejada: " << endl;
		cout << i++ << " - Reservar laboratorio" << endl;
		cout << i++ << " - Cancelar reserva" << endl;
		cout << i++ << " - Sair" << endl;
		cin >> opcao;
		switch (opcao) {
		case 1:
			DEBUG_PRINT("Opcao " << opcao);
			_ReservarLab();
			break;
		case 2:
			DEBUG_PRINT("Opcao " << opcao);
			_CancelarReserva();
			break;
		case 3:
			DEBUG_PRINT("Opcao " << opcao);
			stay = false;
			break;
		default:
			_OpcaoInvalida();
		}
	}
}

void SistemaLinf::_ReservarLab() {
	cout << "Diga o horario e ta feito" << endl;
}

void SistemaLinf::_CancelarReserva() {
	cout << "Diga o numero da reserva e ta feito" << endl;

}
void SistemaLinf::_VerificaReserva() {
	cout << "Verifica se ja existem reservas" << endl;
}

void SistemaLinf::_EditaDadosPessoais() {
	bool stay = true;
	while (stay) {
		_Cabecalho();
		cout << "	Dados pessoais" << endl;
		cout << "/******************************/" << endl;
		cout << "Aqui a logica de saida: " << endl;
		int opcao;
		cin >> opcao;
		switch (opcao) {
		case 1:
			DEBUG_PRINT("Opcao " << opcao);
			break;
		case 2:
			DEBUG_PRINT("Opcao " << opcao);
			break;
		case 3:
			DEBUG_PRINT("Opcao " << opcao);
			stay = false;
			break;
		default:
			_OpcaoInvalida();
		}
	}
}

void SistemaLinf::_EfetuaLogin() {
	string matricula;
	DEBUG_PRINT("Rodando Sistema");
	_LimpaTela();
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