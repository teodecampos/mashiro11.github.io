#ifndef __CaraCracha__
#define __CaraCracha__

#include <iostream>
/// Classe apenas para teste
class CaraCracha
{
public:
	/// metodo get
	int getMatricula();
	/// metodo get
	std::string getNome();
	/// metodo set
	void setMatricula();
	/// contrutor
	CaraCracha(std::string);
protected:
	/// numero da matricula
	int matricula;
	/// nome do individio
	std::string nome;
	};

#endif