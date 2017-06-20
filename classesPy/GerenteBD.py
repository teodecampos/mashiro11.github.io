import sqlite3 as sql3 #utilização de sqlite3 como banco de dados
from os import system

class GerenteBD:	#caso GerenteBD herdasse de outra classe, seria escrito>> class GerenteBD(OutraClasse):
	'Classe gerenciadora da interface com banco de dados'	#Linha de documentação
	#Cada classe possui uma string de documentacao que pode ser acessada por NomeDaClasse.__doc__.
	#o construtor da classe na linguagem python é o metodo __int__()
	#em python, o método de uma classe deve receber self como primeiro parâmetro de entrada
	userBD = 0

	def __init__(self):
		#inicializa o banco de dados
		print(GerenteBD.__doc__)
		print("Construtor de GerenteBD")
		
	
	#__del__() é o método destrutor, invocado ao chamar>> del obj
	def __del__(self):
		print("Destrutor de GerenteBD")

	def InicializaBD(self):
		if GerenteBD.userBD == 0:
			userBD_Connection = sql3.connect("Usuarios.db")
			userBD_Cursor = userBD_Connection.cursor()
			userBD_Cursor.execute('''CREATE TABLE Users(nome text, login text, senha text)''')
			userBD_Connection.commit()
			userBD_Connection.close()
			GerenteBD.userBD = "Usuarios.bd"

	def InsereUsuario(self, user):
		print("Insere um novo usuario")
		if GerenteBD.userBD != 0:
			userBD_Connection = sql3.connect("Usuarios.db")
			userBD_Cursor = userBD_Connection.cursor()
			userBD_Cursor.execute("INSERT into Users VALUES('"+user[0]+"' ,'"+user[1]+"','"+user[2]+"')")
			userBD_Connection.commit()
			userBD_Connection.close()
		else:
			self.InicializaBD()
			userBD_Connection = sql3.connect("Usuarios.db")
			userBD_Cursor = userBD_Connection.cursor()
			userBD_Cursor.execute("INSERT into Users VALUES('"+user[0]+"' ,'"+user[1]+"','"+user[2]+"')")
			userBD_Connection.commit()
			userBD_Connection.close()


	@classmethod
	def BuscaUsuario(self, user):
		system('cls')
		print("Busca um usuario")
		if GerenteBD.userBD != 0:
			userCon = sql3.connect("Usuarios.db")
			userCursor = userCon.cursor()
			userCursor.execute("SELECT * FROM Users WHERE login =?", (user[0],))
			result = userCursor.fetchone()
			userCon.close()
			print(result)
		input("Em desenvolvimento. Pressione enter")


	def AtualizaUsuario(self):
		print("Atualiza um usuario")
		
	def RemoveUsuario(self):
		print("Remove um usuario")

"""
	#checa se o banco de dados existe
	#https://stackoverflow.com/questions/12932607/how-to-check-with-python-and-sqlite3-if-one-sqlite-database-file-exists
	def isSQLite3(filename):
    	from os.path import isfile, getsize

    	if not isfile(filename):
        	return False
    	if getsize(filename) < 100: # SQLite database file header is 100 bytes
        	return False

    	with open(filename, 'rb') as fd:
        	header = fd.read(100)

    	return header[:16] == 'SQLite format 3\x00'



"""