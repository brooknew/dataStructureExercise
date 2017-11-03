
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std ;

typedef struct ListNode* NodePtr ;

struct ListNode {
	int addressC;
	int data ;
	int addressN;
	NodePtr next ;
};
typedef NodePtr List ;

void printList( List L ) 
{

	while( L->next ) {
		cout << setw(5) <<setfill('0') << L->addressC << setw(1) << " " << L->data << " " << setw(5) <<setfill('0') << L->addressN << endl ;
		L = L->next ;
	}
	cout << setw(5) <<setfill('0') << L->addressC << setw(1) << " " << L->data << " "  << L->addressN << endl ;
}

List readList(istream& Istream)
{	
	struct ListNode* LN = new  struct ListNode [100000] ;
	int  address , N , K ;
	int  addressC , v , addressN ;
	Istream >> address >> N >> K ;
	int i = 0 ; 
	while ( i < N ) {
		Istream >> addressC >> v >> addressN ;
		LN[addressC].addressC = addressC ;
		LN[addressC].data = v  ;
		LN[addressC].addressN = addressN ;
		if( addressN == -1 )
			LN[addressC].next = NULL ;
		i ++ ;
	}
	List L0 , L ;
	L0 = L = & LN[address] ;
	while( L->addressN != -1 ){
		L->next = & LN[ L->addressN] ;
		L = L->next ;
	}
//
	printList(  L0 ) ;
//
	i = 0 ;

	L= L0 ;
	List tmp ;
	while ( i < K-1 ) {
		tmp = L->next->next ;
		L->next->next = L0 ;
		L->next->addressN = L0->addressC ;
		L0 = L->next ;
		L->next = tmp ;
		i ++ ; 
	}
	if( L->next )
		L->addressN = L->next->addressC ;
	else
		L->addressN = -1 ;
	return L0 ;
}



int main() 
{
	string filen="ReverseLinkedList.txt" ;
	ifstream ifs( filen.c_str() ) ;
	//ifstream ifs( filen ) ;
	List R = readList( ifs ) ;
	//List R = readList( cin ) ;
	printList( R ) ;
	ifs.close() ;
	return 0 ;
}








/* 
时间限制: 400ms
内存限制: 64MB
代码长度限制: 16KB
Reversing Linked List
Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L. 
For example, given L being 1→2→3→4→5→6, if K=3, then you must output 3→2→1→6→5→4; 
if K=4, you must output 4→3→2→1→5→6.

Input Specification:

Each input file contains one test case. For each case, the first line contains the address of the first node, 
a positive N (≤10^5 ) which is the total number of nodes, and a positive K (≤N) which is the length of the 
sublist to be reversed. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next
where Address is the position of the node, Data is an integer, and Next is the position of the next node.

Output Specification:

For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the same format as in the input.

Sample Input:

00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218

Sample Output:
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1
*/