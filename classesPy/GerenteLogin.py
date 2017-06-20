import cv2	# aqui é bom dizer quais funções vai importar, para não deixar o processo muito lento por importar tudo
from enum import Enum
from os import system

import GerenteBD as GBD

#mais informações sobre python orientado a objeto: https://www.tutorialspoint.com/python/python_classes_objects.htm
#referencia para documentacao Doxygen: https://stackoverflow.com/questions/4302870/doxygen-syntax-in-python

class TELA_INICIO(Enum):
	LOGIN = 1
	CADASTRO = 2
	SAIR = 3

class GerenteLogin:
	"""@brief Classe responsável por gerenciar acesso do usuário ao sistema
	
	A classe GerenteLogin é a responsável por obter a credencial de acesso
	para um usuário. A tentativa padrão de acesso se dá via webcam,
	fazendo uso da biblioteca openCV para identificação facial.
	Caso a identificação facial falhe, será dado ao usuário a opção de
	tentar fazer o login via teclado, com um nome de usuário e senha.
	"""
	__sessaoFinalizada = False
	def __init__(self):
		"""@brief Construtor de GerenteLogin

		Método de construção de GerenteLogin. No construtor, são estabelecidas
		as conexões necessárias (tais, tais e tais).

		@param entrada Entrada inicial de teste
		"""
		print(GerenteLogin.__doc__)
		print("Construtor de GerenteLogin")

	def __del__(self):
		"""@brief Construtor de GerenteLogin

		Método destrutor de GerenteLogin. São finalizadas
		as conexões necessárias (tais, tais e tais).

		@param <param> Descricao de <param>
		"""
		print("Destrutor de GerenteLogin")

	def SessaoFinalizada(self):
		"""@brief Construtor de GerenteLogin

		Método destrutor de GerenteLogin. São finalizadas
		as conexões necessárias (tais, tais e tais).

		@param <param> Descricao de <param>
		@return <return>
		"""
		return self.__sessaoFinalizada

	def SetFimSessao(self, fimSessao):
		"""@brief Construtor de GerenteLogin

		Método destrutor de GerenteLogin. São finalizadas
		as conexões necessárias (tais, tais e tais).

		@param <param> Descricao de <param>
		@return <return>
		"""
		self.__sessaoFinalizada = fimSessao

	def entradaCamera(self):
		"""@brief Construtor de GerenteLogin

		Método destrutor de GerenteLogin. São finalizadas
		as conexões necessárias (tais, tais e tais).

		@param <param> Descricao de <param>
		@return <return>
		"""
		print("Resolve Login via webcam")

	def entradaTeclado(self):
		"""@brief Construtor de GerenteLogin

		Método destrutor de GerenteLogin. São finalizadas
		as conexões necessárias (tais, tais e tais).

		@param <param> Descricao de <param>
		@return <return>
		"""
		print("Resolve login via teclado")

	def TelaInicial(self):
		opcao = 0
		while(opcao != 3):
			system('cls')
			print("Bem vindo ao Sistema LINF!")
			print("1 - Login")
			print("2 - Novo cadastro")
			print("3 - Sair")
			opcao = int(input("Opcao: "))
			#verificar como fazer o switch com enum!
			if opcao == 1:
				system('cls')
				self.TelaLogin()
			elif opcao == 2:
				system('cls')
				self.TelaCadastro()
				opcao = 0
			elif opcao == 3:
				print("Saindo...")
			else:
				print("Opcao invalida!")

	def TelaLogin(self):
		user = []
		login = input("Login: ")
		senha = input("Senha: ")
		user.append(login)
		user.append(senha)
		GBD.GerenteBD().BuscaUsuario(user)
		return user

	def TelaCadastro(self):
		user = []
		nome = input("Nome: ")
		login = input("Login: ")
		senha = input("Senha: ")
		user.append(nome)
		user.append(login)
		user.append(senha)
		GBD.GerenteBD().InsereUsuario(user)
		input("Usuario cadastrado com sucesso! Pressione enter")
