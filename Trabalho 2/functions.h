#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <stdlib.h>

using namespace std;

//Structs
struct registro_func{
	int id_func;
	string nome;
	string sobrenome;
	int idade;
};

struct registro_venda{
	int id_ven;
	int id_func;
	string nome_produto;
	int qtd;
};

struct registro_join{
	int id_ven;
	int id_func;
	string nome_produto;
	int qtd;
	string nome;
	string sobrenome;
	int idade;
};

struct pagina_func{
	registro_func registros[16];
};

struct pagina_venda{
	registro_venda registros[16];
};

struct pagina_join{
	registro_join registros[16];
};

struct tabela{
	pagina_func *paginas_func;
	pagina_venda *paginas_venda;
	int qtd_paginas;
};

struct tabela_join{
	pagina_join *paginas_join;	
	int qtd_paginas;
};

tabela tab1, tab2;
int last_indf, last_indv, last_indj;
typedef pair <int, int> pagtup;
typedef map <int, pagtup> index;

void copy_func(registro_func copy, registro_func &paste){
	paste.id_func   = copy.id_func  ;
	paste.nome      = copy.nome     ;
	paste.sobrenome = copy.sobrenome;
	paste.idade     = copy.idade    ;

}

void copy_ven(registro_venda copy, registro_venda &paste){
	paste.id_ven   	   = copy.id_ven  	  ;
	paste.id_func      = copy.id_func     	  ;
	paste.nome_produto = copy.nome_produto;
	paste.qtd     	   = copy.qtd    	  ;
	
}

void print_func(registro_func reg){
	cout << "id: " 		<< reg.id_func   << endl;
	cout << "nome: " 	<< reg.nome      << endl;
	cout << "sobrenome: "<< reg.sobrenome << endl;
	cout << "idade: " 	<< reg.idade     << endl;

}

void print_ven(registro_venda reg){
	cout << "id venda: "	   << reg.id_ven   	   << endl;
	cout << "id funcionario: " << reg.id_func 	   << endl;
	cout << "produto: " 	   << reg.nome_produto << endl;
	cout << "quantidade: " 	   << reg.qtd     	   << endl;

}

void print_pag_func(pagina_func pag){
	for (int i = 0; i < 16; ++i){
		print_func(pag.registros[i]);
		cout << endl;
	}
	cout << endl;

}

void print_pag_ven(pagina_venda pag){
	for (int i = 0; i < 16; ++i){
		print_ven(pag.registros[i]);
		cout << endl;
	}
	cout << endl;

}

void init_bank(const char* filename1, const char* filename2){

	ifstream dados(filename1, ifstream::in);
	ifstream dados2(filename2, ifstream::in);
	string linha;

	if (dados.fail() || dados2.fail()){
		cerr << "     File \"" << filename1 << "\" not found." << endl;
		exit(1);
	}

	//=======================Criando a tabela de funcionários=====================================

	int ind_pag = 0;	//variável auxiliar para gerenciar o espaço disponível na página
	
	list <pagina_func> paginas;
	pagina_func pagf;
	registro_func regf;

	int id_linha, age_linha;
	string nome_linha, sobn_linha, aux;
	string::size_type sz;

	int j, i;

	while (dados.eof() == false) {
		getline(dados, linha);

		if (linha[0] == '\0') break;		

		id_linha = stoi (linha, &sz);

		j = static_cast<int>(sz);
		j++; i = j;

		while(linha[i] != ',') i++;				

		nome_linha = linha.substr(j, i-j);

		j = ++i;

		while(linha[i] != ',') i++;

		sobn_linha = linha.substr(j, i-j);		

		age_linha = stoi (linha.substr(++i), NULL);		

		regf.id_func = id_linha;
		regf.nome = nome_linha;
		regf.sobrenome = sobn_linha;
		regf.idade = age_linha;

		if (ind_pag < 16){
			copy_func(regf, pagf.registros[ind_pag++]);
		}
		else{
			ind_pag = 0;
			paginas.push_back(pagf);
			copy_func(regf, pagf.registros[ind_pag++]);
		}

		last_indf = ind_pag;		
		
	}

	paginas.push_back(pagf);

	tab1.paginas_venda = NULL;
	tab1.paginas_func = new pagina_func [paginas.size()];
	tab1.qtd_paginas = paginas.size();

	list <pagina_func>::iterator it; i = 0;

	for (it = paginas.begin(); it != paginas.end(); it++){
		tab1.paginas_func[i++] = *it;
	}

	dados.close();

	//=======================Criando a tabela de vendas=====================================

	ind_pag = 0;	//variável auxiliar para gerenciar o espaço disponível na página
	
	list <pagina_venda> vendas;
	pagina_venda pagv;
	registro_venda regv;

	int idv_linha, idf_linha, qtd_linha;
	string prod_linha;

	j = 0, i = 0;

	while (dados2.eof() == false) {
		getline(dados2, linha);

		if (linha[0] == '\0') break;		

		idv_linha = stoi (linha, &sz);

		j = static_cast<int>(sz);
		j++; i = j;

		while(linha[i] != ',') i++;				

		idf_linha = stoi (linha.substr(j, i-j), NULL);

		j = ++i;

		while(linha[i] != ',') i++;

		prod_linha = linha.substr(j, i-j);		

		qtd_linha = stoi (linha.substr(++i), NULL);

		regv.id_ven  	  = idv_linha ;
		regv.id_func 	  = idf_linha ;
		regv.nome_produto = prod_linha;
		regv.qtd 		  = qtd_linha ;		

		if (ind_pag < 16){
			copy_ven(regv, pagv.registros[ind_pag++]);
		}
		else{
			ind_pag = 0;
			vendas.push_back(pagv);
			copy_ven(regv, pagv.registros[ind_pag++]);
		}

		last_indv = ind_pag;		
		
	}

	vendas.push_back(pagv);

	tab2.paginas_venda = new pagina_venda [vendas.size()];
	tab2.paginas_func =  NULL;
	tab2.qtd_paginas = vendas.size();

	list <pagina_venda>::iterator st; i = 0;

	for (st = vendas.begin(); st != vendas.end(); st++){
		tab2.paginas_venda[i++] = *st;
	}

	dados2.close();

}

index create_index_func(tabela tab){

	index ind;

	int i;
	for (i = 0; i < tab1.qtd_paginas-1; ++i){
		for (int j = 0; j < 16; ++j){
			ind.insert(make_pair( tab1.paginas_func[i].registros[j].id_func, make_pair(i,j)));
		}
		
	}		
	for (int j = 0; j < last_indf; ++j){
		ind.insert(make_pair( tab1.paginas_func[i].registros[j].id_func, make_pair(i,j)));		
	}

	return ind;
}

index create_index_ven(tabela tab){

	index ind;

	int i;
	for (i = 0; i < tab2.qtd_paginas-1; ++i){
		for (int j = 0; j < 16; ++j){			
			ind.insert(make_pair( tab2.paginas_venda[i].registros[j].id_ven, make_pair(i,j)));
		}
		
	}		
	for (int j = 0; j < last_indf; ++j){
		ind.insert(make_pair( tab2.paginas_venda[i].registros[j].id_ven, make_pair(i,j)));		
	}

	return ind;
}


void print_tab_func(){
	int i;
	for (i = 0; i < tab1.qtd_paginas-1; ++i){	
		cout << "======================================= Registros da página " << i+1 << ": =======================================\n";
		print_pag_func(tab1.paginas_func[i]);

	}	
	cout << "======================================= Registros da página " << i+1 << ": =======================================\n";	
	for (int j = 0; j < last_indf; ++j){
		print_func(tab1.paginas_func[i].registros[j]);
		cout << endl;
	}
	cout << endl;

}

void print_tab_ven(){
	int i;
	for (i = 0; i < tab2.qtd_paginas-1; ++i){	
		cout << "======================================= Registros da página " << i+1 << ": =======================================\n";
		print_pag_ven(tab2.paginas_venda[i]);

	}	
	cout << "======================================= Registros da página " << i+1 << ": =======================================\n";	
	for (int j = 0; j < last_indv; ++j){
		print_ven(tab2.paginas_venda[i].registros[j]);
		cout << endl;
	}
	cout << endl;

}

void copy_join(registro_func copy, registro_venda copie, registro_join &paste){
	paste.id_ven   	   = copie.id_ven  	   ;
	paste.id_func      = copie.id_func     ;
	paste.nome_produto = copie.nome_produto;
	paste.qtd     	   = copie.qtd    	   ;
	paste.nome 		   = copy.nome 	   	   ;
	paste.sobrenome	   = copy.sobrenome	   ;
	paste.idade		   = copy.idade	   	   ;
	
}

void print_join(registro_join reg){
	cout << "id da venda: " << reg.id_ven   	 		  << endl; 
	cout << "id do funcionário: " << reg.id_func      	  << endl; 
	cout << "nome do produto: " << reg.nome_produto 	  << endl; 
	cout << "quantidade do produto: " << reg.qtd     	  << endl; 
	cout << "nome do funcionario: " << reg.nome 		  << endl; 
	cout << "sobrenome do funcionario: " << reg.sobrenome << endl; 
	cout << "idade do funcionario: " << reg.idade		  << endl; 	
}


void print_pag_join(pagina_join pag){
	for (int i = 0; i < 16; ++i){
		print_join(pag.registros[i]);
		cout << endl;
	}
	cout << endl;
}

void print_tab_join(tabela_join tabj){
	int i;
	for (i = 0; i < tabj.qtd_paginas-1; ++i){	
		cout << "======================================= Registros da página " << i+1 << ": =======================================\n";
		print_pag_join(tabj.paginas_join[i]);

	}	
	cout << "======================================= Registros da página " << i+1 << ": =======================================\n";	
	for (int j = 0; j < last_indf; ++j){
		print_join(tabj.paginas_join[i].registros[j]);
		cout << endl;
	}
	cout << endl;

}

tabela_join nest_loop_index_join(index ind){

	registro_join regj;
	pagina_join   pagj;	
	list <pagina_join> joins;

	int ind_pag = 0;		
	int i;
	for (i = 0; i < tab2.qtd_paginas - 1; ++i){
		for (int j = 0; j < 16; ++j){
			if (ind_pag < 16){
			copy_join(tab1.paginas_func[ind[tab2.paginas_venda[i].registros[j].id_func].first].registros[ind[tab2.paginas_venda[i].registros[j].id_func].second], tab2.paginas_venda[i].registros[j], pagj.registros[ind_pag++]);
			}
			else{
				ind_pag = 0;
				joins.push_back(pagj);
				copy_join(tab1.paginas_func[ind[tab2.paginas_venda[i].registros[j].id_func].first].registros[ind[tab2.paginas_venda[i].registros[j].id_func].second], tab2.paginas_venda[i].registros[j], pagj.registros[ind_pag++]);
			}
		}		
		
	}

	for (int j = 0; j < last_indv; ++j){
			if (ind_pag < 16){
			copy_join(tab1.paginas_func[ind[tab2.paginas_venda[i].registros[j].id_func].first].registros[ind[tab2.paginas_venda[i].registros[j].id_func].second], tab2.paginas_venda[i].registros[j], pagj.registros[ind_pag++]);
			}
			else{
				ind_pag = 0;
				joins.push_back(pagj);
				copy_join(tab1.paginas_func[ind[tab2.paginas_venda[i].registros[j].id_func].first].registros[ind[tab2.paginas_venda[i].registros[j].id_func].second], tab2.paginas_venda[i].registros[j], pagj.registros[ind_pag++]);
			}
	}

	last_indj = ind_pag;

	tabela_join tabj;

	tabj.paginas_join = new pagina_join [joins.size()];
	
	tabj.qtd_paginas = joins.size();

	list <pagina_join>::iterator it; i = 0;

	for (it = joins.begin(); it != joins.end(); it++){
		tabj.paginas_join[i++] = *it;
	}

	return tabj;

}






