//Alunos: Carlos Abraao - 401357 & Leonardo Monteiro - 388838
//Segundo trabalho da disciplina de Sistema de Gerenciamento e Bancos de Dados - CK0117
//Nested Loop Index Join

#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

// para compilar o programa é preciso utilizar o c++ 11, no terminal do linux é só rodar o comando : " g++ -std=c++11 main.cpp -o <nome-do executavel>"
// para rodar o executável é necessário passar os arquivo de dados como argumento, no terminal do linux: ./<nome-do executavel> data_funcionários data_vendas
// é importante que os argumentos sejam passados nessa ordem, caso contrário o programa não funcionará
// aparentemente o arquivo de saída está com um problema para os caracteres especias (ç, á, ó é, etc), não sei como reesolver isso

int main(int argc, char const *argv[]) {

	if (argc < 3) {
		cerr << "\nError - Adicione as instancias de dados na seguinte oredem: Dados funcionários, Dados Vendas" << endl;
		return 2;
	}

	init_bank(argv[1], argv[2]);						//Criando as tabelas	

	index indice = create_index_func(tab1);				//Criando o índice para a tabela de funcionários
	
	tabela_join join = nest_loop_index_join(indice);	//Fazendo a junção

	//print_tab_func(); 								//descomentar para imprimir os funcionários na tela

	//print_tab_ven();									//descomenar paa imprimir as vendas na tela

	//print_tab_join(join);								//descomenar paa imprimir as junções na tela

	file_tab_join(join);								//Gerando o arquivo de junção

	return 0;	
}
