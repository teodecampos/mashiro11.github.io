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
		if (usuarioLogado.GetMatricula() != "") {
			_NavegaConta();
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
				usuarioLogado = GLog.NovoUsuario(matricula);
				break;
			}
			else {
				break;
			}
		}
	}
}

void SistemaLinf::_NavegaConta() {
	bool stay = true;
	while (stay) {
		_Cabecalho();
		int i = 1;
		int opcao;
		cout << "Escolha opcao desejada: " << endl;
		cout << i++ << " - Reserva de laboratorio" << endl;
		cout << i++ << " - Editar dados pessoais" << endl;
		cout << i++ << " - Logout" << endl;
		cin >> opcao;
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

void SistemaLinf::_ReservaLaboratorio() {
	bool stay = true;
	while (stay) {
		_Cabecalho();
		cout << "	Reserva de Laboratorio" << endl;
		cout << "/******************************/" << endl;
		//verifica se o usuario ja possui reserva e mostra na tela
		cout << "Suas reservas:" << endl;
		_ImprimeReservas( GerenteBD::BuscaReserva(usuarioLogado.GetMatricula(), "matricula") );
		int i = 1;
		int opcao;
		cout << "Escolha opcao desejada: " << endl;
		cout << i++ << " - Reservar laboratorio" << endl;
		cout << i++ << " - Cancelar reserva" << endl;
		cout << i++ << " - Voltar" << endl;
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
			GerenteBD::CommitReserva();
			stay = false;
			break;
		default:
			_OpcaoInvalida();
		}
	}
}

void SistemaLinf::_ReservarLab() {
	Reserva reserva;
	int i = 1;
	cout << "Escolha uma data (dd/mm): " << endl;
	cin >> reserva.data;
	vector<Reserva> reservasData = GerenteBD::BuscaReserva(reserva.data, "data");
	_ImprimeReservas(reservasData);
	cout << "Escolha um laboratorio (1 a 5): ";
	cin >> reserva.laboratorio;
	cout << "Horarios: " << endl;
	cout << i++ << " - 8h-10h" << endl;
	cout << i++ << " - 10h-12h" << endl;
	cout << i++ << " - 12h-14h" << endl;
	cout << i++ << " - 14h-16h" << endl;
	cout << i++ << " - 16h-18h" << endl;
	cout << i++ << " - 20h-22h" << endl;
	cout << i++ << " - 22h-23h" << endl;
	cout << "Horario escolhido: ";
	cin >> reserva.hora;
	for (vector<Reserva>::iterator it = reservasData.begin(); it != reservasData.end();) {
		if (reserva.hora == it->hora && reserva.laboratorio == it->laboratorio) {
			it = reservasData.begin();
			cout << "Laboratorio ja reservado neste horario!" << endl;
			cout << "Escolha um laboratorio (1 a 5): ";
			cin >> reserva.laboratorio;
			cout << "Escolha um horario: ";
			cin >> reserva.hora;
			continue;
		}
		else {
			it++;
		}
	}
	reserva.matricula = usuarioLogado.GetMatricula();
	cout << "Reserva efetuada!" << endl;
	GerenteBD::InsereReserva(usuarioLogado.GetMatricula(), reserva);
	Sleep(3000);
}

void SistemaLinf::_ImprimeReservas(vector<Reserva> reservas) {
	if (reservas.size() != 0){
		for (unsigned int i = 0; i < reservas.size(); i++) {
			//cout << reservas[i]; //por algum motivo não quer funcionar direito
			reservas[i].ImprimeReserva();
		}
	}
}

void SistemaLinf::_CancelarReserva() {
	cout << "Diga o numero da reserva e ta feito" << endl;

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

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG