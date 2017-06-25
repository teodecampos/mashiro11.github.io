#include "GerenteBD.h"

#define DEBUG
#ifdef DEBUG
	#define DEBUG_PRINT(x) do{cout << x << endl;}while(0);
#else
	#define DEBUG_PRINT(x) 
#endif

string GerenteBD::dbName("");

GerenteBD::GerenteBD()
{
DEBUG_PRINT("GerenteDB::() - inicio")
	
	dbName = "myDB";
	//sqlite3_open(dbName.c_str(), &db);

DEBUG_PRINT("GerenteDB::() - fim")
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

void GerenteBD::BuscaUsuario() {
DEBUG_PRINT("GerenteBD::BuscaUsuario() - inicio")

DEBUG_PRINT("GerenteBD::BuscaUsuario() - fim")
}

void GerenteBD::RemoveUsuario() {
DEBUG_PRINT("GerenteBD::RemoveUsuario() - inicio")

DEBUG_PRINT("GerenteBD::RemoveUsuario() - fim")
}

#ifdef DEBUG
#undef DEBUG
#endif // DEBUG
