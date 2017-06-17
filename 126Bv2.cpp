/*
 * Password
 * TOPIC: suffix automata
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#define N (1000000)
#define is_primary(x,y) ((x)->len+1==(y)->len)
#define BIT(k) (1UL<<(k))
#define TST(u,k) ((u) & BIT(k))
#define SET(u,k) ((u) |= BIT(k))
#define L(k) ((k)&((~(k))+1UL))
#define WAS_SINK_ONCE(x) ((x)->mask&1)
#define ON_SUFFIX_PATH(x) (((x)->mask>>1)&1)
#define A 26
#define MASK(k) (BIT(k)-1UL)
using namespace std;
typedef long long i64;

typedef struct cell {
	unsigned int u;
	struct cell *son[A],*slink;
	int len,pos,count,freq;
} cell;

int n;
char s[N],which[1<<21];
cell pool[3*N],*ptr = pool,*sink,*root;
queue<cell *> q;

int who( unsigned int u ) {
	return u>=BIT(20)?20+which[u>>20]:which[u];
}

cell *init( int len, int pos ) {
	cell *x = ptr++;
	x->count = x->freq = x->u = 0, x->pos = pos, x->len = len, x->slink = NULL;
	return x;
}

void add_son( cell *x, int ch, cell *y ) {
	SET(x->u,ch), x->son[ch] = y;
}

cell *split( cell *x, int ch, int pos ) {
	unsigned int u,i;
	cell *z = init(x->len+1,pos), *y = x->son[ch];
	for ( ++z->freq, add_son(x,ch,z), x = x->slink; x && TST(x->u,ch) && x->son[ch] == y && !is_primary(x,y); add_son(x,ch,z), x = x->slink ) ;
	for ( u=z->u=(y->u&MASK(A)); u; i = who(L(u)), add_son(z,i,y->son[i]), u &= ~L(u) ) ;
	z->slink = y->slink, y->slink = z, ++z->count;
	return z;
}

cell *update( int ch, int pos ) {
	cell *new_sink = init(sink->len+1,pos),*x;
	SET(new_sink->u,A), ++new_sink->freq;
	for ( add_son(sink,ch,new_sink), x = sink->slink; x && !TST(x->u,ch); add_son(x,ch,new_sink), x = x->slink ) ;
	new_sink->slink = (!x?root:is_primary(x,x->son[ch])?x->son[ch]:split(x,ch,pos));
	++new_sink->slink->count;
	return new_sink;
}

int main() {
	int i,j,k,best_len,pos;
	cell *x,*y;
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i ) ;
	while ( 1 == scanf("%s",s+1) ) {
		for ( n = 1; s[n]; ++n ) ;
		--n, ptr = pool, root = sink = init(0,-1);
		for ( i = 1; i <= n; sink = update(s[i]-'a',i), ++i ) ;
		for ( x = sink; x; SET(x->u,A+1), x = x->slink ) ;
		for ( i = 0; i < ptr-pool; ++i )
			if ( !pool[i].count ) q.push(pool+i);
		for ( ;!q.empty(); q.pop() ) 
			if ( y = (x = q.front())->slink ) {
				y->freq += x->freq;
				if ( !--y->count ) q.push(y);
			}
		for ( best_len = -1, i = 0; i < ptr-pool; ++i ) 
			if ( (x=pool+i)->len > 0 && (x->u>>A) == 3 && x->freq >= 3 )
				if ( x->len > best_len ) 
					best_len = x->len, pos = x->pos;
		if ( best_len <= 0 ) {
			puts("Just a legend");
			continue ;
		}
		for ( i = pos-best_len+1; i <= pos; putchar(s[i++]) ) ;
		putchar('\n');
	}
	return 0;
}

