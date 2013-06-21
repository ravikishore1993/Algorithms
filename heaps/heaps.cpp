#include <iostream>
using namespace std;

class Heap{
public:
	int size; // Stores the size of the array given . It is the total number of elements in tree
	int* tree;  
	
	Heap(int s){
		size = s ;
	}

	void makeTree(int* arr){
		this->tree = new int[this->size + 1];
		for(int i = 1; i <= this->size; i++ ){
			*(this->tree + i) = arr[i]; 
		}
	}

	void getTreeArray(){
		for(int i = 1; i <= this->size; i++ ){
			cout<<*(this->tree + i)<<" ";
			
		}
		cout<<endl;
	}	
		
	void printleft(int i){
		if( 2*i <= this->size)
		cout<<this->tree[2*i]<<" "<<endl;
	}


	void printright(int i){
		if( 2*i+1 <= this->size)
		cout<<this->tree[2*i+1]<<" "<<endl;
	}

	int left(int i){
		if( 2*i <= this->size)
		return this->tree[2*i];
		else return 0;
	}


	int right(int i){
		if( 2*i + 1 <= this->size)
		return this->tree[2*i+1];
				else return 0;
	}

	void build_max_heap(){
		for(int i = this->size/2 ; i > 0 ; i--){
			max_heapify(i);
			//this->getTreeArray();		
		}
	}

	void build_min_heap(){
		for(int i = this->size/2 ; i > 0 ; i--){
			min_heapify(i);
		}
	}

	void max_heapify(int i){
		if(!isMax_heap(2*i + 1) ) max_heapify(2*i + 1);
		if(!isMax_heap(2*i) ) max_heapify(2*i);
		
		if(!isMax_heap(i)){
			int max;
			if(this->left(i) > this->right(i)) {  max =this->left(i); *( this->tree + 2*i ) = *( this->tree + i );  }
			else { max = this->right(i);
			 *( this->tree + 2*i+1 ) = *( this->tree + i );
			}
			*( this->tree + i ) = max;
		}
	}

	void min_heapify(int i){
		if(!isMin_heap(2*i + 1) ) min_heapify(2*i + 1);
		if(!isMin_heap(2*i) ) max_heapify(2*i);
		
		if(!isMin_heap(i)){
			int min;
			if(this->left(i) < this->right(i)) {  min =this->left(i); *( this->tree + 2*i ) = *( this->tree + i );  }
			else { min = this->right(i);
			 *( this->tree + 2*i+1 ) = *( this->tree + i );
			}
			*( this->tree + i ) = min;
		}
	}


	bool isMax_heap(int i){
		if(i > (this->size)/2 ) return true;
		if(isMax_heap(2*i + 1) && isMax_heap(2*i) )
		if( *(this->tree + i) > this->left(i) && *(this->tree + i) > this->right(i)  )
			return true;
		else return false;
		else return false;
	}
	

	bool isMin_heap(int i){
		if(i > (this->size)/2 ) return true;
		if(isMin_heap(2*i + 1) && isMin_heap(2*i) )
		if( *(this->tree + i) < this->left(i) && *(this->tree + i) < this->right(i)  )
			return true;
		else return false;
		else return false;
	}

	void deleteElement(int i){
		(this->size)--; 
	}
	
	void deleteLastElement(){
		deleteElement(this->size);	
	}

	void swapFirstLast(){
		int help = *(this->tree + 1);
		*(this->tree + 1) = *(this->tree + this->size);
		*(this->tree + this->size) = help;
	}

	void heapsort(int* max){
		int flag = this->size;
		for(int i = 1 ; i <=10 ; i++){
 		max[i] = this->tree[1];
 		this->swapFirstLast();
 		this->deleteLastElement();
 		this->getTreeArray();	
 		this->max_heapify(1);
 	}

 	this->size = flag;

	}

};

int main(){

 	Heap a(10);
 	int arr[11]={0,1,2,3,4,5,6,7,8,9,10};
 	a.makeTree(arr);
 	a.getTreeArray();
 	a.build_max_heap();
 	a.getTreeArray();
 	
 	int max[11];

 	a.heapsort(max);

 	for(int i = 1 ; i <=10 ; i++){
 		cout<<max[i]<<"  ";
 	}
 	
 	cout<<endl;
a.getTreeArray();
 	
return 42;
}
