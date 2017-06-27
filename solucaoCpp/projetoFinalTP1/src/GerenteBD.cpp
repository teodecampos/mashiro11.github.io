#include "GerenteBD.h"

//#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0)
#else
	#define DEBUG_PRINT(x) 
#endif

string GerenteBD::dbName("");
map<string, string> GerenteBD::dadosUsuarios;

GerenteBD::GerenteBD()
{
	DEBUG_PRINT("GerenteDB::() - inicio");
	dbName = "myDB";
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
	DEBUG_PRINT("GerenteDB::() - fim");
}


GerenteBD::~GerenteBD()
{
	//sqlite3_close(db);
}

void GerenteBD::InsereUsuario(Usuario &usuario) {
	DEBUG_PRINT("GerenteBD::InsereUsuario() - inicio");
	ofstream bdFile;
	bdFile.open(dbName+".txt", std::ofstream::app);
	bdFile << usuario.GetMatricula() << " " << usuario.GetNome() << endl;
	bdFile.close();
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
		if(uSenha == senha) return true;
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

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
