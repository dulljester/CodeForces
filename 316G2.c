/*
 * G3. Good Substrings
 * TOPIC: suffix automaton
 * status: 
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXK (19)
#define MAXT (11)
#define N (MAXT*MAXLEN)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define is_primary(x,ch) ((x)->len+1 == (x)->son[ch]->len)
#define TST(u,k) ((u)&BIT(k))
#define SET(u,k) ((u)|=BIT(k))
#define Q (3*N)
#define A 26
#define L(k) ((k)&((~(k))+1ULL))
#define MAXLEN (50000+7)
typedef unsigned long long u64;

typedef struct cell {
	u64 u;
	struct cell *son[A+MAXT],*slink;
	int len,freq[MAXT],count,pos;
} cell;

cell *ptr,pool[Q],**head,**tail,*q[Q],*sink,*root;
char which[BIT(21)];
int who( u64 u ) { return u>=BIT(20)?20+which[u>>20]:which[u]; }

cell *init( int len, int pos ) {
	cell *x = ptr++;
	x->len = len, x->u = x->count = 0, x->slink = NULL, x->pos = pos;
	memset(x->freq,0,sizeof x->freq);
	return x;
}

void add_son( cell *x, int ch, cell *y ) { SET(x->u,ch), x->son[ch] = y; }

cell *split( cell *x, int ch, int pos ) {
	cell *z = init(x->len+1,pos), *y = x->son[ch];
	u64 u,i;
	for ( add_son(x,ch,z); (x = x->slink) && TST(x->u,ch) && x->son[ch] == y; add_son(x,ch,z) ) ;
	for ( u = z->u = y->u; u; i = who(L(u)), add_son(z,i,y->son[i]), u &= ~L(u) ) ;
	z->slink = y->slink, y->slink = z, ++z->count;
	return z;
}

cell *update( int ch, int pos, int idx ) {
	cell *new_sink = init(sink->len+1,pos), *x;
	for ( ++new_sink->freq[idx], add_son(x = sink,ch,new_sink); (x = x->slink) && !TST(x->u,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink = (!x?root:is_primary(x,ch)?x->son[ch]:split(x,ch,x->son[ch]->pos));
	++new_sink->slink->count;
	return new_sink;
}

char s[MAXLEN];
int rules, left[MAXT], right[MAXT], bad_position[MAXT];

int main() {
	int i,j,k,ans,n,l,r;
	cell *x,*y;
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i ) ;
	for ( ;1 == scanf("%s",s+1); ) {
		ptr = pool, sink = root = init(0,0);
		for ( n = 1, i = 1; s[i]; sink = update(s[i++]-'a',n++,0) ) ;
		for ( sink = update(A+0,n++,0), bad_position[0]=n-1,\
				scanf("%d",&rules), k = 1; k <= rules; scanf("%d %d",left+k,right+k), sink = update(A+k,n++,k), bad_position[k]=n-1, ++k ) 
			for ( scanf("%s",s+1), i = 1; s[i]; sink = update(s[i++]-'a',n++,k) ) ;
		for ( head = tail = q, x = pool+1; x < ptr; ++x )
			if ( !x->count ) *tail++ = x;
		for ( ;head<tail; )
			if ( y = (x=*head++)->slink ) {
				for ( i = 0; i <= rules; ++i )
					y->freq[i] += x->freq[i];
				if ( !--y->count ) *tail++ = y;
			}
		for ( ans = 0, x = pool+1; x < ptr; ans += k*(x->len-x->slink->len), ++x ) {
			assert( x->slink ) ;
			l = x->pos-x->len+1, r = x->pos;
			if ( r >= bad_position[0] ) { k = 0; continue ; }
			k = (l<=bad_position[0]&&bad_position[0]<=r)?0:1;
			for ( i = 1; x->freq[0] && k && i <= rules; ++i ) {
				if ( !(left[i] <= x->freq[i] && x->freq[i] <= right[i]) ) k = 0;
				if ( k && l <= bad_position[i] && bad_position[i] <= r ) k = 0;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

