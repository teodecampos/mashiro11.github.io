#include "SistemaLinf.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
#define DEBUG_PRINT(x)  
#endif


SistemaLinf::SistemaLinf() {


}

void SistemaLinf::Run() {
	string matricula;
	DEBUG_PRINT("Rodando Sistema");
	cout << "Insira a matricula: ";
	cin >> matricula;
	Usuario usuario(GLog.Credencia(matricula));
	if (usuario.GetNome() != "") {//usuario cadastrado
		DEBUG_PRINT("Usuario logado com sucesso");
		cout << "Bem vindo ao sistema, " << usuario.GetNome() << "." << endl;
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
	cin >> matricula;
}
#ifdef DEBUG
#undef DEBUG
#endif // DEBUG