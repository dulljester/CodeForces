/*
 * D. String
 * TOPIC: suffix automaton
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (100000+7)
#define Q (3*N)
#define is_primary(x,y) ((x)->len+1 == (y)->len)
#define L(k) ((k)&((~(k))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,k) ((u) & BIT(k))
#define SET(u,k) ((u) |= BIT(k))
#define A 26
typedef long long i64;

typedef struct cell {
	struct cell *slink, *son[A];
	unsigned int u;
	int len,count;
	i64 freq;
} cell;

cell pool[Q],*ptr,*root,*sink,**head,**tail,*q[Q];
char which[BIT(21)],s[N];

int who( unsigned int u ) { return u>=BIT(20)?20+which[u>>20]:which[u]; }

cell *init( int len ) {
	cell *x = ptr++;
	x->u = x->freq = x->count = 0, x->len = len, x->slink = NULL;
	return x;
}

void add_son( cell *x, int ch, cell *y ) {
	x->son[ch] = y, SET(x->u,ch);
}

cell *split( cell *x, int ch ) {
	cell *z = init(x->len+1), *y = x->son[ch];
	unsigned int u,i;
	for ( u=z->u=y->u; u; i = who(L(u)), add_son(z,i,y->son[i]), u &= ~L(u) ) ;
	for ( add_son(x,ch,z); (x=x->slink) && TST(x->u,ch) && x->son[ch] == y; add_son(x,ch,z) ) ;
	z->slink = y->slink, y->slink = z, ++z->count;
	return z;
}

cell *update( int ch ) {
	cell *new_sink = init(sink->len+1), *x;
	for ( ++new_sink->freq, add_son(x = sink,ch,new_sink); (x=x->slink) && !TST(x->u,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink = (!x?root:is_primary(x,x->son[ch])?x->son[ch]:split(x,ch));
	++new_sink->slink->count;
	return new_sink;
}

i64 f( i64 freq ) { return (freq*(freq+1))>>1; }

int main() {
	int i,j,k,n;
	cell *x,*y;
	i64 ans;
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i ) ;
	for (;1==scanf("%s",s+1);) {
		ptr = pool, root = sink = init(0);
		for ( n = 1; s[n]; sink = update(s[n++]-'a') ) ;
		for ( head = tail = q, i = 0; i < ptr-pool; ++i )
			if ( !pool[i].count ) *tail++ = pool+i;
		for ( ;head<tail; )
			if ( y = (x=*head++)->slink )
				if ( !(y->freq += x->freq,--y->count) && (*tail++ = y) ) ;
		for ( ans = 0, x = pool+1; x < ptr; ++x ) 
			y = x->slink, ans += (x->len-y->len)*f(x->freq);
		printf("%I64d\n",ans);
	}
	return 0;
}

