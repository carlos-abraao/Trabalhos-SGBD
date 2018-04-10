/*
 * Arvore Binaria de Busca
 * Universidade Federal do Ceara
 * Tiberius O. Bonates
 */
#include <iostream>
#include <time.h>
using namespace std;

struct NoAB {
	int chave;
	NoAB *fesq;
	NoAB *fdir;
};

// Funcao auxiliar: cria um novo no com a chave dada
NoAB * criarNo(int chave) {
	NoAB * novo = new NoAB;
	novo->chave = chave;
	novo->fesq = NULL;
	novo->fdir = NULL;
	return novo;
}

void inserir(NoAB * &arvore, int chave) {
	if (arvore == NULL)
		arvore = criarNo(chave);
	else {
		if (chave <= arvore->chave)
			inserir(arvore->fesq, chave);
		else
			inserir(arvore->fdir, chave);
	}
}

// Desce pela arvore ate encontrar o elemento ou chegar a um
// ponteiro NULL
NoAB * buscar(NoAB *arvore, int chave) {
	if (arvore != NULL) {
		if (chave < arvore->chave)
			return buscar(arvore->fesq, chave);
		if (chave > arvore->chave)
			return buscar(arvore->fdir, chave);

		return arvore; // se chave == arvore->chave
	}
	return NULL;
}

// Retorna um ponteiro para o maior elemento da (sub-)arvore com
// raiz apontada pelo parametro p
NoAB * maior(NoAB *p) {
	if (p == NULL)
		return NULL;
	if (p->fdir != NULL)
		return maior(p->fdir);

	return p;
}

/* Encontra e remove o elemento com a chave fornecida.
 * Caso nao exista elemento com aquela chave, nenhuma alteracao e' feita.
 * Dependendo do numero de filhos do no fornecido, teremos um dos 3 casos:
 * 1. elemento e' uma folha => apagar elemento;
 * 2. elemento possui apenas um filho => desviar ponteiro do pai do elemento,
 *    fazendo-o apontar para o unico filho;
 * 3. elemento possui dois filhos => trocar elemento de posicao com seu
 *    "antecessor" na arvore e chamar a funcao recursivamente para apagar
 *    elemento (nesta segunda chamada, recairemos no caso 1 ou 2 acima.
 * Notar que o parametro "no" e' passado por referencia para que possa
 * ser modificado.
 */
void remover(NoAB * &no, int chave) {
	if (no == NULL)
		return;
	if (no->chave > chave)
		return remover(no->fesq, chave);
	if (no->chave < chave)
		return remover(no->fdir, chave);

	// Se tivermos encontrado o elemento a remover...

	// Obter o numero de filhos do no
	int nfilhos = (no->fesq?1:0) + (no->fdir?1:0);

	switch (nfilhos) {
	case 0: // Se no e' uma folha
		delete no;
		no = NULL;
		break;
	case 1: // Se no possui um apenas filho
		if (no->fesq != NULL) { // Se esse filho for o esquerdo
			NoAB *aux = no->fesq;
			delete no;
			no = aux;
		}
		else { // Se esse filho for o direito
			NoAB *aux = no->fdir;
			delete no;
			no = aux;
		}
		break;
	case 2: // Se no possui dois filhos
		// Obter ponteiro para antecessor
		// (antecessor e' o maior elemento da subarvore esquerda)
		NoAB *antecessor = maior(no->fesq);
		// Troca dados entre no atual e seu antecessor
		no->chave = antecessor->chave;
		antecessor->chave = chave;
		// Requisita a remocao do elemento na subarvore para onde
		// ele foi movido
		remover(no->fesq, chave);
	}
}

// Funcao auxiliar utilizada para imprimir dados durante um percurso
void visita(NoAB *no) {
	if (no != NULL) {
		cout << no->chave << " ";
	}
}

// Efetua um percurso em-ordem
void emOrdem(NoAB *no) {
	if (no != NULL) {
		emOrdem(no->fesq);
		visita(no);
		emOrdem(no->fdir);
	}
}

// Efetua um percurso pre-ordem
void preOrdem(NoAB *no) {
}

// Efetua um percurso pos-ordem
void posOrdem(NoAB *no) {
}

// Percurso em nivel -- usar uma fila
void emNivel(NoAB *p) {
}

// Rotina que gera em tela uma especificacao da arvore no
// formato DOT, do software Graphviz (graphviz.org).
// Obs.: Esta funcao segue o mesmo formato geral de um percurso.
void desenhar(NoAB *p) {
	if (p != NULL) {
		cout << "  n" << p << " [label=" << p->chave << "]" << endl;
		if (p->fesq != NULL)
			cout << "  n" << p << " -> n" << p->fesq << endl;
		if (p->fdir != NULL)
			cout << "  n" << p << " -> n" << p->fdir << endl;

		desenhar(p->fesq); // Aplicar o mesmo procedimento ao filho esquerdo
		desenhar(p->fdir); // Aplicar o mesmo procedimento ao filho direito
	}
}


// Efetua percurso pos-ordem, deletando nos
void destruir(NoAB * &p) {
	if (p == NULL)
		return;
	destruir(p->fesq);
	destruir(p->fdir);
	delete p;
	p = NULL;
}

// Calcula recursivamente a altura da arvore cuja raiz e' p
int calcularAltura(NoAB *p) {
	if (p != NULL) {
		int altEsq = calcularAltura(p->fesq);
		int altDir = calcularAltura(p->fdir);
		if (altEsq > altDir)
			return 1 + altEsq;
		else
			return 1 + altDir;
	}
	return -1;
}

// Funcao auxiliar: troca dois valores
void troca(int &a, int &b) {
	int aux = a;
	a = b;
	b = aux;
}


int main(void) {
	NoAB *raiz = NULL;

	// Criar permutacoes dos elementos
	srand( time(NULL) );

	for (int i=0; i<10; i++) inserir(raiz, rand()%100);

	int altura = calcularAltura(raiz);
	cout << "Altura = " << altura << endl;

	cout << endl << "Copie e cole o texto abaixo para o software Graphviz (e aperte F5):" << endl << endl;
	cout << "digraph g" << endl << "{" << endl;
	desenhar(raiz);
	cout << "}" << endl;

	getchar();
	return 0;
}