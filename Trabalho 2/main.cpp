#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

//Pesquisar mais, estrutura de índice:    std::map<int chave, int id_pag, int id_reg,> indice;

int main(int argc, char const *argv[]) {

	if (argc < 3) {
		cerr << "\nError - try: " << argv[0] << " input-instance-file" << endl;
		return 2;
	}

	init_bank(argv[1], argv[2]);

	teste();
	
	
	//Continuação da main, aguardando especificações
}
