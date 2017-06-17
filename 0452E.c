/*
 * E. Three Strings
 * TOPIC: suffix automaton, dp on the states of suffix automaton, sqrt decomposition
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L(k) ((k)&((~(k))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,k) ((u)&BIT(k))
#define SET(u,k) ((u)|=BIT(k))
#define is_primary(x,ch) ((x)->len+1==(x)->son[ch]->len)
#define A (26)
#define K 3
#define N (3*100007)
#define Q (3*N)
#define MOD (1000000000LL+7LL)
typedef long long i64;

typedef struct cell {
	unsigned int u;
	struct cell *slink, *son[A+K];
	i64 freq[K];
	int len,count;
} cell;

cell *ptr,pool[Q],**head,**tail,*q[Q],*sink,*root;
char which[BIT(21)];
int BS;

int min( int x, int y ) { return x<y?x:y; }

int who( unsigned int u ) { return u>=BIT(20)?20+which[u>>20]:which[u]; }

cell *init( const int len ) {
	cell *x = ptr++;
	x->len = len, x->slink = NULL, x->u = x->count = 0, memset(x->freq,0,sizeof(x->freq));
	return x;
}

void add_son( cell *x, const int ch, cell *y ) { SET(x->u,ch), x->son[ch] = y; }

cell *split( cell *x, const int ch ) {
	unsigned int u,i;
	cell *z = init(x->len+1), *y = x->son[ch];
	for ( add_son(x,ch,z); (x = x->slink) && TST(x->u,ch) && x->son[ch] == y; add_son(x,ch,z) ) ;
	for ( u = z->u = y->u; u; i = who(L(u)), add_son(z,i,y->son[i]), u &= ~L(u) ) ;
	z->slink = y->slink, y->slink = z, ++z->count;
	return z;
}

cell *update( const int ch, const int idx ) {
	cell *new_sink = init(sink->len+1), *x;
	for ( ++new_sink->freq[idx], add_son(x=sink,ch,new_sink); (x = x->slink) && !TST(x->u,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink = (!x?root:is_primary(x,ch)?x->son[ch]:split(x,ch)); ++new_sink->slink->count;
	return new_sink;
}

char s[N/K];
i64 cnt[N/K],block[0x400];

i64 f( i64 *c, int n ) { return n==0?1LL:(c[n-1]*f(c,n-1)); }

int main() {
	int i,j,k,len,bi,bj,ri,rj;
	i64 dw;
	cell *x,*y;
	for ( i = 0; i < 21; which[BIT(i)] = i, ++i ) ;
	for ( ;1 == scanf("%s",s+1); ) {
		ptr = pool, root = sink = init(0);
		for ( k = 0, i = 1; s[i]; sink = update(s[i++]-'a',k) ) ;
		for ( len = i-1, sink = update(A+k,k); ++k < K; len = min(len,i-1), sink = update(A+k,k) ) 
			for ( scanf("%s",s+1), i = 1; s[i]; sink = update(s[i++]-'a',k) ) ;
		for ( head = tail = q, x = pool; x < ptr; ++x )
			if ( !x->count ) *tail++ = x;
		for (;head<tail;)
			if ( y = (x = *head++)->slink ) {
				for ( i=0; i<K; y->freq[i]+=x->freq[i], ++i ) ;
				if ( !--y->count ) *tail++=y;
			}
		for ( i = 1; i <= len; cnt[i++] = 0 ) ;
		BS = min(0x400,(int)(sqrt(len)));
		for ( i = 0; i <= len/BS; block[i++] = 0 ) ;
		for ( x = pool+1; x < ptr; ++x ) {
			if ( !(dw = f(x->freq,K)) ) continue ;
			i = x->slink->len+1, j = min(len,x->len);
			bi = (i/BS), bj = (j/BS), ri = (i%BS), rj = (j%BS);
			if ( bi+1 > bj-1 ) {
				for ( k = i; k <= j; ++k )
					if ( (cnt[k] += dw) >= MOD+MOD )
						cnt[k] %= MOD;
				continue ;
			}
			for ( k = ri; k <= BS-1; ++k )
				if ( (cnt[bi*BS+k] += dw) >= MOD+MOD )
					cnt[bi*BS+k] %= MOD;
			for ( k = 0; k <= rj; ++k )
				if ( (cnt[bj*BS+k] += dw) >= MOD+MOD )
					cnt[bj*BS+k] %= MOD;
			/*printf("bi = %d, bj = %d\n",bi+1,bj-1);*/
			for ( k = bi+1; k <= bj-1; ++k )
				if ( (block[k] += dw) >= MOD+MOD )
					block[k] %= MOD;
		}
		for ( k = 0; k <= len/BS; ++k )
			for ( i = k*BS; block[k] > 0 && i < (k+1)*BS; ++i )
				if ( (cnt[i] += block[k]) >= MOD+MOD )
					cnt[i] %= MOD;
		for ( i = 1; i <= len; ++i )
			if ( cnt[i] >= MOD )
				printf("%I64d ",cnt[i]%MOD);
			else printf("%I64d ",cnt[i]);
		putchar('\n');
	}
	return 0;
}

