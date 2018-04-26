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

struct pagina_func{
	registro_func registros[16];
};

struct pagina_venda{
	registro_venda registros[16];
};

struct tabela{
	pagina_func *paginas_func;
	pagina_venda *paginas_venda;
	int qtd_paginas;
};

tabela tab1, tab2;
int last_ind;

void copy_func(registro_func copy, registro_func &paste){
	paste.id_func   = copy.id_func  ;
	paste.nome      = copy.nome     ;
	paste.sobrenome = copy.sobrenome;
	paste.idade     = copy.idade    ;

}

void print_func(registro_func reg){
	cout << "id: " 		<< reg.id_func   << endl;
	cout << "nome: " 	<< reg.nome      << endl;
	cout << "sobrenome:"<< reg.sobrenome << endl;
	cout << "idade: " 	<< reg.idade     << endl;

}

void print_pag_func(pagina_func pag){
	for (int i = 0; i < 16; ++i){
		print_func(pag.registros[i]);
		cout << endl;
	}
	cout << endl;

}

void init_bank(const char* filename1, const char* filename2){
	cout << filename1 << endl;

	ifstream dados(filename1, ifstream::in);
	string linha;

	if (dados.fail()){
		cerr << "     File \"" << filename1 << "\" not found." << endl;
		exit(1);
	}

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
			copy_func(regf, pagf.registros[ind_pag++]) ;
		}
		else{
			ind_pag = 0;
			paginas.push_back(pagf);
		}

		last_ind = ind_pag;
		
		tab1.paginas_venda = NULL;
		tab1.paginas_func = new pagina_func [paginas.size()];
		tab1.qtd_paginas = paginas.size();

		list <pagina_func>::iterator it; i = 0;

		for (it = paginas.begin(); it != paginas.end(); it++){
			tab1.paginas_func[i++] = *it;
		}
		
	}

}


void teste(){
	int i;
	for (i = 0; i < tab1.qtd_paginas-1; ++i){	
		cout << "======================================= Registros da página " << i+1 << ": =======================================\n";
		print_pag_func(tab1.paginas_func[i]);

	}
	/*
	cout << "======================================= Registros da página " << i+1 << ": =======================================\n";
	for (int i = 0; i < last_ind; ++i){
		print_pag_func(tab1.paginas_func[i]);
		cout << endl;
	}
	/*
	for (int j = 0; j < last_ind; ++j){
		print_func(tab1.paginas_func[j].registros[j]);
		cout << endl;
	}*/
	cout << endl;

}


