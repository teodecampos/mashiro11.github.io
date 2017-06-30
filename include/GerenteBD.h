#ifndef GERENTE_BD 
#define GERENTE_BD

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include "Usuario.h"
#include "Reserva.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::map;
using std::vector;

/*!
*	\brief Controla requisições ao banco de dados
*
*	GerenteBD é responsável por promover a interface entre a camada de negócio
*	e a camada de persistência de dados.
*/
class GerenteBD
{
public:
	/*!
	*	\brief Construtor padrão
	*
	*	Na construção da instância de \c GerenteBD é feita a leitura
	*	dos arquivos com registros de usuários e registros das reservas.
	*/
	GerenteBD();

	/*!
	*	\brief Destrutor.
	*/
	virtual ~GerenteBD();
	
	//CRUD Pessoa
	/*!
	*	\brief Insere um novo usuário no banco de dados.
	*	\param usuario Instancia de usuario a ser salvo no banco.
	*/
	static void InsereUsuario(Usuario &usuario);

	/*!
	*	\brief Busca um usuário no banco de dados.
	*
	*	\param matricula Matricula do usuario
	*	\return Objeto usuario com os campos preenchidos
	*/
	static Usuario BuscaUsuario(string matricula);
	
	/*!
	*	\brief Atualiza um usuário no banco de dados.
	*/
	void AtualizaUsuario();

	/*!
	*	\brief Remove um usuário do banco de dados.
	*/
	void RemoveUsuario();

	/*!
	*	\brief Verifica a existencia de usuario.
	*	\param matricula Matricula de usuario.
	*	\return true caso a matricula exista no banco.
	*/
	static bool ExisteUsuario(string matricula);
	
	/*!
	*	\brief Verifica se a matricula confere com a senha.
	*	\param matricula Matricula do usuario.
	*	\param senha Senha a ser testada.
	*	\return Sretorna true apenas se a matricula existe e está associada à senha.
	*/
	static bool ChecaUsuario(string matricula, string senha);

	/*!
	*	\brief Executa as modificações sobre usuário na base de dados.
	*/
	static void CommitUsuario();

	//CRUD Reserva
	/*!
	*	\brief Salva um novo registro de reserva.
	*
	*	\param matricula Matrícula do usuário que efetuou reserva.
	*	\param reserva Objeto que contém as informações da reserva.
	*/
	static void InsereReserva(string matricula, Reserva reserva);

	/*!
	*	\brief Busca registros de reserva de acordo com o campo utilizado como critério de busca.
	*
	*	\param entrada Valor a ser comparado na busca.
	*	\param campo Informação da reserva a ser levada em consideração (data ou matricula).
		\return Vetor de registros que respondem à pesquisa.
	*/
	static vector<Reserva> BuscaReserva(string entrada, string campo);

	/*!
	*	\brief Cancela uma reserva.
	*
	*	\param numReserva Código da reserva a ser cancelada.
	*/
	static void CancelaReserva(string numReserva);

	/*!
	*	\brief Executa as modificações sobre reserva na base de dados.
	*/
	static void CommitReserva();

	/*!
	*	\brief Verifica se a data informada possui reservas.
	*
	*	\param data Data a ser verificada.
	*	\return \c true caso hajam reservas na data informada. \c false caso contrário. 
	*/
	static bool DataComReserva(string data);


private:
	/*!
	*	\brief Contador para gerar códigos de novas reservas.
	*/
	static int codigoReserva;

	/*!
	*	\brief Nome do arquivo detentor dos registros de usuario.
	*/
	static string dbName;

	/*!
	*	\brief Nome do arquivo detentor dos registros de reservas.
	*/
	static string dbReserva;

	/*!
	*	\brief Mapeamento de usuarios.
	*
	*	O mapeamento utiliza a matrícula do usuário para obter suas informações cadastrais.
	*/
	static map<string, string> dadosUsuarios;

	/*!
	*	\brief Mapeamento de registros de reservas.
	*
	*	O mapeamento é feito priorizando a busca por data (chave), 
	*	permitindo acesso aos registros de reservas daquele dia.
	*/
	static map<string, vector<Reserva>> dadosReservas;
};

#endif