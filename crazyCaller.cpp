#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std ;

#define CALL_BITNUM 11 
#define HASH_BITNUM 5
#define HASH_LEN 200000

typedef struct CallNode *CallNodePtr ; 


struct CallNode {
	char  call[12] ;
	int count ;
	CallNodePtr next ;
} ;


int hash1(char s[12]) 
{
	//string s1 = s.substr( CALL_BITNUM - HASH_BITNUM , HASH_BITNUM ) ;
	int intr = atoi( s+CALL_BITNUM - HASH_BITNUM  ) ;
	return intr ;
}

CallNodePtr hashTable[HASH_LEN] ;	

void initHashTable()
{
	for( int i = 0 ;  i < HASH_LEN ; i ++ )
		hashTable[i] = 0 ;
}


void insertHashItem( char  s[12] )
{
	int h = hash1(  s ) ;
	CallNodePtr next = hashTable[h];
	if( next == NULL ) {
		CallNodePtr newNode =(CallNodePtr) malloc( sizeof(*newNode) ) ;
		strcpy( newNode->call , s ) ;
		newNode->count = 1 ;
		newNode->next = NULL ;
		hashTable[h] = newNode ;
		return ;
	}
	while (next ) {
		if( strcmp( next->call ,  s ) == 0 ) { 
			next->count ++ ;
			break ;
		}else if( next->next == NULL ) {
			CallNodePtr newNode =(CallNodePtr) malloc( sizeof(*newNode) ) ;
			strcpy( newNode->call , s ) ;
			newNode->count = 1 ;
			newNode->next = NULL ;
			next->next = newNode ;
		}else {
			next = next->next ;
		}
	}
}

int maxCallCount = -1 ;
int maxCallCount_Callers  = 0   ;
char*  maxCallCount_of_phoneNumber ;

void findMax() 
{
	for( int i = 0 ; i < HASH_LEN ; i ++ ){
		CallNodePtr cnp = hashTable[i] ;
		while( cnp ) {
			if( maxCallCount < cnp->count  ) {
				maxCallCount = cnp->count ;
				maxCallCount_of_phoneNumber  =  cnp->call  ;
				maxCallCount_Callers = 1 ;
			}else if( maxCallCount == cnp->count ) {
				maxCallCount_Callers ++ ;
				if( strcmp( maxCallCount_of_phoneNumber , cnp->call ) > 0 ) {
					 maxCallCount_of_phoneNumber  = cnp->call ;
				}
			}
			cnp = cnp->next ;
		}
	}
}
 

void countCallers(istream& is)
{
	int N ; 
	is >>  N ;
	if( N == 0 )
		return ;
	char s[12] ;
	initHashTable() ;
	for ( int i = 0 ; i < N ; i ++ ){
		is >> s ;
		insertHashItem(s) ;
		is >> s ;
		insertHashItem(s) ;	
	}
	findMax()  ;
	cout << maxCallCount_of_phoneNumber << " " << maxCallCount  ;
	if( maxCallCount_Callers  > 1 )
		cout << " " <<  maxCallCount_Callers    ;
	cout << endl ;
/*	ofstream ofs( "crazyCallerOut.txt" ) ;
	ofs << *maxCallCount_of_phoneNumber << " " << maxCallCount  ;
	if( maxCallCount_Callers  > 1 )
		ofs << " " <<  maxCallCount_Callers    ;
	ofs << endl ;
	ofs.close() ;
*/
 }

#define UsingFileIn 0

int main() 
{
#if UsingFileIn  
	ifstream ifs( "crazyCaller.txt" ) ;
	istream& is = ifs ;
#else 
	istream& is = cin  ;
#endif 
	countCallers( is )  ;

#if UsingFileIn
	ifs.close() ;
#endif
	return 0 ;
}


#if 0 
11-ɢ��1 �绰������ˣ�25 �֣�
���������ֻ��û�ͨ����¼���ҳ�����ͨ����������������ˡ�

�����ʽ:

�������ȸ���������N����10^5 ����Ϊͨ����¼���������N�У�ÿ�и���һ��ͨ����¼�������������ֻ�г��������ͽ��շ���11λ���ֹ��ɵ��ֻ����룬�����Կո�ָ���

�����ʽ:

��һ���и���������˵��ֻ����뼰��ͨ������������Կո�ָ�������������˲�Ψһ���������������С�ĺ��뼰��ͨ�����������Ҹ��Ӹ������п��˵�������

��������:

4
13005711862 13588625832
13505711862 13088625832
13588625832 18087925832
15005713862 13588625832
�������:

13588625832 3

#endif