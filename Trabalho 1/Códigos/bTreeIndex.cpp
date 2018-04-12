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

	insert(6, root);
	insert(1, left);
	insert(2, left);
	insert(3, left);
	insert(4, left);
	insert(5, left);
	insert(6, right);
	insert(7, right);
	insert(8, right);
	insert(9, right);
	insert(10, right);

	root -> childs[0] = left;
	root -> childs[1] = right;
	root -> IsLeaf = 0;
	right -> IsLeaf = 0;
	left -> IsLeaf = 0;

	left -> next = right;
	right -> prev = left;

	//print_nodeinfo(right);

	//cout << endl;

	BTnode* newroot = NULL;

	insert(1, newroot);
	insert(10, newroot);
	insert(2, newroot);
	insert(7, newroot);
	insert(4, newroot);
	insert(8, newroot);
	insert(5, newroot);
	insert(3, newroot);
	insert(6, newroot);
	insert(9, newroot);
	insert(11, newroot);
	insert(0, newroot);

	print_nodeinfo(newroot);
	cout << endl;cout << endl;
	print_nodeinfo(newroot->childs[0]);
	cout << endl;cout << endl;
	print_nodeinfo(newroot->childs[1]);
	cout << endl;cout << endl;
	//print_nodeinfo(newroot->childs[1]->father);
	cout << endl;cout << endl;
	cout << endl;cout << endl;

	int* inter = find_rg(1,4, newroot);

	for (int i = 0; i < 4; ++i)
	{
		cout << inter[i] << " ";
	}
	cout << endl;



	return 0;
}


