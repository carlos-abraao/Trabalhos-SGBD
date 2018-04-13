//Alunos: Carlos Abraao - 401357 & Leonardo Monteiro - 388838
//Primeiro trabalho da disciplina de Sistema de Gerenciamento e Bancos de Dados - CK0117
//Índice B+
//

#include <iostream>
#include "bTreeIndex.h"

using namespace std;

int main(int argc, char const *argv[]){

	BTnode* root  = NULL;
	BTnode* left  = NULL;
	BTnode* right = NULL;

	int choose = -1;

	cout << "+-------------------------------------------------------------------------------------+" << endl;
	cout << "|                                BTree+ Index System                                  |" << endl;
	cout << "+-------------------------------------------------------------------------------------+" << endl;

	while(choose != 0){
	cout << "Escolha uma função:" << endl << "(1) Inserção" << endl << "(2) Exclusão" << endl 
	<< "(3) Busca por igualdade" << endl << "(4) Busca por intervalo" << endl << "(5) Bulk-Loading" << endl << "(0) Turn-off" << endl;
	cin >> choose;
	cout << endl;
	switch(choose){
		case 0:
			break;
		case 1: 
			int a;
			cout << "Informe o valor inteiro a ser inserido: ";
			cin >> a;
			insert(a,root);  
			break;
		case 2:
			int b;
			cout << "Informe o valor a ser excluido: ";
			cin >> b;
			//Função Excluir
			break;
		case 3:
			int c;
			cout << "Informe o valor a ser buscado: ";
			cin >> c;
			if(find_eq(c,root) == 0){
				cout << "+---------------------------Inserção carregada com sucesso!---------------------------+" << endl << endl;
			}else{
				cout << "+--------------------------ERRO: Falha na inserção inserção!--------------------------+" << endl << endl;
			}
			break;
		case 4:
			int d, e;
			cout << "Informe o primeiro valor do intervalo: ";
			cin >> d;
			cout << "Informe o segundo valor do intervalo: ";
			cin >> e;

			int aux;
			if(k1 > k2){
				aux = k2;
				k2 = k1;
				k1 = aux;
			}
			int range[k2-k1];

			if(find_rg(d,e,root) != NULL){
				for (int i = 0; i < k2-k1; ++i)
				{
					cout << range[i] << " ";
				}
				cout << endl < endl;
			}
			else{
				cout << "+-------------------------------Nenhum valor encontrado-------------------------------+" << endl << endl;
			}
			break;
		case 5:
			int size = 0;
			cout << "Informe a quantidade de valores que serão inseridos: ";
			cin >> size;
			int vector[size];
			int f;
			cout << endl << "Informe a seguir o conjunto de valores que deseja inserir (0 para parar):" << endl;
			for(int i = 0; i < size; i++){
				cin >> f;
				vector[i] = f;
			}
			if(/*Função Bulk-Loading*/ == 0){
				cout << "+-------------------------Bulk-Loading carregado com sucesso!-------------------------+" << endl << endl;
			}else{
				cout << "+--------------------------ERRO: Ocorreu um erro na inserção--------------------------+" << endl << endl;
			}
			
			break;
		default:
			cout << "+----------------------------ERRO: Insira uma opção válida----------------------------+" << endl << endl;
		}

	}

	cout << "+-------------------------------------------------------------------------------------+" << endl;
	cout << "|                                      Good bye                                       |" << endl;
	cout << "+-------------------------------------------------------------------------------------+" << endl;

	return 0;
}


