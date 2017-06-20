import GerenteBD as GBD
import GerenteLogin as GLog


#o Idela é que a classe main seja responsável
#apenas por iniciar a execução do sistema,
#passando o controle para uma das classes que a compõe
objGLog = GLog.GerenteLogin()
objGLog.TelaInicial()

"""
objGDB = GBD.GerenteBD()
while(objGLog.SessaoFinalizada() != True):
	if(input()[0] == 'f'): objGLog.SetFimSessao(True)
"""