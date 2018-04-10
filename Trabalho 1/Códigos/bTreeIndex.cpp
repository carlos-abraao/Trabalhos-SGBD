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
	bool d = insert(9, root);
	bool e = insert(8, root);
	bool f = insert(10, root);
	bool g = insert(11, root);


	cout << v << " " << d << " " << e << " " << f << " " << g << endl;

	cout << root -> keys[0] << endl;
	cout << root -> keys[1] << endl;
	cout << root -> keys[2] << endl;
	cout << root -> keys[3] << endl;

	return 0;
}