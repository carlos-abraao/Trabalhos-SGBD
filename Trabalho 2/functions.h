#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

//Structs
struct registro {
	int id;
	string nome;
	string sobrenome;
	string cpf;
};

struct pagina {
	registro registros[1000];
};

struct tabela {
	pagina *paginas;
	int qtd_paginas;
};

int file() {
	/*
	Fun��o file(): Esta fun��o l� o arquivo com os dados e os aloca na nossa estrutura de dados
	Retorno: 
	- 0 para importa��o bem sucedida
	- 1 para erro de leitura.
	*/


	//Abrindo o arquivo	
	ifstream arquivo;
	string linha;
	arquivo.open("nome.txt");

	//Importando os registros
	if (arquivo.is_open()) {
		while (getline(arquivo, linha)) {
			//C�digo de indexar os registros, aguardando a estrutura dos dados.
			return 0;
		}
	}
	else {
		//Erro na leitura
		return 1;
	}


}