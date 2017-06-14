import cv2	# aqui é bom dizer quais funções vai importar, para não deixar o processo muito lento por importar tudo

#mais informações sobre python orientado a objeto: https://www.tutorialspoint.com/python/python_classes_objects.htm
#referencia para documentacao Doxygen: https://stackoverflow.com/questions/4302870/doxygen-syntax-in-python


class GerenteLogin:
	"""@brief Classe responsável por gerenciar acesso do usuário ao sistema
	
	A classe GerenteLogin é a responsável por obter a credencial de acesso
	para um usuário. A tentativa padrão de acesso se dá via webcam,
	fazendo uso da biblioteca openCV para identificação facial.
	Caso a identificação facial falhe, será dado ao usuário a opção de
	tentar fazer o login via teclado, com um nome de usuário e senha.
	"""
	__sessaoFinalizada = False
	def __init__(self, entrada):
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
