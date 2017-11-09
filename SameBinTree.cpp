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


#if 0

04-树4 是否同一棵二叉搜索树（25 分）
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:

输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:

对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

输入样例:

4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0

输出样例:

Yes
No
No

#endif