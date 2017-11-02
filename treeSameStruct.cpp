//data structure exercise

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std ;

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


Tree readTree( string filn )
{
	ifstream ifs( filn.c_str() ) ;
	Tree R = NULL;
	char c ;
	char left , right ;
	int n ;
	int i = 0 ;
	//cin >> n ;
	ifs >> n ;
	if( n == 0 )
		return NULL ;
	int* pIndex = new int[n] ;
	for( i = 0 ; i < n ; i ++ )
		pIndex[i] = -1 ;
	struct InputStru* pInput = new  struct InputStru [n] ;
	i = 0 ;
	while( i < n ) {
		//cin >> c >> left >> right ;
		ifs >> c >> left >> right ;
		pInput[i].c = c ;
		pInput[i].left = left - '0' ;
		pInput[i].right = right - '0' ;
		if( pInput[i].left >= 0 )
			pIndex[ pInput[i].left ] = pInput[i].left ;
		if( pInput[i].right >= 0  ) 
			pIndex[ pInput[i].right] = pInput[i].right ; 
		i++ ;
	}
	ifs.close() ;
	int head ;
	for( i = 0 ; i < n ; i ++ ) {
		if( pIndex[i] == -1 ) {
			head = i ;
			break ;
		}
	}
	cout << head << endl ;
	R = insertTree( pInput ,  head  ) ;
	return R ;
}

Tree readTree( istream  InStream )
{	
	Tree R = NULL;
	char c ;
	char left , right ;
	int n ;
	int i = 0 ;
	//cin >> n ;
	InStream  >> n ;
	if( n == 0 )
		return NULL ;
	int* pIndex = new int[n] ;
	for( i = 0 ; i < n ; i ++ )
		pIndex[i] = -1 ;
	struct InputStru* pInput = new  struct InputStru [n] ;
	i = 0 ;
	while( i < n ) {
		//cin >> c >> left >> right ;
		InStream >> c >> left >> right ;
		pInput[i].c = c ;
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
	cout << head << endl ;
	R = insertTree( pInput ,  head  ) ;
	return R ;
}



bool compareTree( Tree T1 , Tree T2 )
{
	if( T1==NULL && T2==NULL )
		return true ;
	if( T1 == NULL && T2 !=NULL )
		return false ;
	if( T1 != NULL && T2 == NULL )
		return false ;
	if( T1->data != T2->data ) 
		return false ;
	bool b1, b2 , b3 , b4;
	Tree T11= T1->lt ; 
	Tree T21 = T2->lt ;
	Tree T12 = T1->rt ;
	Tree T22 = T2->rt ;
	b1 = compareTree( T11 , T21 ) ;
	b2 = compareTree( T12 , T22 ) ;

	b3 = compareTree( T11, T22 ) ;
	b4 = compareTree( T12 , T21 ) ;
	return (b1&&b2) || (b3&&b4)  ;
}

int main()
{
	string filn1 = "d:\\tree1Input.txt" ;
	string filn2 = "d:\\tree2Input.txt" ;
	ifstream ifs( filn1.c_str() ) ;
	Tree R1 = readTree(  ifs /*cin*/ ) ;
	ifs.close() ;
	Tree R2 = readTree(filn2) ;
	bool b = compareTree( R1 , R2 ) ;
	if( b ) 
		cout<<"Yes"<<endl ;
	else
		cout<<"No"<<endl ;
	return 0 ;	
}


/*
03-树1 树的同构（25 分）
给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。
例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。
现给定两棵树，请你判断它们是否是同构的。
输入格式:

输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，即该树的结点数（此时假设结点从0到N?1编号）；
随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，
则在相应位置上给出“-”。给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。

输出格式:

如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1（对应图1）： 见Fig1Fig2.png

8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
输出样例1:

Yes
输入样例2（对应图2）：见Fig1Fig2.png

8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4
输出样例2:

No
*/
