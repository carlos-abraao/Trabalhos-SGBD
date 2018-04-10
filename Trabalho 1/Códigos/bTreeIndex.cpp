//Alunos: Carlos Abraao - 401357 & Leonardo Monteiro - 388838
//Primeiro trabalho da disciplina de Sistema de Gerenciamento e Bancos de Dados - CK0117
//Índice B+
//

#include <iostream>
#include "bTreeIndex.h"

using namespace std;

int main(int argc, char const *argv[]){
	
	cout << "Hello World!\n";

	BTnode* root = NULL;

	bool v = insert(10, root);

	cout << v << endl;

	cout << root -> keys[0] << endl << root -> childs[0] -> keys[0] << endl;


	return 0;
}