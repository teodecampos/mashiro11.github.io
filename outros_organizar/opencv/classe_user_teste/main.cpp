#include "CaraCracha.h"

using namespace std;

int main(void){
	CaraCracha user("Joao");
	user.setMatricula();
	cout << user.getNome() << ", sua matricula eh: " << user.getMatricula() << endl;
return 0;
}