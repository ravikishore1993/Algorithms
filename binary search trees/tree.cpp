#include <iostream>
using namespace std;

struct node{
public:
	node* parent, *left, *right;
	int size,index;
};

class BST{ 
public:
	node* head;

	BST(){
	/*	this->head = new node;
		this->head->parent = null;
		this->head->left = null;
		this->head->right = null;
		this->head->size = 1;
	*/
		this->head = 0;
	}

	void insertNode(node newNode){
		
		node* indexNewNode = this->head;
		node* parentNode = 	this->head;
		bool side = 0; //0 for left , 1 for right
		while(indexNewNode != 0){
			if( newNode.index > indexNewNode->index ){
				(indexNewNode->size)++;
				parentNode = indexNewNode;
				indexNewNode = indexNewNode->right;
				side = 1;
			}
			else{
				(indexNewNode->size)++;
				parentNode = indexNewNode;
				indexNewNode = indexNewNode->left;	
				side = 0;
			}
		}
		
		indexNewNode = new node;
		
		indexNewNode->parent = parentNode;
		
		indexNewNode->left = 0;
		indexNewNode->right = 0;
		indexNewNode->size = 1;
		indexNewNode->index = newNode.index;
		
		if(parentNode == 0)  						// Initialization of tree
			this->head = indexNewNode;
		
		if(side){									// new node has to be set to right side 
			if(parentNode != 0)
			parentNode->right = indexNewNode;
		}
		else{										// new node has to be set to left side 
			if(parentNode != 0)
			parentNode->left = indexNewNode;	
		}	
	}


	void DisplayTree(){ 					// recursively displays the index values in the tree .
		RecursiveDisplayFrom(this->head);
	}

	void RecursiveDisplayFrom(node* newNode){
		if(newNode != 0)
		cout<<newNode->index<<endl;
		if(newNode->left != 0)
		RecursiveDisplayFrom(newNode->left);
		if(newNode->right != 0)
		RecursiveDisplayFrom(newNode->right);
	}

	BST(int arr[] , int length)
	{ 	this->head = 0;
		Binarify(arr,length);
	}
	
	void Binarify(int arr[], int length){
		node flag[length]; 
		for(int i = 0 ; i < length ; i++){
			flag[i].index = arr[i];
			this->insertNode(flag[i]);
		}
	}
	
	bool find(int index){		
	return	recursiveFind(this->head , index);
		}

	bool recursiveFind(node* indexNewNode , int index){
		if(indexNewNode->index == index)return true;
		else{
			if(index < indexNewNode->index){ if(indexNewNode->left ==0)return false; return recursiveFind(indexNewNode->left , index);}
			else {if(indexNewNode->right ==0)return false;return recursiveFind(indexNewNode->right , index);}
		}
	}	

	int NodesLessThan(int index){
		return RecursiveLessThan(this->head ,index);
	}

	int RecursiveLessThan(node* indexNewNode, int index){
		if(indexNewNode == 0) return 0;
		if(index >= indexNewNode->index ){ if(indexNewNode->left != 0) return 1 +(indexNewNode->left)->size + RecursiveLessThan(indexNewNode->right , index); else return 1+ RecursiveLessThan(indexNewNode->right , index);}
		else {return RecursiveLessThan(indexNewNode->left,index);}
	}
};

main(){

	int length = 9;
	int a[9] = {2,8,9,5,6,12,7,1,3};
	BST tree;
	tree.Binarify(a,length);
	cout<<"============================================================="<<endl;
	cout<<"Displaying the Binary Sorted tree :- "<<endl;
	tree.DisplayTree();
	cout<<"============================================================="<<endl;
	cout<<"Size of Binary Tree = "<<(tree.head)->size<<endl;
	cout<<"============================================================="<<endl;
	cout<<"Finding if 13 is a member of tree :- "<<tree.find(13)<<endl;
	cout<<"Finding if 9 is a member of tree :- "<<tree.find(9)<<endl;
	cout<<"============================================================="<<endl;
	cout<<"Finding number of nodes less than 9 :-  "<<tree.NodesLessThan(9)<<endl;
	cout<<"============================================================="<<endl;
}
