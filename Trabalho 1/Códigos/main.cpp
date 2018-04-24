//Alunos: Carlos Abraao - 401357 & Leonardo Monteiro - 388838
//Primeiro trabalho da disciplina de Sistema de Gerenciamento e Bancos de Dados - CK0117
//Índice B+
//

#include <iostream>
#include <unistd.h>
#include "bTreeIndex.h"

using namespace std;

int main(int argc, char const *argv[]){

	BTnode* root = NULL;

	int choose = -1;

	while(choose != 0){
	clear();
	cout << "+-------------------------------------------------------------------------------------+" << endl;
	cout << "|                                BTree+ Index System                                  |" << endl;
	cout << "+-------------------------------------------------------------------------------------+" << endl;
	cout << "Escolha uma função:" << endl << "(1) Inserir Elemento" << endl << "(2) Bulk-Loading" << endl << "(3) Buscar Elemento" << endl 
	<< "(4) Buscar Intervalo" << endl << "(5) Excluir Elmento" << endl << "(6) Imprimir Árvore" << endl << "(0) Turn-off" << endl;
	cin >> choose;
	cout << endl;
	switch(choose){
		case 0:
			break;
		case 1:
		{
			clear();
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			cout << "|                                     Inserção                                        |" << endl;
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			int a = 0;
			cout << "Informe o valor inteiro a ser inserido: ";
			cin >> a;
			if(insert(a,root) == 1){
				cout << endl << "Elemento inserido com sucesso!" << endl;
			}
			else{
				cout << endl << "ERRO: Elemento já existente!" << endl;
			}
			sleep(2.5);
			break;
		}
		case 2:
		{
			clear();
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			cout << "|                                   Bulk-Loading                                      |" << endl;
			cout << "+-------------------------------------------------------------------------------------+" << endl;
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
			
			if(bulkLoading(vector, size, root) == 1){
				cout << endl << "Bulk-Loading carregado com sucesso!" << endl;
				sleep(2.5);
			}else{
				cout << endl << "ERRO: Ocorreu um erro na inserção" << endl;
				sleep(4);
			}
			break;
		}
		case 3:
		{
			clear();
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			cout << "|                                      Busca                                          |" << endl;
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			int c;
			cout << "Informe o valor a ser buscado: ";
			cin >> c;
			if(find_eq(c,root) == 1){
				cout << endl << "Elemento econtrado!" << endl;
			}else{
				cout << "ERRO: Elemento não encontrado!" << endl;
			}
			sleep(2.5);
			break;
		}
		case 4:
		{
			clear();
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			cout << "|                                Busca por intervalo                                  |" << endl;
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			int d, e;
			cout << "De: ";
			cin >> d;
			cout << ", até: ";
			cin >> e;

			int aux;
			if(e > d){
				aux = e;
				e = d;
				d = aux;
			}

			int* range;

			range = find_rg(d,e,root);

			if(range != NULL){
				/*Podemos passar o vetor como parameto, alocar os resultados nele lá na função e retornar ele, assim
				poderemos usar um sizeof para calcular seu tamanho e poder exibi-lo.*/
				for (int i = 0; i < 1; ++i)
				{
					cout << range[i] << " ";
				}
				cout << endl << endl;
			}
			else{
				cout << "ERRO: Nenhum valor encontrado!" << endl << endl;
			}
			sleep(2.5);
			break;
		}
		case 5:
		{
			clear();
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			cout << "|                                     Exclusão                                        |" << endl;
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			int b;
			cout << "Informe o valor a ser excluido: ";
			cin >> b;
			if(deleteKey() == 1){
				cout << endl << "O elemento " << b << " foi excluído!"; 
			}
			else{
				cout << endl << "ERRO: o elemento não existe!";
			}
			sleep(2.5);
			break;
		}
		case 6:
		{
			clear();
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			cout << "|                                     Imprimir                                        |" << endl;
			cout << "+-------------------------------------------------------------------------------------+" << endl;
			cout << endl;
			emOrdem(root);
			char io[2];
			cout << endl << "Retornar [S/N]: ";
			cin >> io;
			break;
		}
		default:
			cout << "+----------------------------ERRO: Insira uma opção válida----------------------------+" << endl << endl;
	}

	}

	cout << "+-------------------------------------------------------------------------------------+" << endl;
	cout << "|                                      Good bye                                       |" << endl;
	cout << "+-------------------------------------------------------------------------------------+" << endl;

	return 0;
}


