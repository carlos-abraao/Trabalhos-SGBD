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
	Função file(): Esta função lê o arquivo com os dados e os aloca na nossa estrutura de dados
	Retorno: 
	- 0 para importação bem sucedida
	- 1 para erro de leitura.
	*/


	//Abrindo o arquivo	
	ifstream arquivo;
	string linha;
	arquivo.open("nome.txt");

	//Importando os registros
	if (arquivo.is_open()) {
		while (getline(arquivo, linha)) {
			//Código de indexar os registros, aguardando a estrutura dos dados.
			return 0;
		}
	}
	else {
		//Erro na leitura
		return 1;
	}


}