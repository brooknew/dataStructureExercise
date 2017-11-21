#include <iostream>
#include <fstream>

using namespace std ;

#define  TOTAL_V 100 

typedef struct GNode *PtrToGNode ; 

struct GNode {
	int nv ;
	int ne ;
	int G[TOTAL_V][TOTAL_V] ;
} ;

typedef PtrToGNode MGraph ;

typedef struct _Edge {
	int v1 ;
	int v2 ;
}Edge ;

MGraph createMGraph(int nv)
{
	MGraph g = (MGraph) malloc( sizeof(*g) ) ;
	g->nv = nv ;
	g->ne = 0 ;
	for( int i = 0 ; i < nv ; i ++ )
		for( int j = 0 ; j < nv ; j ++ )
			g->G[i][j] = 0 ;
	return g ;
}


void insertEdge( MGraph g , Edge e )
{
	g->G[e.v1][e.v2] = 1 ;
	g->G[e.v2][e.v1] = 1 ;
}

void printMGraph( MGraph g  )
{
	cout<<"-  "  ;
	int i ;
	for( i = 0 ; i < g->nv ; i ++ )
		cout << i << "  " ;
	cout << endl ;
	for(  i = 0 ; i < g->nv ; i ++ ) {
		cout << i << "  " ;
		for( int j = 0 ; j < g->nv ; j ++ )
			cout << g->G[i][j] << "  " ;
		cout << endl ;
	}
}


MGraph InputMGraph( istream & is ) 
{
	int nv , ne ;
	is >> nv ;
	MGraph g = createMGraph( nv ) ;
	int en = 0 ;
	is >> ne ;
	while( en ++ < ne ) {
		Edge e ;
		is >> e.v1 >> e.v2 ;
		insertEdge( g , e ) ;
	}
	return g ;
}

bool visited[ TOTAL_V ] = {false} ;
void resetVisited() 
{
	for( int i = 0 ;  i < TOTAL_V ; i++ )
		visited [ i ] = false ;
}

void DFS( MGraph g , int v )
{
	visited[v] = true ;
	cout << v << " " ;
	for( int i = 0 ; i < g->nv ; i ++ ){
		if( !visited[i]  && g->G[v][i] ) {
			DFS ( g , i ) ;
		}
	}
}

void traverseDFS ( MGraph g )
{
	for( int i = 0 ; i < g->nv ; i ++ ) {
		if( ! visited[i] ) {
			cout << "{ " ;
			DFS( g , i ) ;
			cout << "}" << endl ;
		}
	}
//	cout << endl ;	
}

#define QUEUE_ELNUM_MAX  TOTAL_V*20 
int* queue ;
int elNum = 0 ;
int elNextW = 0 ;
int elNextR = 0 ;
void initQueue()
{
	queue = (int*)malloc( QUEUE_ELNUM_MAX) ;
	elNum = 0 ;
	elNextW = 0 ;
	elNextR = 0 ;
}

void enQueue( int el ) 
{	
	queue[ elNextW  ] = el ;
	elNum ++ ;
	elNextW = (elNextW+1) % QUEUE_ELNUM_MAX ;
}

int dequeue() 
{
	int el = queue[ elNextR  ] ;
	elNum -- ;
	elNextR = (elNextR+1) % QUEUE_ELNUM_MAX;
	return el ;
}

bool isQueEmpty() 
{
	return elNum == 0 ;
}



void traverseBFS ( MGraph g )
{
	initQueue();
	resetVisited();
	for( int i = 0 ; i < g->nv ; i ++ ) {
		if( ! visited[i] ) {
			cout << "{ " ;
			cout << i << " " ;
			visited[i] = true ;
			enQueue( i ) ;
			while( true ) {
				if( isQueEmpty() )
					break ;
				int v = dequeue() ; 
				for( int j = 0 ; j < g->nv ; j ++ ) {
					if( g->G[v] [j]  &&  !visited[j]  ) {
						enQueue( j ) ;
						cout << j << " " ;
						visited[j] = true ;
					}
				}
			}
			cout << "}" << endl ;
		}
	}
//	cout << endl ;	
}


#define UsingFileIn 1

int main() 
{
#if UsingFileIn  
	ifstream ifs( "graphTraverse.txt" ) ;
	istream& is = ifs ;
#else 
	istream& is = cin  ;
#endif 
	MGraph  g = InputMGraph( is ) ; 
	//printMGraph( g ) ;

	traverseDFS( g ) ;
	
	traverseBFS( g ) ;

#if UsingFileIn
	ifs.close() ;
#endif
	return 0 ;
}


#if 0 

06-图1 列出连通集（25 分）
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N?1编号。进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。

输入格式:

输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。

输出格式:

按照"{v1 v2 ... vk }"的格式，每行输出一个连通集。先输出DFS的结果，再输出BFS的结果。

输入样例:

8 6
0 7
0 1
2 0
4 1
2 4
3 5
输出样例:

{ 0 1 4 2 7 }
{ 3 5 }
{ 6 }
{ 0 1 2 7 4 }
{ 3 5 }
{ 6 }

#endif