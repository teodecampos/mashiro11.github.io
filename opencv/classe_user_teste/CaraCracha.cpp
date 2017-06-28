#include "CaraCracha.h"

CaraCracha::CaraCracha( std::string user_name ): nome(user_name)
{}

int CaraCracha::getMatricula()
{
	return matricula;
}

std::string CaraCracha::getNome()
{
	return nome;
}

void CaraCracha::setMatricula()
{
	std::cout << "matricula: ";
	std::cin >> matricula;
	std::cout << std::endl;
}


