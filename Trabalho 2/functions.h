#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <stdlib.h>

using namespace std;

//Structs, feitos a partir das especifica��es
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

// Esse struct ser� utilizado na tebela que ser� o resultado da join
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

// P�gina da tabela resultado da join
struct pagina_join{
	registro_join registros[16];
};

struct tabela{
	pagina_func *paginas_func;
	pagina_venda *paginas_venda;
	int qtd_paginas;
};

//Tabela resultado da join
struct tabela_join{
	pagina_join *paginas_join;	
	int qtd_paginas;
};

//Vari�veis globais, preferi deixar as tabelas acess�veis por todo o programa, como este c�digo faz uma tarefa bem controlada, n�o vi problemas
tabela tab1, tab2;						//tab1 ser� a tabela de funcin�rios e tab2 a tabela de vendas						
int last_indf, last_indv, last_indj;	//Essas vari�veis ser�o utilizadas para armazenar quantidade de registros que a �ltima p�gina de cada tabe�a possui, j� que elan precisa ter exatamente 16 registros
typedef pair <int, int> pagtup;			//Vari�vel auxiliar para o indice
typedef map <int, pagtup> index;		//Declara��o do tipo do �nd�ce, basicamente um map<int, (int, int)>


//Fun��o auxiliar que recebe dois registros do tipo funcion�rios e copia os conte�deos de um para o outro
void copy_func(registro_func copy, registro_func &paste){
	paste.id_func   = copy.id_func  ;
	paste.nome      = copy.nome     ;
	paste.sobrenome = copy.sobrenome;
	paste.idade     = copy.idade    ;

}

//Fun��o auxiliar que recebe dois registros do tipo venda e copia os conte�deos de um para o outro
void copy_ven(registro_venda copy, registro_venda &paste){
	paste.id_ven   	   = copy.id_ven  	  ;
	paste.id_func      = copy.id_func     	  ;
	paste.nome_produto = copy.nome_produto;
	paste.qtd     	   = copy.qtd    	  ;
	
}

//Fun��o auxiliar que imprime um �nico registro do tipo funcion�rio
void print_func(registro_func reg){
	cout << "id: " 		<< reg.id_func   << endl;
	cout << "nome: " 	<< reg.nome      << endl;
	cout << "sobrenome: "<< reg.sobrenome << endl;
	cout << "idade: " 	<< reg.idade     << endl;

}

//Fun��o auxiliar que imprime um �nico registro do tipo venda
void print_ven(registro_venda reg){
	cout << "id venda: "	   << reg.id_ven   	   << endl;
	cout << "id funcionario: " << reg.id_func 	   << endl;
	cout << "produto: " 	   << reg.nome_produto << endl;
	cout << "quantidade: " 	   << reg.qtd     	   << endl;

}

//Fun��o auxiliar que imprime uma �nica p�gina do tipo funcion�rio
void print_pag_func(pagina_func pag){
	for (int i = 0; i < 16; ++i){
		print_func(pag.registros[i]);
		cout << endl;
	}
	cout << endl;

}

//Fun��o auxiliar que imprime uma �nica p�gina do tipo venda
void print_pag_ven(pagina_venda pag){
	for (int i = 0; i < 16; ++i){
		print_ven(pag.registros[i]);
		cout << endl;
	}
	cout << endl;

}

//Fun��o que cria as tabelas de funcion�rios e vendedor a partir dos arquivos de entrada. s� funciona se o primeiro arquivo a ser passado for o de funcion�rios e o segundo o de vendas
void init_bank(const char* filename1, const char* filename2){

	ifstream dados(filename1, ifstream::in);	//dados ir� ler o arquivo de funcion�rios 
	ifstream dados2(filename2, ifstream::in);	//dados2 er� ler o arquivo de vendas
	string linha;	//vari�vel auxiliar, que ir� receber o conte�do de cada linha dos arquivos

	if (dados.fail() || dados2.fail()){		//Se a leitura de alguns dos arquivos fallhar, fecha o programa
		cerr << "     File \"" << filename1 << "\" not found." << endl;
		exit(1);
	}

	//=======================Criando a tabela de funcion�rios=====================================

	int ind_pag = 0;	//vari�vel auxiliar para gerenciar o espa�o dispon�vel na p�gina
	
	list <pagina_func> paginas;		//Lista utilizada para armazenar as p�ginas j� criadas, essencilamente possui todas as informa��es de uma tabela
	pagina_func pagf;				//pagina auxiliar, usada na montagem da tabela
	registro_func regf;				//registro auxiliar utilizado na montagem de cada p�gina

	//vari�veis auxiliares que ir�o receber os valores de cada linha e ser�o utililzadas para a montagem de cada registro
	int id_linha, age_linha;			
	string nome_linha, sobn_linha, aux;

	//vari�vel auxiliar do tipo ponteiro de string, que aopntar� para a posi��o da primeira virgula de cada linha
	string::size_type sz;
	//vari�veis auxiliares que ser�o utilizadas para caminhar na linha
	int j, i;

	while (dados.eof() == false) {
		getline(dados, linha);

		if (linha[0] == '\0') break;		

		id_linha = stoi (linha, &sz);	//essa fun��o converte a primeira parte da string em inteiro e atribui � id_linha, e retorna a posi��o da primeira coisa "n�o inteiro" para sz, que no caso � uma virgula

		j = static_cast<int>(sz);		//j recebe o valor de sz
		j++; i = j;						//incrementa j, pois este est� na posi��o de uma virgula e agora i e j est�o na mesma posi��o

		while(linha[i] != ',') i++;		//ao sair desse while, i est� apontando para a posi��o da pr�xima virgula		

		nome_linha = linha.substr(j, i-j);	//a fun��o substr, pega a substring a partir da posi��o j at� i-j pois��es � frente

		//o mesmo processo � repetido para o sobre nome
		j = ++i;

		while(linha[i] != ',') i++;

		sobn_linha = linha.substr(j, i-j);

		//nesse momento, na linha s� sobrou o ultimo valor que � um inteiro
		age_linha = stoi (linha.substr(++i), NULL);

		//passando os valores da linha para o registro auxiliar
		regf.id_func = id_linha;
		regf.nome = nome_linha;
		regf.sobrenome = sobn_linha;
		regf.idade = age_linha;

		//nesse if eu passo o valor do registro auxiliar para a p�gina auxiliar
		if (ind_pag < 16){	//se a pag tiver espa�o, copio os valores de regf, para o registro atual(ind_pag) e aumento a qtde. de registros em 1
			copy_func(regf, pagf.registros[ind_pag++]);
		}
		else{ // se a p�gina estiver lotada
			ind_pag = 0;								//zero o contador de registro
			paginas.push_back(pagf);					//coloco as informa��es da p�gina na lista de p�ginas
			copy_func(regf, pagf.registros[ind_pag++]);	//insiro o registro atual na primeira posi��o da p�gina auxiliar e incrmento o n�mero de registros em um
		}				
		
	}

	last_indf = ind_pag;		// o last_ind recebe o valor da posi��o do �ltimo registro que foi inserido na �ltima p�gina

	paginas.push_back(pagf);	// colocando a ultima p�gina na lista de p�ginas, (caso o n�o tenha entrado no else para a �ltima p�gina)

	tab1.paginas_venda = NULL;	// apontando a parte de vendas de tab1 para null, pois tab1 armazaena funcion�rios
	tab1.paginas_func = new pagina_func [paginas.size()];	//a qtd de p�ginas � justamente o tamanho da lista de p�ginas
	tab1.qtd_paginas = paginas.size();

	list <pagina_func>::iterator it; i = 0;
	//transferindo as p�ginas da lista para a tabela
	for (it = paginas.begin(); it != paginas.end(); it++){
		tab1.paginas_func[i++] = *it;
	}

	dados.close();

	//=======================Criando a tabela de vendas=====================================
	// aqui acontece um procedimento exatamenta an�logo para a tabela de vendas

	ind_pag = 0;
	
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
		
	}

	last_indv = ind_pag;

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

//Nessa fun��o � criado um indice para a tabela de funcion�rios
index create_index_func(tabela tab){

	index ind;

	int i;
	//com esses dois "for" aninhados eu passo por toda a tebela
	for (i = 0; i < tab1.qtd_paginas-1; ++i){ // na vou na �ltima p�gina, pois l� pode ser que n�o existam 16 p�ginas
		for (int j = 0; j < 16; ++j){
			//no indice, a informa��es ser�o adicionadas da seguinte forma, o indice do funcion�rio ser� a chave, e o par (i,j) representa a p�gina da tabela que ele se encontra e a posi��o do registro nessa p�gina, respectivamente
			ind.insert(make_pair( tab1.paginas_func[i].registros[j].id_func, make_pair(i,j)));
		}
		
	}		
	for (int j = 0; j < last_indf; ++j){
		//adicionando a �ltima p�gina
		ind.insert(make_pair( tab1.paginas_func[i].registros[j].id_func, make_pair(i,j)));		
	}

	return ind;
}


//fun��o para criar um indice para vendas (n�o utilizada), segue a mesma ideia da fun��o anterior
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

//fun��es para imprimir o conte�do das tabelas em tela
void print_tab_func(){
	int i;
	for (i = 0; i < tab1.qtd_paginas-1; ++i){	
		cout << "======================================= Registros da p�gina " << i+1 << ": =======================================\n";
		print_pag_func(tab1.paginas_func[i]);

	}	
	cout << "======================================= Registros da p�gina " << i+1 << ": =======================================\n";	
	for (int j = 0; j < last_indf; ++j){
		print_func(tab1.paginas_func[i].registros[j]);
		cout << endl;
	}
	cout << endl;

}

void print_tab_ven(){
	int i;
	for (i = 0; i < tab2.qtd_paginas-1; ++i){	
		cout << "======================================= Registros da p�gina " << i+1 << ": =======================================\n";
		print_pag_ven(tab2.paginas_venda[i]);

	}	
	cout << "======================================= Registros da p�gina " << i+1 << ": =======================================\n";	
	for (int j = 0; j < last_indv; ++j){
		print_ven(tab2.paginas_venda[i].registros[j]);
		cout << endl;
	}
	cout << endl;

}

//fun��es com funcionamento an�logo �s anteriores, mas para a tabela da jun��o
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
	cout << "id do funcion�rio: " << reg.id_func      	  << endl; 
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
		cout << "======================================= Registros da p�gina " << i+1 << ": =======================================\n";
		print_pag_join(tabj.paginas_join[i]);

	}	
	cout << "======================================= Registros da p�gina " << i+1 << ": =======================================\n";	
	//cout << last_indv << " " << last_indf << " " << last_indj << endl;
	for (int j = 0; j < last_indv; ++j){
		print_join(tabj.paginas_join[i].registros[j]);
		cout << endl;
	}
	cout << endl;

}

//fun��es para cria��o do arquivo de s�ida de tabela de jun��o (segue o mesmo caminho da impress�o)
void file_join(registro_join reg, ofstream &saida){
	saida << "id da venda: " <<    	 		    reg.id_ven << endl; 
	saida << "id do funcion�rio: " <<          reg.id_func << endl; 
	saida << "nome do produto: " <<  	  reg.nome_produto << endl; 
	saida << "quantidade do produto: " <<      	   reg.qtd << endl; 
	saida << "nome do funcionario: " << 		  reg.nome << endl; 
	saida << "sobrenome do funcionario: " << reg.sobrenome << endl; 
	saida << "idade do funcionario: " << 		 reg.idade << endl; 	
}


void file_pag_join(pagina_join pag, ofstream &saida){
	for (int i = 0; i < 16; ++i){
		file_join(pag.registros[i], saida);
		saida << endl;
	}
	saida << endl;
}

void file_tab_join(tabela_join tabj){
	ofstream saida;
	saida.open("juncao.txt");
	int i;
	for (i = 0; i < tabj.qtd_paginas-1; ++i){	
		saida << "======================================= Registros da p�gina " << i+1 << ": =======================================\n";
		file_pag_join(tabj.paginas_join[i], saida);

	}	
	saida << "======================================= Registros da p�gina " << i+1 << ": =======================================\n";	
	//saida << last_indv << " " << last_indf << " " << last_indj << endl;
	for (int j = 0; j < last_indv; ++j){
		file_join(tabj.paginas_join[i].registros[j], saida);
		saida << endl;
	}
	saida << endl;
	saida.close();

}

//fun��o que realiza a jun��o
tabela_join nest_loop_index_join(index ind){

	//vari�veis auxiliares que ser�o utilizadas para a montagem de cada registro, p�gina e tabela
	registro_join regj;
	pagina_join   pagj;	
	list <pagina_join> joins;

	//vari�veis auxiliares de indices
	int ind_pag = 0;		
	int i;

	//aqui caminho por todas a p�ginas e registros de tab2, e a cada registro de vendas, posso acessar diretamente o registo do funcion�rio dessa venda, gran�as ao �ndice criado
	for (i = 0; i < tab2.qtd_paginas - 1; ++i){
		for (int j = 0; j < 16; ++j){
			//nesse "if" checo se a p�gina da tabela de jun��o est� lotada, se n�o adiciona o registro correspondente, se sim adiciono a mesma na lista de p�ginas da jun��o
			if (ind_pag < 16){
				//nessa linha eu fa�o a utiliza��o do indice, a fun��o copy_join deve receber um registro de cada tabela, o primeiro registro deve ser o funcion�rio da venda da itera��o atual
				//para acessar esse registro, uso o indice, com o id_func da venda atual que � "tab2.paginas_venda[i].registros[j].id_func", do jeito que o map foi montade, o campo ".first" � o n�mero da p�gina em tab1 e o campo ".second" � o n�mero do registro dessa p�gina
				//para acessar o registro da venda atual uso "tab2.paginas_venda[i].registros[j].id_func"
				//e usando as informa��es desses dois registros, monto o registro atual da tabela de join "pagj.registros[ind_pag]"
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

	joins.push_back(pagj);

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