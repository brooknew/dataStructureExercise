#include <iostream>
#include <fstream>
#include <string>

using namespace std ;

typedef struct BinarySearchTreeNode BSTNode , * BST ; 

struct BinarySearchTreeNode {
	int		data ;
	BST		left ;
	BST		right ;
};


BST insertBst( BST bst , int da )
{
	if( ! bst ) {
		bst = (BST)malloc( sizeof(*bst) ) ;
		bst->data = da ;
		bst->left = bst->right = NULL ;
	}else {
		if ( da < bst->data ) 
			bst->left = insertBst(  bst->left , da ) ;
		else if( da > bst->data )
			bst->right = insertBst( bst->right , da ) ;
		else ;//do nothing ;
	}
	return bst ;	
}

BST inputOriginBst( istream& ist , int& numNode ,  int& NumTestSeq ) 
{
	BST bst = NULL  ;
	NumTestSeq = 0 ;
	ist >> numNode ;
	int n = numNode   ;
	int da ;
	if( n > 0 ) 
		ist >> NumTestSeq ; 
	while( n --   ) {
		ist >> da ;
		bst  = insertBst ( bst , da ) ;
	}
	return bst ;
}

BST inputTestBst( istream&  ist  , int numNode ) 
{
	BST bst = NULL  ;
	int n = numNode   ;
	int da ;
	while( n --   ) {
		ist >> da ;
		bst  = insertBst ( bst , da ) ;
	}
	return bst ;
}
	
string travseralBst( BST bst  ) 
{
	string str = "";
	if( bst ) { 
		char c ;
		c = bst->data + '0' ; 
		str = str + string ( 1 ,  c  ) ;
		if( bst->left ) 
			str += travseralBst( bst->left ) ;
		if( bst->right )
			str += travseralBst ( bst->right ) ;
	}
	return str ;
}

bool compareBst( BST bst1 , BST bst2 )
{
	if( bst1 == bst2 ) 
		return true ;
	else if( (bst1) && (bst2) ){
		if( bst1->data != bst2->data )
			return false ;
		else {
			bool b = compareBst( bst1->left , bst2->left ) ;
			if( !b ) 
				return b ;
			return compareBst( bst1->right , bst2->right ) ;
		}
	}else{
		return false ;
	}
}

#define UsingFileINPUT 0
int main() 
{
#if UsingFileINPUT 
	ifstream ifs( "SameBinTree.txt" ) ;
	istream& ist = ifs ; 
#else
	istream& ist = cin ;
#endif
	while( true ) {
		int numNode , NumTestSeq;
		BST bst = inputOriginBst( ist ,  numNode ,  NumTestSeq )  ;
		if( numNode == 0 )
			break ;
		//string str = travseralBst( bst  );
		int i= 0 ;
		while ( i++ < NumTestSeq ) {
			BST bst1 = inputTestBst( ist , numNode ) ;
			//string str1 = travseralBst( bst1  );
			//int ret = str.compare( str1 ) ;
			bool ret = compareBst(  bst , bst1 ); // more fast 
			//if( ret == 0 ) 
			if ( ret )
				cout << "Yes"<<endl ;
			else
				cout << "No"<< endl ;
		}
		//cout << str << endl ;
	}
#if UsingFileINPUT
		ifs.close() ;
#endif
	return 0 ;
}