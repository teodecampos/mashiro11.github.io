#include "GerenteBD.h"

#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0);
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
	ifstream usuarios(dbName + ".txt");
	while (!usuarios.eof()) {
		stringstream aux;
		getline(usuarios, registro);
		aux << registro;
		aux >> matricula;	//extraindo informações posicionais de cada registro
		aux >> nome;		//pode ser feito assim
		dadosUsuarios[matricula] = nome;	//como por enquanto só tem o nome, fica só o nome mapeado pela matricula
	}
	for (map<string,string>::iterator it = dadosUsuarios.begin(); it != dadosUsuarios.end(); it++) {
		cout << "Chave: " << it->first << endl;
		cout << "	Valor: " << it->second << endl;
	}

	DEBUG_PRINT("GerenteDB::() - fim");
}


GerenteBD::~GerenteBD()
{
	//sqlite3_close(db);
}

void GerenteBD::InsereUsuario(Usuario &usuario) {
	DEBUG_PRINT("GerenteBD::InsereUsuario() - inicio")
	ofstream bdFile;
	bdFile.open(dbName+".txt", std::ofstream::app);
	bdFile << usuario.GetMatricula() << " " << usuario.GetNome() << endl;
	bdFile.close();
	DEBUG_PRINT("GerenteBD::InsereUsuario() - fim")
}

void GerenteBD::AtualizaUsuario() {
DEBUG_PRINT("GerenteBD::AtualizaUsuario() - inicio")

DEBUG_PRINT("GerenteBD::AtualizaUsuario() - fim")
}

Usuario GerenteBD::BuscaUsuario(string matricula) {
	DEBUG_PRINT("GerenteBD::BuscaUsuario() - inicio")
		return Usuario(matricula , dadosUsuarios[matricula]);	//como por enquanto é só matricula e nome, td ok
DEBUG_PRINT("GerenteBD::BuscaUsuario() - fim")
}

bool GerenteBD::ExisteUsuario(string matricula) {
	if (dadosUsuarios.find(matricula) != dadosUsuarios.end())
		return true;
	else return false;

}

void GerenteBD::RemoveUsuario() {
DEBUG_PRINT("GerenteBD::RemoveUsuario() - inicio")

DEBUG_PRINT("GerenteBD::RemoveUsuario() - fim")
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
