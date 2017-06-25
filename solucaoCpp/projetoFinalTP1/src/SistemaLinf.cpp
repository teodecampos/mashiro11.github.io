#include "SistemaLinf.h"

SistemaLinf::SistemaLinf() {


}

void SistemaLinf::Run() {
	string matricula;
	cout << "Rodando Sistema" << endl;
	cout << "Insira a matricula: ";
	cin >> matricula;
	Usuario usuario(GLog.Credencia(matricula));
	if (usuario.GetNome() != "") {//usuario cadastrado
		cout << "Usuario logado com sucesso" << endl;
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