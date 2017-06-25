/*
	Classe para armazenar informações dos usuários
*/
class Lista{
        public:
                int numero;
                const char *nome;
                const char *sobrenome;
                char *disciplina;
                void exibe();
};

/*
	Cria objeto usuário e cadastra no banco de dados
*/
void criaObj(signed long long int numero, std::string nome, std::string sobrenome);

/*
	Retorna 1 caso o arquivo exista
*/
int existencia(signed long long int numero);

/*
	Colhe as informações para inserção no banco de dados
*/
void insere();

/*
	Método criado para editar qualquer informação do usuário,
	inclusive adicionar várias disciplinas
*/
void edita();

/*
	Busca no banco de dados informações sobre o usuário especificado
*/
void busca();

/*
	Exclui o arquivo especificado
*/
void deleta();

/*
	Lista o diretório corrente
*/
void dir();