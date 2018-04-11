#include <iostream>
#define D 5		//Order
#define M 10	//Order

using namespace std;


/*
struct LeafNode{

	int keys[9];	//9 possible entries	
	LeafNode *next;	//poitner to the next leaf node
	LeafNode *prev;	//pointer to previous leaf onde. they will be used in case of a range search
};
*/

/*
LeafNode *createleaf(int entrie){	//creates a leaf node, given a vector of entries data

	LeafNode *newleaf = new LeafNode;
	newleaf -> keys = entries;
	newleaf -> next = NULL;
	newleaf -> prev = NULL;

	return newleaf;
}
*/

/*
void updateheight(BTnode *p){
	if (p != NULL) {

		int maxheight;

		if (p -> child[0] != NULL){
			maxheight = p -> child[0] -> h;
			for (int i = 1; i < 10; ++i){
				maxheight = max(maxheight, p->child[i]->h)
			}
		}
		else if (p -> data[0] != NULL){
			maxheight = 0;
		}
		else maxheight = -1;

		p->h = 1 + maxheight

	}
}
*/

int max(int a, int b){ return (a>b)? a : b; }	//auxiliar function

struct BTnode{

	bool IsRoot;
	bool IsLeaf;			
	int nEntries;			//numbers of entries on the node			
	BTnode *childs[10];		//pointers to the next level in case of it being a index level, not a data level(leaf)
	int keys[9];			//keys values
	BTnode *next;	
	BTnode *prev;
	int h;					// tree height. for balance purposes
};

BTnode* createnode(int key){		//creates anode given one int value
	
	BTnode *newnode = new BTnode;

	newnode -> IsRoot = 0;
	newnode -> IsLeaf = 0;
	newnode -> nEntries = 1;

	for (int i = 0; i < M; ++i)	newnode-> childs[i] = NULL;
	for (int i = 0; i < (M-1); ++i)	newnode-> keys[i] = -1;
	newnode-> next = NULL;
	newnode-> prev = NULL;
	
	newnode -> keys[0] = key;	
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

/*

BTnode create_indexnode(int ind, BTnode* node){
	if (node -> IsLeaf == 1){

	}

}
*/

void insertOnNode (int k, BTnode* node, int nEntries){		//insert on leaf

	if(k > node -> keys[nEntries-1]){
		node -> keys[nEntries] = k;
		node -> nEntries++;
		return;
	}

	int newData[9];											//create a new data array
	for (int i = 0; i < 9; ++i) newData[i] = -1;			//set all values to default
	int j = 0;												//auxiliar variable		

	for (int i = 0; i < nEntries; ++i){						//for every entrie on the node
				
		if( node -> keys[i] < k ){		//if the node value is smaller thaan the key and the key has no been already inserted
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
			return;									//return NULL as a flag
		
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

bool insert(int k, BTnode* &node){
	if (node == NULL){					//empty tree
		BTnode* aux = createnode(k);
		aux ->IsRoot = 1;
		aux ->IsLeaf = 1;
		node = aux;

		return 1;
	}

	else if ( (node -> IsRoot == 1) && (node -> IsLeaf == 1) ){

		if(node -> nEntries == 9){
			/* split da raiz */;
		}
		else{
			int j = node -> nEntries;
			insertOnNode(k, node, node -> nEntries);
			if (j == node -> nEntries) return 0;
			return 1;
		}
		
	}

	else if (node -> IsLeaf == 1){
		/* code */
	}
	else{

	}

}





