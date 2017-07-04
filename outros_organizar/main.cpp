#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //sleep();
#include <string.h>
#include <iostream>
#include <time.h>

#include <dirent.h>
#include <sys/types.h>

#include "lib.h"

using namespace std;

int main(void)
{
        char escolha;
        do {
                system("cls");
                cout << "\n Cadastro de Usuario\n\n";
                cout << "Escolha uma opcao: \n\n";
                cout << "1 - Insere Dados\n";
                cout << "2 - Busca Dados\n";
                cout << "3 - Edita Dados\n";
                cout << "4 - Deleta Dados\n";
                cout << "5 - Ver Diretorio\n";
                cout << "6 - Sair\n\n";

                cin >> escolha;

                switch(escolha) {
                        case '1':
								insere();
                                break;
                        case '2':
                        		busca();
                                break;
                        case '3':
								edita();
                                break;
                        case '4':
								deleta();
                                break;
                        case '5':
                        		dir();
                                break;
                        case '6':
                                exit(0);
                                break;
                        default:
                        		cout << "Digite uma opcao valida!";
                                sleep(1);
                                break;
                }
        }
        while (escolha > 0);
        return 0;
}

#include "functions.cpp"