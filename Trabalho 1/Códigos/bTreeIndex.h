#include <iostream>
#define D 5		//Order
#define M 10		//Order

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

	bool IsLeaf;			
	int nEntries;			// numbers of entries on the node			
	BTnode *childs[10];		//pointers to the next level in case of it being a index level, not a data level(leaf)
	int keys[9];			//keys values
	BTnode *next;	
	BTnode *prev;
	int h;					// tree height. for balance purposes
};

BTnode* createnode(int key){		//creates anode given one int value
	
	BTnode *newnode = new BTnode;

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
	if (node -> IsLeaf == 1){
		for (int i = 0; i < (node -> nEntries); ++i){
			if (node->keys[i] == k) return 1;
		}
		return 0;
	}
	else if (k < node->keys[0]){
		find_eq(k, node->childs[0]);
	}
	else if (k > node->keys[ (node -> nEntries-1)] ){
		find_eq(k, node->childs[ (node -> nEntries) ]);
	}
	else{
		int i;
		for (i = 0; i < (node -> nEntries); ++i){
			if (node->keys[i] > k) break;
		}
		find_eq(k, node->childs[i]);

	}

}

/*

BTnode create_indexnode(int ind, BTnode* node){
	if (node -> IsLeaf == 1){

	}

}
*/
bool insert(int k, BTnode* &node){
	if (node == NULL){					//empty tree
		BTnode* aux = createnode(k);
		aux ->IsLeaf = 1;
		node = createnode(k + M);
		node -> h = 1;
		node -> childs[0] = aux;

		return 1;
	}

	else{
		
		return 0;
	}

}





