/*
 * D. Match and Catch
 * TOPIC: suffix automata
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L(k) ((k) & ((~(k))+1))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SET(u,k) ((u)|=BIT(k))
#define TST(u,k) ((u) & BIT(k))
#define N (2*5000+7)
#define Q (3*N)
#define is_primary(x,ch) ((x)->len+1==(x)->son[ch]->len)
#define A 26

typedef struct cell {
	unsigned int u;
	struct cell *son[A+2],*slink;
	int len, freq[2], count;
} cell;

char which[BIT(21)];
int who( unsigned int u ) { return u>=BIT(20)?20+which[u>>20]:which[u]; }
cell *ptr,pool[Q],**head,**tail,*q[Q],*root,*sink;

cell *init( int len ) {
	cell *x = ptr++;
	x->len = len, x->slink = NULL, x->u = 0, x->freq[0]=x->freq[1]=x->count = 0;
	return x;
}

void add_son( cell *x, int ch, cell *y ) { SET(x->u,ch), x->son[ch] = y; }

cell *split( cell *x, int ch ) {
	unsigned int u,i;
	cell *z = init(x->len+1), *y = x->son[ch];
	for ( add_son(x,ch,z); (x = x->slink) && TST(x->u,ch) && x->son[ch] == y; add_son(x,ch,z) );
	for ( u = z->u = y->u; u; i = who(L(u)), add_son(z,i,y->son[i]), u &= ~L(u) );
	z->slink = y->slink, y->slink = z, ++z->count;
	return z;
}

cell *update( int ch, int idx ) {
	cell *new_sink = init(sink->len+1), *x;
	for ( ++new_sink->freq[idx], add_son(x=sink,ch,new_sink); (x = x->slink) && !TST(x->u,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink = (!x?root:is_primary(x,ch)?x->son[ch]:split(x,ch));
	++new_sink->slink->count;
	return new_sink;
}

char s[N];

int main() {
	int i,j,k,len;
	cell *x,*y;
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i ) ;
	while ( 1 == scanf("%s",s+1) ) {
		ptr = pool, root = sink = init(0);
		sink = update(A,0);
		for ( i = 1; s[i]; sink = update(s[i++]-'a',0) ) ;
		sink = update(A+1,1);
		for ( scanf("%s",s+1), i = 1; s[i]; sink = update(s[i++]-'a',1) ) ;
		for ( head = tail = q, x = pool+1; x < ptr; ++x )
			if ( !x->count ) *tail++ = x;
		for ( ;head < tail; )
			if ( y = (x=*head++)->slink ) {
				for ( i = 0; i < 2; ++i ) y->freq[i] += x->freq[i];
				if ( !--y->count ) *tail++ = y;
			}
		for ( len = (1<<30), x = pool+1; x < ptr; ++x )
			if ( x->freq[0] == 1 && x->freq[1] == 1 ) {
				y = x->slink;
				if ( len > y->len+1 )
					len = y->len+1;
			}
		printf("%d\n",len == (1<<30)?-1:len);
	}
	return 0;
}

