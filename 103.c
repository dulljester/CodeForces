/*
 * 103. Traffic Lights
 * TOPIC: Dijkstra, IOI '99
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x200
#define MAXE (1<<16)
#define xchg(x,y) (((x)==(y))||((x)^=(y),(y)^=(x),(x)^=(y)))
#define bubble (xchg(pos[heap[i]],pos[heap[j]]),xchg(heap[i],heap[j]))
#define oo (0xfffffffful)
typedef enum { WHITE, BLACK } color;

int E,to[MAXE],next[MAXE],len[MAXE],n,last[N],
	tm[2][N],src,sink,rem[N],
	heap[N<<1],pos[N],cnt,
	parent[N];
color c0[N];
unsigned int d[N];

int compatible( int x, int y ) {
	if ( tm[WHITE][x] == tm[BLACK][y] && tm[BLACK][x] == tm[WHITE][y] ) {
		if ( rem[x] == rem[y] && c0[x] != c0[y] ) return 0;
		else if ( rem[x] != rem[y] && abs(rem[x]-rem[y])%(tm[WHITE][x]+tm[BLACK][x]) == 0 ) return 0;
		else if ( rem[x] == rem[y] && abs(rem[x]-rem[y])%(tm[WHITE][x]+tm[BLACK][x]) == tm[WHITE][x] ) return 0;
		else if ( rem[x] == rem[y] && abs(rem[x]-rem[y])%(tm[WHITE][x]+tm[BLACK][x]) == tm[BLACK][x] ) return 0;
	}
	return 1;
}

void add_edge( int x, int y, int w ) {
	int i = E++, j = E++;
	if ( !compatible(x,y) ) {
		E -= 2;
		return ;
	}
	to[i] = y, next[i] = last[x], last[x] = i, len[i] = w;
	to[j] = x, next[j] = last[y], last[y] = j, len[j] = w;
}

color which_color( int x, unsigned int cur_time ) {
	int P = tm[WHITE][x]+tm[BLACK][x];
	if ( cur_time < rem[x] )
		return c0[x];
	cur_time -= rem[x], cur_time %= P;
	if ( cur_time < tm[c0[x]^1][x] )
		return (c0[x]^1);
	return c0[x];
}

void push( int x ) {
	int i,j;
	if ( pos[x] < 0 )
		pos[heap[cnt]=x] = cnt, ++cnt;
	for ( j = pos[x]; j && d[heap[i=(j-1)>>1]] > d[heap[j]]; bubble, j = i ) ;
}

int pop() {
	int i,j,x = *heap;
	if ( cnt += (pos[x]=-1) ) 
		pos[*heap = heap[cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < cnt; bubble ) {
		if ( j < cnt-1 && d[heap[j]] > d[heap[j+1]] ) ++j;
		if ( d[heap[i]] <= d[heap[j]] ) break ;
	}
	return x;
}

int dijkstra() {
	int i,j,k,x,y;
	color cx,cy;
	unsigned int W,mask;

	for ( cnt = 0, x = 0; x < n; d[x] = +oo, pos[x++] = -1 ) ;
	for ( d[src] = 0, push(src); cnt; ) {
		x = pop(), cx = which_color(x,d[x]);
		for ( i = last[x]; i >= 0 && (y = to[i]) >= 0; i = next[i] ) {
			for ( mask = 0, W = d[x]; mask != 0xf && W+len[i] < d[y]; ++W ) {
				if ( (cx = which_color(x,W)) == (cy = which_color(y,W)) ) {
					d[y] = W+len[i], push(y), parent[y] = i;
					break ;
				}
				if ( cx == WHITE && cy == WHITE )
					mask |= 1;
				else if ( cx == WHITE && cy == BLACK )
					mask |= 2;
				else if ( cx == BLACK && cy == WHITE )
					mask |= 4;
				else mask |= 8;
			}
		}
	}
	return d[sink] < +oo;
}

void dump( int x ) {
	if ( x != src )
		dump(to[parent[x]^1]), printf(" %d",x+1);
	else printf("%d",src+1);
}

int main() {
	int i,j,k,m;
	char tmp[0x10];
	for ( ;2 == scanf("%d %d",&src,&sink); ) {
		for ( --src, --sink, E = 0, scanf("%d %d",&n,&m), i = 0; i < n; last[i++] = -1 ) ;
		for ( i = 0; i < n; ++i )
			scanf("%s %d %d %d",tmp,rem+i,tm[WHITE]+i,tm[BLACK]+i), c0[i] = 0[tmp]=='B'?WHITE:BLACK;
		for ( ;m-- && 3 == scanf("%d %d %d",&i,&j,&k); add_edge(--i,--j,k) ) ;
		if ( !dijkstra() ) puts("0");
		else 
			printf("%u\n",d[sink]), dump(sink), putchar('\n');
	}
	return 0;
}

