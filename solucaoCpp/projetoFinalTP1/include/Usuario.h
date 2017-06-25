#pragma once
#ifndef __USUARIO__
#define __USUARIO__

#include <iostream>
#include <string>

using std::string;

/*!
*	\brief Representa a instância do usuario que utiliza o sistema.
*	
*	Contém as informações do usuário.
*/
class Usuario {
private:
	string nome;
	string matricula;

public:
	/*!
	*	\brief Construtor padrão
	*/
	Usuario();
	
	/*!
	*	\brief Construtor alternativo.
	*	\param nome Nome do usuario.
	*	\param matricula Matricula do usuario
	*/
	Usuario(string nome, string matricula);

	/*!
	*	\brief Construtor de cópia.
	*	\param user Usuario a ser copiado.
	*/
	Usuario(Usuario &user);

	/*!
	*	\brief Getter do atributo nome.
	*/
	string GetNome();
	
	/*!
	*	\brief Getter do atributo matricula.
	*/
	string GetMatricula();

	/*!
	*	\brief Setter do atributo nome.
	*	\param nome Nome designado para instancia.
	*/
	void SetNome(string nome);

	/*!
	*	\brief Setter do atributo matricula.
	*	\param matricula Matricula designada para instância.
	*/
	void SetMatricula(string matricula);

};

#endif // !__USUARIO__
