#include <iostream>
#include <list>
#define D 5		//Order
#define M 10	//Order

using namespace std;

void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

struct BTnode{

	bool IsRoot;
	bool IsLeaf;			
	bool visitado;
	int nEntries;			//numbers of entries on the node			
	BTnode *childs[10];		//pointers to the next level in case of it being a index level, not a data level(leaf)
	int keys[9];			//keys values
	BTnode *next;	
	BTnode *prev;
	BTnode *father;
	int h;					// tree height. for balance purposes
};

BTnode* createnode(){		//creates anode given one int value
	
	BTnode *newnode = new BTnode;

	newnode -> visitado	= 0;
	newnode -> IsRoot 	= 0;
	newnode -> IsLeaf 	= 0;
	newnode -> nEntries = 0;

	for (int i = 0; i < M; ++i)	newnode-> childs[i] = NULL;
	for (int i = 0; i < (M-1); ++i)	newnode-> keys[i] = -1;
	newnode-> next 	 = NULL;
	newnode-> prev 	 = NULL;
	newnode-> father = NULL;
	
	//newnode -> keys[0] = key;	
	newnode -> h = 0;

	return newnode;
}


bool find_eq(int k, BTnode* node){
	if (node -> IsLeaf == 1){									//if the node is a leaf (data) node
		for (int i = 0; i < (node -> nEntries); ++i){			//check all the elements
			if (node->keys[i] == k) return 1;					//if the element is found, then return 1
		}
		return 0;												//here the element is not in the leaf, thus is not on the tree. return 0
	}
	else if (k < node->keys[0]){								//if the key is smaller than the leftmost element.
		return find_eq(k, node->childs[0]);						//then, go to the leftmost child
	}
	else if (k > node->keys[ (node -> nEntries-1)] ){			//if the key is bigger than the rightmost element
		return find_eq(k, node->childs[ (node -> nEntries) ]);	//then, go to rightmost child
	}
	else{														//the key is between child 0 and child n
		int i;
		for (i = 0; i < (node -> nEntries); ++i){				//run all the indexes of the node.
			if (node->keys[i] > k) break;						//find an index greater than the key
		}		
		return find_eq(k, node->childs[i]);						//then, go to the left child of the found index 
	}
}

int* find_rg(int k1, int k2, BTnode* node){
	int aux;
	list<int> vetor;
	
	if(k1 > k2){
		aux = k1;
		k1 = k2;
		k2 = aux;
	}

	if (node -> IsLeaf == 1){
		int *range, size = 0;
		int i = 0;
		BTnode* auxNode = createnode();
		auxNode = node;
		while(auxNode->keys[i] < k1 && auxNode->keys[i] != -1){
			i++;				
		}
		
		if (auxNode -> keys[i] == -1){
			auxNode = auxNode -> next;
			i = 0;
		}
		while(auxNode != NULL && auxNode -> keys[i] <= k2){
			if(auxNode -> keys[i] == -1 || i == 8){					
				auxNode = auxNode -> next;
				i = 0;
			}
			vetor.push_back(auxNode -> keys[i]);
			i++;
		}

		if (vetor.size()){
			range = new int [vetor.size()];

			list<int>::iterator it;
			int j = 0;
			for (it = vetor.begin(); it != vetor.end(); ++it){
				range[j] = *it;
				j++;
			}
		}

		else range = NULL;

		return range;								
	}
	else if (k1 < node->keys[0]){								
		return find_rg(k1, k2, node->childs[0]);						
	}
	else if (k1 > node->keys[ (node -> nEntries-1)] ){		
		return find_rg(k1, k2, node->childs[ (node -> nEntries) ]);	
	}
	else{														
		int i;
		for (i = 0; i < (node -> nEntries); ++i){				
			if (node->keys[i] > k1) break;						
		}		
		return find_rg(k1, k2, node->childs[i]);						
	}

}

void print_nodeinfo(BTnode* node){

	if (node == NULL){
		cout << "Nó vazio" << endl;
		return;
	}

	cout << "Root: " << node -> IsRoot	<< endl;
	cout << "Leaf: " << node -> IsLeaf 	<< endl;
	cout << "Entries : " << node -> nEntries	<< endl;

	cout << "Keys: ";

	for (int i = 0; i < node -> nEntries; ++i) cout <<	node-> keys[i] << " ";
	cout << endl;

	if (node -> childs[0] != NULL) cout << "Has childs!" << endl;
	else cout << "No childs!" << endl;

	if (node -> next != NULL) cout << "Has right sibling!" << endl;
	else cout << "No right sibling!" << endl;	
	
	if (node -> prev != NULL) cout << "Has left sibling!" << endl;
	else cout << "No left sibling!" << endl;

	cout << "Height: " << node -> h << endl;		

}

void copy_node(BTnode* source, BTnode* &copy){
	if (source == NULL) return;

	if (copy == NULL) copy = createnode();
	

	copy -> IsRoot 	= source -> IsRoot;
	copy -> IsLeaf 	= source -> IsLeaf;
	copy -> nEntries = source -> nEntries;

	for (int i = 0; i < M; ++i)	copy-> childs[i] = source -> childs[i];
	for (int i = 0; i < (M-1); ++i)	copy-> keys[i] = source -> keys[i];
		
	copy-> next 	 = source -> next;
	copy-> prev 	 = source -> prev;
	copy-> father 	 = source -> father;
	copy -> h = source -> h;	

}

void visita(BTnode* node){
	if (node != NULL && node -> visitado == 0){
		node -> visitado =1;
		if (node -> IsLeaf == 0){
			cout << "Nó indice!\nDados: ";
			for (int i = 0; i < node -> nEntries; ++i) cout << node -> keys[i] << " ";
			cout << endl;
		}
		else{
			cout << "Nó folha!\nDados: ";
			for (int i = 0; i < node -> nEntries; ++i) cout << node -> keys[i] << " ";
			cout << endl;	
		}
		cout << endl;
	}
}

void emOrdem(BTnode* node) {
	if (node != NULL) {
		for (int i = 0; i < node -> nEntries; ++i){			
			emOrdem(node -> childs[i]);
			visita(node);
			emOrdem(node -> childs[i+1]);
		}		
	}
	//else cout << "arvore vazia" << endl;
}

void insertOnLeaf (int k, BTnode* node, int nEntries){		//insert on a leaf that has available space

	if(k > node -> keys[nEntries-1]){
		node -> keys[nEntries] = k;
		node -> nEntries++;
		return;
	}

	int newData[9];											//create a new data array
	for (int i = 0; i < 9; ++i) newData[i] = -1;			//set all values to default
	int j = 0;												//auxiliar variable		

	for (int i = 0; i < nEntries; ++i){						//for every entrie on the node
				
		if( node -> keys[i] < k ){							//if the node value is smaller thaan the key and the key has no been already inserted
			newData[i] = node -> keys[j];					//newdata receives the actual value on the node
			j++;											//advance j so its following i
		}
		else if (node -> keys[i] != k){						//if the node vale is not smaller nor equal to the key						
			newData[i] = k;									//new data[i] receive the key
			for (int l = i+1; l < nEntries+1; ++l){
				newData[l] = node -> keys[j];
				j++;
			}
			break;			
		}
		else												//the key already exists on the leaf
			return;											//return NULL as a flag
		
	}

	for (int i = 0; i < 9; ++i){
		if (newData[i] != -1){
			node -> keys[i] = newData[i];
		}
		else 
			break;
		
	}	

	node -> nEntries++;

}


void insertOnIndex (int k, BTnode* father, BTnode* son){		

	
	BTnode* newData = NULL;											
	copy_node(father, newData);
	
	int j;

	for (j = 0; j < father -> nEntries; j++)
		if (father -> keys[j] > k) break;

	father -> childs[j+1] = son;
	father -> keys[j] = k;

	for (int i = j+2; i <= father->nEntries; ++i){
		father -> childs[i] = newData -> childs[j+1];		
		j++;
		if (i < father -> nEntries){
			father -> keys[i-1] = newData -> keys[j];
		}
	}	

	father -> nEntries++;

}


bool insert(int k, BTnode* &node){
	if (node == NULL){					//empty tree
		BTnode* aux = createnode();
		aux -> keys[0] = k;
		aux -> nEntries = 1;
		aux ->IsRoot = 1;
		aux ->IsLeaf = 1;
		copy_node(aux, node);

		delete aux;

		return 1;
	}

	else if ( (node -> IsLeaf == 1) ){ 

			if(node -> nEntries == 9){
				if (node -> IsRoot == 1){							//split de um nó folha e raiz
					for (int i = 0; i < 9; ++i){
						if (k == node -> keys[i]) return 0;
					}

					int newIndex, caso;

					if (k < node -> keys[4]){
						newIndex = node -> keys[4];
						caso = 0;
					}

					else if (k > node -> keys[4] && k < node -> keys[5]){
						newIndex = k;
						caso = 1;
					}

					else{
						newIndex = node -> keys[5];
						caso = 1;
					}

					BTnode* copy  = NULL;
					BTnode* left  = NULL;
					BTnode* right = NULL;

					copy_node(node, copy);

					node = createnode();
					left = createnode();
					right = createnode();

					node -> keys[0] = newIndex;
					node -> nEntries++;
					node -> IsRoot =1;
					node -> h ++;
					node -> childs[0] = left;
					node -> childs[1] = right;

					left -> IsLeaf = 1;
					left -> next = right;
					left -> father = node;

					right -> IsLeaf = 1;
					right -> prev = left;
					right -> father = node;


					switch (caso){
						case 0:	insertOnLeaf(k, left, left->nEntries);
								for (int i = 0; i < 4; ++i) insertOnLeaf(copy -> keys[i], left, left->nEntries);	//metade esquerda dos dados
								for (int i = 4; i < 9; ++i) insertOnLeaf(copy -> keys[i], right, right->nEntries);	//metade direita dos dados	
								break;	

						case 1:	insertOnLeaf(k, right, right->nEntries);
								for (int i = 0; i < 5; ++i) insertOnLeaf(copy -> keys[i], left, left->nEntries);	//metade esquerda dos dados
								for (int i = 5; i < 9; ++i) insertOnLeaf(copy -> keys[i], right, right->nEntries);	//metade direita dos dados	
								break;

						default: cerr << "Some error ocurred on the split" << endl;

					}

					delete copy;

					return 1;
				}
				else{									//splt difçil (genérico)
					BTnode* newnode = createnode();
					BTnode* copy    = createnode();

					for (int i = 0; i < 9; ++i){
						if (k == node -> keys[i]) return 0;
					}

					int newIndex, caso;

					if (k < node -> keys[4]){
						newIndex = node -> keys[4];
						caso = 0;
					}

					else if (k > node -> keys[4] && k < node -> keys[5]){
						newIndex = k;
						caso = 1;
					}

					else{
						newIndex = node -> keys[5];
						caso = 1;
					}

					

					copy_node(node, copy);
					copy_node(node, newnode);
					for (int i = 0; i < 9; ++i) node ->keys[i] = -1;
					for (int i = 0; i < 9; ++i) newnode ->keys[i] = -1;
					node -> nEntries = 0;
					newnode -> nEntries = 0;					

					newnode -> next = node-> next;			

					if (copy -> next != NULL) copy -> next -> prev = newnode;

					node -> next = newnode;
					

					newnode -> prev = node;
					

					newnode -> father = node -> father;
					

					newnode -> h = node-> h;
										

					switch (caso){
						case 0:	insertOnLeaf(k, node, node->nEntries);
								for (int i = 0; i < 4; ++i) insertOnLeaf(copy -> keys[i], node, node->nEntries);	//metade esquerda dos dados
								for (int i = 4; i < 9; ++i) insertOnLeaf(copy -> keys[i], newnode, newnode->nEntries);	//metade direita dos dados	
								break;	

						case 1:	insertOnLeaf(k, newnode, newnode->nEntries);
								for (int i = 0; i < 5; ++i) insertOnLeaf(copy -> keys[i], node, node->nEntries);	//metade esquerda dos dados
								for (int i = 5; i < 9; ++i) insertOnLeaf(copy -> keys[i], newnode, newnode->nEntries);	//metade direita dos dados	
								break;

						default: cerr << "Some error ocurred on the split" << endl;

					}

					if (copy->father->nEntries != 9){ //sem split no pai						
						newnode->father = copy->father;
						insertOnIndex (k, newnode->father, newnode);
					}
					else{							  //com split no pai

					}



				}	

			}
			else{
				int j = node -> nEntries;
				insertOnLeaf(k, node, node -> nEntries);
				if (j == node -> nEntries) return 0;
				return 1;
			}
		//Final do If
	}

	else if (node -> IsLeaf == 0){
		if (k < node->keys[0]){										//if the key is smaller than the leftmost element.
			return insert(k, node->childs[0]);						//then, go to the leftmost child
		}
		else if (k > node->keys[ (node -> nEntries-1)] ){			//if the key is bigger than the rightmost element
			return insert(k, node->childs[ (node -> nEntries) ]);	//then, go to rightmost child
		}
		else{
			for (int i = 0; i < node -> nEntries; i++){				
				if (node -> keys[i] > k) return insert(k, node -> childs[i]);
			}
		}
	}

}







