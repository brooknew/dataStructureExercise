
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std ;

#if 1

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
	int num = 1 ;
	while( L->addressN != -1 ){
		L->next = & LN[ L->addressN] ;
		L = L->next ;
		num ++ ;
	}
	//cout << "tot:"<<num <<endl ;
//
	//printList(  L0 ) ;
//
	int count = 0 ;
	NodePtr head0 = (NodePtr)malloc(sizeof(*head0) ) ;
	head0->next = L0 ;
	NodePtr head = (NodePtr)malloc(sizeof(*head) ) ;
	//head->next = L0 ;
	List tmp =  L0 ;
	List lastTail ;
	while( count <  num /K  ) {
		i = 1 ;		
		head->next = tmp ;
		List L2 = head->next  ;
		while ( i < K ) {
			tmp = L2->next   ; //L2:first , tmp:2nd 
			L2->next = tmp->next ; //L2(first): linked to 3rd
			//L2->addressN = tmp->next->addressC ;
			tmp->next = head->next ; 
			tmp->addressN = head->next->addressC ;
		
			head->next = tmp ; //						
			i++ ;
		}
		
		if( count == 0 ){
			head0->next = head->next ;
			lastTail = L2 ;
		}
		else {
			lastTail->next = head->next ;
			lastTail = L2 ;
		}
		
		
		tmp = L2 -> next ;
		if( tmp == NULL ) {
			L2->addressN = -1 ;
			break ;
		}
		
		count ++ ;
	}
	return head0->next ;
}


#define UsingFileIn 0 
int main() 
{
#if UsingFileIn
	string filen="ReverseLinkedList.txt" ;
	ifstream ifs( filen.c_str() ) ;
	List R = readList( ifs ) ;
#else
	List R = readList( cin ) ;
#endif
	
	printList( R ) ;

#if UsingFileIn
	ifs.close() ;
#endif 
	return 0 ;
}

#endif

#if 0

typedef struct LNode
{
    int     data;
    struct LNode    *next;
}LNode, *LinkedList;



LinkedList ReverseSinglyLinkedList(LinkedList list)
{
    LinkedList  newList;    //新链表的头结点
    LNode       *tmp;       //指向list的第一个结点，也就是要摘除的结点
 
    //
    //参数为空或者内存分配失败则返回NULL
    //
    if (list == NULL || (newList = (LinkedList)malloc(sizeof(LNode))) == NULL)
    {
        return NULL;
    }
 
    //
    //初始化newList
    //
    newList->data = list->data;
    newList->next = NULL;
 
    //
    //依次将list的第一个结点放到newList的第一个结点位置
    //
    while (list->next != NULL)
    {
        tmp = newList->next;         //保存newList中的后续结点
        newList->next = list->next;       //将list的第一个结点放到newList中
        list->next = list->next->next;     //从list中摘除这个结点
        newList->next->next = tmp;        //恢复newList中后续结点的指针
    }
 
    //
    //原头结点应该释放掉，并返回新头结点的指针
    //
    free(list);
    return newList;
}

 
LinkedList ReverseSinglyLinkedList1(LinkedList list)
{
    LNode   *tmp = NULL;
    LNode   *p = NULL;
 
    if (list == NULL)
    {
        return NULL;
    }
    tmp = list->next;
    while (tmp->next != NULL)
    {
        p = tmp->next;
        tmp->next = p->next;
        p->next = list->next;
        list->next = p;
    }
    return list;
}


void printList( LinkedList L ) 
{
	LinkedList L1 = L->next ;
	while( L1 ) {
		cout << L1->data << " "  ;
		L1 = L1->next ;
	}

}



int main()
{
	LinkedList L = (LinkedList)malloc( sizeof( *L ) ) ;
	L->data = -1 ;
	L->next = NULL ;
	LinkedList L0 = L ;
	for( int i = 1 ; i < 16 ; i ++ ) {
		LinkedList L1 = (LinkedList)malloc( sizeof( *L1 ) ) ;
		L1->data  = i ;
		L1->next = NULL ;
		L->next = L1 ;
		L = L1 ;
	}
	printList( L0 ) ;
	cout << endl ;
	LinkedList NL = ReverseSinglyLinkedList1(L0) ;
	printList( NL ) ;
}
#endif 

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