#include "Usuario.h"

Usuario::Usuario() {

}

Usuario::Usuario(string matricula, string nome) {
	this->nome = nome;
	this->matricula = matricula;
}

Usuario::Usuario(const Usuario &usuario) {
	this->nome = usuario.nome;
	this->matricula = usuario.matricula;
}

string Usuario::GetNome() {
	return nome;
}

string Usuario::GetMatricula() {
	return matricula;
}

string Usuario::GetSenha() {
	return senha;
}

void Usuario::SetNome(string nome) {
	this->nome = nome;
}

void Usuario::SetMatricula(string matricula) {
	this->matricula = matricula;
}

void Usuario::SetSenha(string senha) {
	this->senha = senha;
}