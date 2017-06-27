#include "CaraCracha.h"
#include <iostream>
using namespace std;
int main(void){
	CaraCracha user("Joao");
	int user_data;
	cout << "matricula: ";
	cin >> user_data;
	user.setMatricula(user_data);
	cout << endl << user.getNome() << ", sua matricula eh: " << user.getMatricula() << endl;
return 0;
}