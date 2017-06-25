#include "Usuario.h"

Usuario::Usuario() {

}

Usuario::Usuario(string matricula, string nome) {
	this->nome = nome;
	this->matricula = matricula;
}

Usuario::Usuario(Usuario &usuario) {
	this->nome = usuario.nome;
	this->matricula = usuario.matricula;
}

string Usuario::GetNome() {
	return nome;
}

string Usuario::GetMatricula() {
	return matricula;
}

void Usuario::SetNome(string nome) {
	this->nome = nome;
}

void Usuario::SetMatricula(string matricula) {
	this->matricula = matricula;
}