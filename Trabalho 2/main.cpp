#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"

using namespace std;

//Pesquisar mais, estrutura de índice:    std::map<int chave, int id_pag, int id_reg,> indice;

int main(int argc, char const *argv[]) {

	if (argc < 3) {
		cerr << "\nError - Adicione as instancias de dados na seguinte oredem: Dados funcionários, Dados Vendas" << endl;
		return 2;
	}

	init_bank(argv[1], argv[2]);

	//print_tab_ven();

	index indice = create_index_func(tab1);

	index indice2 = create_index_ven(tab2);

	cout << indice[9984].first << " " << indice[9984].second << endl;

	cout << tab1.paginas_func[indice[9984].first].registros[indice[9984].second].nome << endl << tab1.paginas_func[indice[9984].first].registros[indice[9984].second].sobrenome << endl;

	cout << tab2.paginas_venda[indice2[39996].first].registros[indice2[39996].second].nome_produto << endl << tab2.paginas_venda[indice2[39996].first].registros[indice2[39996].second].id_ven << endl << tab2.paginas_venda[indice2[39996].first].registros[indice2[39996].second].id_func << endl;	

	tabela_join join = nest_loop_index_join(indice);

	print_tab_join(join);
	
}
