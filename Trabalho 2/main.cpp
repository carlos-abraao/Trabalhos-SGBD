#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

//Structs

struct registro{
	int id;
	string nome;
	string sobrenome;
	string cpf;
};

struct pagina{
	registro registros[1000];
};

struct tabela{
	pagina *paginas;
	int qtd_paginas;
};

//Pesquisar mais, estrutura de índice:    std::map<int chave, int id_pag, int id_reg,> indice;

int main(int argc, char const *argv[]){	
	//Abrindo o arquivo	
	ifstream arquivo;
	string linha;

	arquivo.open("nome.txt");

	//Importando os registros
	if(arquivo.is_open()){
		while(getline(arquivo,linha)){
			//Código de importação, aguardando pela organização
		}
	}else{
		cout << "ERRO: Não foi possivel abrir o arquivo!" << endl;
	}

	//Continuação do código
}