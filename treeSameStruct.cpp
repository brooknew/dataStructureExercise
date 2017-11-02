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
03-��1 ����ͬ����25 �֣�
����������T1��T2�����T1����ͨ�����ɴ����Һ��ӻ����ͱ��T2�������ǳ��������ǡ�ͬ�����ġ�
����ͼ1����������������ͬ���ģ���Ϊ���ǰ�����һ�����Ľ��A��B��G�����Һ��ӻ����󣬾͵õ�����һ��������ͼ2�Ͳ���ͬ���ġ�
�ָ����������������ж������Ƿ���ͬ���ġ�
�����ʽ:

�������2�ö�����������Ϣ������ÿ������������һ���и���һ���Ǹ�����N (��10)���������Ľ��������ʱ�������0��N?1��ţ���
���N�У���i�ж�Ӧ��ŵ�i����㣬�����ý���д洢��1��Ӣ�Ĵ�д��ĸ�������ӽ��ı�š��Һ��ӽ��ı�š�������ӽ��Ϊ�գ�
������Ӧλ���ϸ�����-�������������ݼ���һ���ո�ָ���ע�⣺��Ŀ��֤ÿ������д洢����ĸ�ǲ�ͬ�ġ�

�����ʽ:

�����������ͬ���ģ������Yes�������������No����

��������1����Ӧͼ1���� ��Fig1Fig2.png

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
�������1:

Yes
��������2����Ӧͼ2������Fig1Fig2.png

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
�������2:

No
*/
