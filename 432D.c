/*
 * 432D: Prefixes and Suffixes
 * TOPIC: suffix automata
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L(k) ((k) & ((~(k))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,k) ((u)&BIT(k))
#define SET(u,k) ((u)|=BIT(k))
#define A 26
#define N (100000+7)
#define IS_PREFIX(x) ((x)->u & BIT(A))
#define IS_SUFFIX(x) ((x)->u & BIT(A+1))
#define is_primary(x,y) ((x)->len+1==(y)->len)
#define Q (N*3)

typedef struct cell {
	struct cell *son[A],*slink;
	unsigned int u;
	int len, freq, count;
} cell;

char which[1<<20],s[N];
int who( unsigned int u ) { return u>=BIT(20)?20+which[u>>20]:which[u]; }
cell *ptr,pool[Q],*q[Q],**head,**tail,*sink,*root;
int cnt[N];

void add_son( cell *x, int ch, cell *y ) { SET(x->u,ch), x->son[ch] = y; }

cell *init( int len ) {
	cell *x;
	assert( ptr-pool < sizeof(pool)/sizeof *pool );
	x = ptr++, x->len = len, x->u = x->freq = x->count = 0, x->slink = NULL;
	return x;
}

cell *split( cell *x, int ch ) {
	cell *y = x->son[ch], *z = init(x->len+1);
	unsigned int u,i;
	z->slink = y->slink, y->slink = z, ++z->count;
	for ( u=z->u=(y->u&MASK(A)); u; i = who(L(u)), add_son(z,i,y->son[i]), u &= ~L(u) ) ;
	for ( add_son(x,ch,z); (x=x->slink) && TST(x->u,ch) && x->son[ch] == y; add_son(x,ch,z) ) ;
	return z;
}

cell *update( int ch ) {
	cell *new_sink = init(sink->len+1), *x;
	for (++new_sink->freq,SET(new_sink->u,A),add_son(x=sink,ch,new_sink); (x=x->slink) && !TST(x->u,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink = (!x?root:is_primary(x,x->son[ch])?x->son[ch]:split(x,ch));
	++new_sink->slink->count;
	return new_sink;
}

int main() {
	int i,j,k,n;
	cell *x,*y;
	for ( i = 0; i < 20; which[BIT(i)] = i, ++i ) ;
	while ( 1 == scanf("%s",s+1) ) {
		ptr = pool, root = sink = init(0);
		for ( n = 1; s[n]; sink = update(s[n++]-'A') ) ;
		for ( --n, head = tail = q, i = 0; i < ptr-pool; ++i )
			if ( !pool[i].count ) *tail++ = pool+i;
		for (;head<tail;)
			if ( (y=(x=*head++)->slink) && !((y->freq+=x->freq),--y->count) && (*tail++=y) ) ;
		for ( x=sink; x; SET(x->u,A+1),x=x->slink ) ;
		for ( i = 0; i <= n; cnt[i++] = 0 ) ;
		for ( k = 0, i = 0; i < ptr-pool; ++i ) 
			if ( (x = pool+i)->len && (x->u>>A) == 3 ) 
				cnt[x->len] = x->freq, ++k;
		for ( printf("%d\n",k), i = 1; i <= n; ++i )
			if ( cnt[i] ) 
				printf("%d %d\n",i,cnt[i]);
	}
	return 0;
}

