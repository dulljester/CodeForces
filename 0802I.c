/*
 * TOPIC: suffix automata
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define TST(u,k) ((u) & BIT(k))
#define SET(u,k) ((u) |= BIT(k))
#define L(k) ((k)&((~(k))+1ULL))
#define A 26
#define N (1<<17)
#define is_primary(x,y) ((x)->len+1==(y)->len)
typedef long long i64;

char which[BIT(21)];

int who( unsigned int u ) {
	return u>=BIT(20)?20+which[u>>20]:which[u];
}

typedef struct cell {
	unsigned int u;
	struct cell *slink,*son[A];
	int len,count;
	i64 freq;
} cell;

cell pool[N<<1],*ptr,*q[N<<1],**head,**tail,*sink,*root;

cell *init( int len ) {
	cell *x = ptr++;
	x->slink = NULL, x->u = x->freq = x->count = 0, x->len = len;
	return x;
}

void add_son( cell *x, int ch, cell *y ) {
	SET(x->u,ch), x->son[ch] = y;
}

cell *split( cell *x, int ch ) {
	unsigned int u;
	cell *z = init(x->len+1), *y = x->son[ch];
	z->slink = y->slink, y->slink = z, ++z->count;
	for ( u=z->u=y->u; u; add_son(z,who(L(u)),y->son[who(L(u))]), u &= ~L(u) ) ;
	for ( add_son(x,ch,z), x=x->slink; x && TST(x->u,ch) && x->son[ch]==y; add_son(x,ch,z), x=x->slink ) ;
	return z;
}

cell *update( int ch ) {
	cell *new_sink = init(sink->len+1), *x;
	for ( ++new_sink->freq, add_son(sink,ch,new_sink), x = sink->slink; x && !TST(x->u,ch); add_son(x,ch,new_sink), x = x->slink  );
	new_sink->slink = (!x?root:is_primary(x,x->son[ch])?x->son[ch]:split(x,ch));
	++new_sink->slink->count;
	return new_sink;
}

char str[N];

int main() {
	int i,j,k,ts;
	cell *x,*y;
	i64 ans;
	for ( k = 0; k < 21; which[BIT(k)] = k, ++k ) ;
	for ( scanf("%d",&ts); ts--; ) {
		ptr = pool, root = sink = init(0);
		for ( scanf("%s",str), i = 0; str[i]; sink = update(str[i++]-'a') ) ;
		for ( head = tail = q, i = 0; i < ptr-pool; ++i )
			if ( !pool[i].count )
				*tail++ = pool+i;
		for ( ;head < tail; ) 
			if ( y = (x = *head++)->slink ) {
				y->freq += x->freq;
				if ( !--y->count ) *tail++ = y;
			}
		for ( ans = 0, i = 0; i < ptr-pool; ++i ) 
			if ( y = (x=pool+i)->slink ) 
				ans += (x->len-y->len)*(x->freq*x->freq);
		printf("%I64d\n",ans);
	}
	return 0;
}

