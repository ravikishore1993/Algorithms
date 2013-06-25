#include <iostream>
using namespace std;

struct node{
public:
	node* parent, *left, *right;
	int size,index,height;
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

	node* insertNode(node newNode){
		
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

		return indexNewNode;	
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
			flag[i].height = 0;
			this->insertNode(flag[i]);
		}
	}
	
	node* find(int index){		
	return	recursiveFind(this->head , index);
		}

	node* recursiveFind(node* indexNewNode , int index){
		if(indexNewNode->index == index){return indexNewNode;  }
		else{
			if(index < indexNewNode->index){ if(indexNewNode->left ==0)return 0; return recursiveFind(indexNewNode->left , index);}
			else {if(indexNewNode->right ==0)return 0;return recursiveFind(indexNewNode->right , index);}
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

class AVL :public BST{
public:
	node* insertNode(node newNode){
		
		node* indexNewNode;
		indexNewNode = BST::insertNode(newNode);
		recursiveChangeHeight(indexNewNode);
		AVLifyFrom(indexNewNode);   // Takes a node that has been inserted into the tree and traverses up the tree to make changes if any unbalanced node is encountered
		return indexNewNode;
	}

	void AVLifyFrom(node* indexNewNode){

		if(indexNewNode != 0){
			recursiveBalance(indexNewNode);
		}
	}

	bool isBalanced(node* indexNewNode){
		int difference = height(indexNewNode->left) - height(indexNewNode->right) ;
		if(  difference <= 1 && difference >= -1 )return 1;
		return 0;
	}

	void recursiveBalance(node* indexNewNode){
		if(indexNewNode != 0){
			if( !isBalanced(indexNewNode) ){    /// Got here the node which is not balanced

				if(height(indexNewNode->right) > height(indexNewNode->left) ){ // case of right heavy
					if(height(indexNewNode->right->left) > height(indexNewNode->right->right) ){ // case of right-left
						RightRotateAbout(indexNewNode->right);
					}

					LeftRotateAbout(indexNewNode);

				}

				else{								// case of left heavy
					if(height(indexNewNode->left->right) > height(indexNewNode->left->left) ){ // case of left-right
						LeftRotateAbout(indexNewNode->left);
					}
					RightRotateAbout(indexNewNode);
				}

				recursiveBalance(indexNewNode->parent);
			}	

			else{
				recursiveBalance(indexNewNode->parent);
			}
		}
	}

	bool IsNodeLeftChildOfParent(node* newNode){
		if(newNode->index == newNode->parent->left->index)return 1;
		else return 0;
	}

	void recursiveChangeHeight(node* newNode){
		int leftheight , rightheight ;
		leftheight = (newNode->left == 0)?-1:newNode->left->height;
		rightheight = (newNode->right == 0)?-1:newNode->right->height;
		newNode->height = ((leftheight>rightheight)?leftheight:rightheight) + 1;
		if(newNode->parent != 0 )recursiveChangeHeight(newNode->parent);
	}

	void DisplayTreeWithHeights(){ 					// recursively displays the index values in the tree .
		RecursiveDisplayWithHeightsFrom(this->head);
	}

	void Binarify(int arr[], int length){
		node flag[length]; 
		for(int i = 0 ; i < length ; i++){
			flag[i].index = arr[i];
			flag[i].height = 0;
			this->insertNode(flag[i]);
		}
	}

	void RecursiveDisplayWithHeightsFrom(node* newNode){
		if(newNode != 0)
		cout<<"Index ==> "<<newNode->index<<"  Height ==>  "<<newNode->height<<endl;
		if(newNode->left != 0)
		RecursiveDisplayWithHeightsFrom(newNode->left);
		if(newNode->right != 0)
		RecursiveDisplayWithHeightsFrom(newNode->right);
	}

	int height(node* newNode){
		if(newNode == 0 )return -1;
		else return newNode->height;
	}

	node* RightRotateAbout(node* Pivot){

	
	if( Pivot->left !=0 ){
		if(Pivot->parent!=0)
		{
		int left = IsNodeLeftChildOfParent(Pivot);
		if(left){
		Pivot->parent->left = Pivot->left;
		}
		
		else{

		Pivot->parent->right = Pivot->left;	
		}
	}
		else{ 			// That means the root of the tree is the pivot , so head of the whole class is to be changed also;
			this->head = Pivot->left;
		}

		Pivot->left->parent = Pivot->parent;
		Pivot->parent = Pivot->left;
		Pivot->left = Pivot->parent->right;
		Pivot->parent->right = Pivot;
		if(Pivot->left != 0)Pivot->left->parent = Pivot;

		//////////////Before This Point , rotation Has been complete , next few lines deal with height adjustments due to rotation
		recursiveChangeHeight(Pivot);
		/////////////Lines after this change size modifications
		
		Pivot->size  = 1 + ((Pivot->left == 0)?0:(Pivot->left->size) ) + ((Pivot->right == 0)?0:(Pivot->right->size));
		Pivot->parent->size = 1 + ((Pivot->parent->left == 0)?0:(Pivot->parent->left->size)) +((Pivot->parent->right == 0)?0:(Pivot->parent->right->size)); 

		}	
	return Pivot;
	}


	node* LeftRotateAbout(node* Pivot){

	
	if( Pivot->right !=0 ){
		if(Pivot->parent!=0){
		int left = IsNodeLeftChildOfParent(Pivot);
		if(left){
		Pivot->parent->left = Pivot->right;
		}
		
		else{
		Pivot->parent->right = Pivot->right;	
		}
	}
		else{ 			// That means the root of the tree is the pivot , so head of the whole class is to be changed also;
			this->head = Pivot->right;
		}

		Pivot->right->parent = Pivot->parent;
		Pivot->parent = Pivot->right;
		Pivot->right = Pivot->parent->left;
		Pivot->parent->left = Pivot;
		if(Pivot->right != 0)Pivot->right->parent = Pivot;

		//////////////Before This Point , rotation Has been complete , next few lines deal with height adjustments due to rotation
		recursiveChangeHeight(Pivot);
		/////////////Lines after this change size modifications
		Pivot->size = 1 + ( (Pivot->left == 0)?0:(Pivot->left->size) ) +((Pivot->right == 0)?0:(Pivot->right->size));
		Pivot->parent->size = 1 + ((Pivot->parent->left == 0)?0:(Pivot->parent->left->size)) + ((Pivot->parent->right == 0)?0:(Pivot->parent->right->size)); 

		}	
	return Pivot;
	}

};

main(){

	int length = 6;
	int a[6] = {1,2,3,4,5,6};
	AVL tree;
	tree.Binarify(a,length);
	cout<<"============================================================="<<endl<<endl;
	cout<<"Displaying the Binary Sorted tree :- "<<endl;
	tree.DisplayTree();
	cout<<"============================================================="<<endl<<endl;
	cout<<"Heights of nodes in the AVL: "<<endl;
	tree.DisplayTreeWithHeights();
	cout<<"Size of Binary Tree = "<<(tree.head)->size<<endl;
	cout<<"============================================================="<<endl<<endl;
	cout<<"Displaying Tree with Heights after Rotating about 4"<<endl;
	tree.LeftRotateAbout(tree.find(1));
	tree.DisplayTreeWithHeights();
	cout<<"Size of Binary Tree = "<<(tree.head)->size<<endl;
	cout<<"============================================================="<<endl<<endl;
	cout<<"Displaying Tree with Heights after again Rotating about 4"<<endl;
	tree.LeftRotateAbout(tree.find(2));
	tree.DisplayTreeWithHeights();
	cout<<"Size of Binary Tree = "<<(tree.head)->size<<endl;
	cout<<"============================================================="<<endl<<endl;
	cout<<"Displaying Tree with Heights after again Rotating about 2"<<endl;
	tree.LeftRotateAbout(tree.find(4));
	tree.DisplayTreeWithHeights();
	cout<<"Size of Binary Tree = "<<(tree.head)->size<<endl;
	cout<<"============================================================="<<endl<<endl;
	cout<<"Size of Binary Tree = "<<(tree.head)->size<<endl;
	cout<<"============================================================="<<endl<<endl;
	cout<<"Finding if 13 is a member of tree :- "<<tree.find(13)<<endl;
	cout<<"Finding if 2 is a member of tree :- "<<tree.find(2)<<endl;
	cout<<"============================================================="<<endl<<endl;
	cout<<"Finding number of nodes less than 9 :-  "<<tree.NodesLessThan(9)<<endl;
	cout<<"============================================================="<<endl<<endl;
}
	
