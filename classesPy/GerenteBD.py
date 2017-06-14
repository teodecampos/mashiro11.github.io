import sqlite3 as sql3 #utilização de sqlite3 como banco de dados

class GerenteBD:	#caso GerenteBD herdasse de outra classe, seria escrito>> class GerenteBD(OutraClasse):
	'Classe gerenciadora da interface com banco de dados'	#Linha de documentação
	#Cada classe possui uma string de documentacao que pode ser acessada por NomeDaClasse.__doc__.
	#o construtor da classe na linguagem python é o metodo __int__()
	#em python, o método de uma classe deve receber self como primeiro parâmetro de entrada
	def __init__(self):
		#inicializa o banco de dados
		print(GerenteBD.__doc__)
		print("Construtor de GerenteBD")
	
	#__del__() é o método destrutor, invocado ao chamar>> del obj
	def __del__(self):
		print("Destrutor de GerenteBD")

	def InsereUsuario(self):
		print("Insere um novo usuario")

	def BuscaUsuario(self):
		print("Insere um novo usuario")

	def AtualizaUsuario(self):
		print("Insere um novo usuario")
		
	def RemoveUsuario(self):
		print("Insere um novo usuario")






