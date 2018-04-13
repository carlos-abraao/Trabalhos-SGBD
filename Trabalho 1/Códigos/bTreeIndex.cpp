//Alunos: Carlos Abraao - 401357 & Leonardo Monteiro - 388838
//Primeiro trabalho da disciplina de Sistema de Gerenciamento e Bancos de Dados - CK0117
//Índice B+
//

#include <iostream>
#include "bTreeIndex.h"

using namespace std;

int main(int argc, char const *argv[]){
	clear();
/*
	BTnode* newroot = NULL;

	insert(1, newroot);
	insert(10, newroot);
	insert(2, newroot);
	insert(7, newroot);
	insert(4, newroot);
	insert(8, newroot);
	insert(5, newroot);
	insert(3, newroot);
	insert(11, newroot);
	insert(6, newroot);
	insert(9, newroot);
	insert(0, newroot);

	print_nodeinfo(newroot);
	cout << endl;cout << endl;
	print_nodeinfo(newroot->childs[0]);
	cout << endl;cout << endl;
	print_nodeinfo(newroot->childs[1]);
	cout << endl;cout << endl;	

	emOrdem(newroot);

	cout << endl;
*/

	BTnode* newroot = NULL;
	
	insert(20, newroot);
	insert(40, newroot);
	insert(50, newroot);
	insert(10, newroot);
	insert(60, newroot);
	insert(90, newroot);
	insert(30, newroot);
	insert(70, newroot);
	insert(80, newroot);

	emOrdem (newroot);

	insert(100, newroot);

	emOrdem (newroot);

	bool  v = find_eq(20, newroot);

	cout << "20: " << v << endl;


	v = find_eq(25, newroot);

	cout << "25: " << v << endl;

	int* vetor = find_rg(30, 70, newroot);	

	for (int i = 0; i < 5; ++i) cout << vetor[i] << " ";

	cout << endl;

	return 0;
}


