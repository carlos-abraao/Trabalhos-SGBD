//Alunos: Carlos Abraao - 401357 & Leonardo Monteiro - 388838
//Primeiro trabalho da disciplina de Sistema de Gerenciamento e Bancos de Dados - CK0117
//Índice B+
//

#include <iostream>
#include "bTreeIndex.h"

using namespace std;

int main(int argc, char const *argv[]){
	
	cout << "Hello World!\n";

	BTnode* root  = NULL;
	BTnode* left  = NULL;
	BTnode* right = NULL;

	bool v = insert(6, root);
	bool d = insert(1, left);
	 d = insert(2, left);
	 d = insert(3, left);
	 d = insert(4, left);
	 d = insert(5, left);
	 d = insert(6, right);
	 d = insert(7, right);
	 d = insert(8, right);
	 d = insert(9, right);
	 d = insert(10, right);

	root -> childs[0] = left;
	root -> childs[1] = right;
	root -> IsLeaf = 0;

	left -> next = right;
	right -> prev = left;

	for (int i = 0; i < 9; ++i) cout << root -> childs[0] -> keys[i] << " ";
	cout << endl;

	for (int i = 0; i < 9; ++i) cout << root -> childs[1] -> keys[i] << " ";
	cout << endl;

	d = find_eq(10, root);

	cout << d << endl;


	return 0;
}