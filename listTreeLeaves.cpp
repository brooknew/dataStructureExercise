#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std ;

namespace ListTreeLeaves {

typedef struct TreeNode TreeNode , *Tree ;


struct TreeNode {
	char data ;
	Tree lt ;
	Tree rt ;
} ;



struct InputStru{
	char c ;
	char left ;
	char right ;
} ;

Tree insertTree( struct InputStru* pInput , int inde  ) 
{
	Tree T =(Tree) malloc( sizeof(*T) ) ;
	T->data = pInput[inde].c ;
	T->lt = T->rt = NULL ;
	if( pInput[inde].left >=0  )
		T->lt = insertTree( pInput, pInput[inde].left ) ;
	if( pInput[inde].right >=0  )
		T->rt = insertTree(pInput, pInput[inde].right ) ;
	return T ;
}



Tree readTree( istream&  InStream )
{	
	Tree R = NULL;

	char left , right ;
	int n ;
	int i = 0 ;

	InStream  >> n ;
	if( n == 0 )
		return NULL ;
	int* pIndex = new int[n] ;
	for( i = 0 ; i < n ; i ++ )
		pIndex[i] = -1 ;
	struct InputStru* pInput = new  struct InputStru [n] ;
	i = 0 ;
	while( i < n ) {
		InStream >>  left >> right ;
		pInput[i].c = i+'0' ;
		pInput[i].left = left - '0' ;
		pInput[i].right = right - '0' ;
		if( pInput[i].left >= 0 )
			pIndex[ pInput[i].left ] = pInput[i].left ;
		if( pInput[i].right >= 0  ) 
			pIndex[ pInput[i].right] = pInput[i].right ; 
		i++ ;
	}
	int head ;
	for( i = 0 ; i < n ; i ++ ) {
		if( pIndex[i] == -1 ) {
			head = i ;
			break ;
		}
	}
	//cout << head << endl ;
	R = insertTree( pInput ,  head  ) ;
	return R ;
}

typedef struct queue_node* queue_ptr ; 
struct queue_node 
{
	Tree  elem ;
	queue_ptr next ;
} ;

typedef struct
{
	queue_ptr front ;
	queue_ptr rear ;
}LinkQueue ;

LinkQueue* InitQueue()
{
	LinkQueue* lq =(LinkQueue*) malloc( sizeof( LinkQueue ) ) ;
	queue_ptr node0 =(queue_ptr) malloc( sizeof( *node0) )  ;
	node0->next = 0 ;
	lq->front=lq->rear = node0 ;
	return lq ;
}

int EnQueue(  LinkQueue* Q  , Tree  T )
{
	queue_ptr node0 =(queue_ptr) malloc( sizeof( *node0) )  ;
	node0->elem = T ;
	node0->next =  NULL ;
	Q->rear->next = node0 ;
	Q->rear = node0 ;
	return 1 ;
}

Tree DeQueue( LinkQueue* Q  )
{
	if( Q->front == Q->rear )
		return NULL ;
	Tree p = Q->front->next->elem ;
	if( Q->rear == Q->front->next )
		Q->rear = Q->front ;
	else
		Q->front->next = Q->front->next->next ;
	return p ;
}

void listTreeLeavesBaseOnDepth(Tree T)
{
	if( !T ) 
		return ;
	LinkQueue* Q = InitQueue() ;
	EnQueue( Q , T ) ;
	bool first = true ;
	while( T= DeQueue(Q) ) {
		if( (!T->lt)  && (!T->rt) ){
			if( !first ) {
				cout << " " ;
			}else{
				first = false ;
			}
			cout << T->data  ;
		}
		if( T->lt ) 
			EnQueue( Q , T->lt ) ;
		if( T->rt ) 
			EnQueue( Q , T->rt ) ;		
	}
	cout << endl ;
}



} //namespace

 
using namespace ListTreeLeaves ;

void testListTreeLeaves()
{
	string filen="listTreeLeavesInput.txt" ;
	ifstream ifs( filen.c_str() ) ;
	//ifstream ifs( filen ) ;
	//Tree R = readTree( cin ) ;
	Tree R = readTree( ifs ) ;
	listTreeLeavesBaseOnDepth( R ) ;
	ifs.close() ;
}

int main() 
{
	testListTreeLeaves();

	return 0 ;
}


/*
03-Ê÷2 List Leaves£¨25 ·Ö£©
Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (¡Ü10) which is the total
number of nodes in the tree -- and hence the nodes are numbered from 0 to N-1. 
Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. 
If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

Output Specification:

For each test case, print in one line all the leaves' indices in the order of top down, and left to right. 
There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

Sample Input:

8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
Sample Output:

4 1 5
*/
