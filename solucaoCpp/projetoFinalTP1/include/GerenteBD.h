#ifndef GERENTE_BD 
#define GERENTE_BD

#include <iostream>
#include <fstream>
#include <string>
#include "Usuario.h"

/*!
*	\brief \c GerenteBD controla requisições ao banco de dados
*	
*	GerenteBD é responsável por promover a interface entre a camada de negócio
*	e a camada de persistência de dados.
*/
using std::cout;
using std::endl;
using std::string;
using std::ofstream;

class GerenteBD
{
public:
	GerenteBD();
	virtual ~GerenteBD();
	
	//CRUD Pessoa
	/*!
	*	\brief Insere um novo usuário no banco de dados.
	*	\param usuario Instancia de usuario a ser salvo no banco.
	*/
	static void InsereUsuario(Usuario &usuario);

	/*!
	*	\brief Busca um usuário no banco de dados.
	*/
	void BuscaUsuario();
	
	/*!
	*	\brief Atualiza um usuário no banco de dados.
	*/
	void AtualizaUsuario();

	/*!
	*	\brief Remove um usuário do banco de dados.
	*/
	void RemoveUsuario();
private:
	static string dbName;

};

#endif