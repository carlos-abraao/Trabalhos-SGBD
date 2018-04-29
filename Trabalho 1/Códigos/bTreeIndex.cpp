//Alunos: Carlos Abraao - 401357 & Leonardo Monteiro - 388838
//Primeiro trabalho da disciplina de Sistema de Gerenciamento e Bancos de Dados - CK0117
//Índice B+
//

#include <iostream>
#include "bTreeIndex.h"

using namespace std;

int main(int argc, char const *argv[]){

	BTnode* newroot = NULL;
	
	insert(20, newroot); 		//inserir

	remove(20, newroot); 		//remover

	find_eq(20, newroot); 		//busca igualdade

	find_rg(20, 30, newroot); 	//busca intervalo

	emOrdem (newroot);			//mostrar árvore (executar essa função apenas uma vez por árvore)

	int *vet, size = 5;

	vet = new int [size];

	bulkLoading(vet, size, newroot);	//carregamento em massa


	return 0;
}


