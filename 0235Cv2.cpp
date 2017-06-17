/*
 * C. Cyclic Quest
 * TOPIC: suffix automata, crazy DP over the states of suffix automaton
 * status: Accepted
 */
#include <iostream>
#include <set>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BIT(k) (1ULL<<(k))
#define MAXK (20)
#define N (BIT(MAXK))
#define MASK(k) (BIT(k)-1ULL)
#define Q (3*N)
#define L(k) ((k)&((~(k))+1))
#define is_primary(x,y) ((x)->len+1==(y)->len)
#define A 26
#define SET(u,k) ((u) |= BIT(k))
#define TST(u,k) ((u) & BIT(k))
typedef long long i64;
using namespace std;

char which[BIT(20)],s[N+N];
int who(unsigned int u) {return u>=BIT(20)?20+which[u>>20]:which[u];}

typedef struct cell {
	struct cell *slink,*son[A];
	unsigned int u;
	int len,count;
	i64 freq;
} cell;

cell pool[Q],*ptr,**head,**tail,*q[Q],*sink,*root;
int n,K;

cell *init( int len ) {
	int k;
	cell *x = ptr++;
	x->len=len,x->u=x->freq=x->count=0,x->slink=NULL;
	return x;
}

void add_son( cell *x, int ch, cell *y ) { assert(y); SET(x->u,ch), x->son[ch]=y; }

cell *split( cell *x, int ch ) {
	unsigned int u,i;
	cell *z = init(x->len+1), *y = x->son[ch];
	for ( u=z->u=y->u; u; i=who(L(u)), add_son(z,i,y->son[i]), u&=~L(u) ) ;
	z->slink=y->slink,y->slink=z,++z->count;
	for ( add_son(x,ch,z); (x=x->slink) && TST(x->u,ch) && x->son[ch]==y; add_son(x,ch,z) ) ;
	return z;
}

cell *update( int ch ) {
	cell *new_sink = init(sink->len+1), *x;
	for ( ++new_sink->freq, add_son(x=sink,ch,new_sink); (x=x->slink) && !TST(x->u,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink=(!x?root:is_primary(x,x->son[ch])?x->son[ch]:split(x,ch));
	++new_sink->slink->count;
	return new_sink;
}

int main() {
	int i,j,k,m,qr,ch,safe,unsafe,mid;
	cell *x,*y;
	i64 ans;
	for ( i = 0; i < 20; which[BIT(i)] = i, ++i ) ;
	for ( ;1 == scanf("%s",s+1); ) {
		ptr = pool, root = sink = init(0);
		n = strlen(s+1);
		if ( !(n&(n-1)) ) K = who(n)+1;
		else 
			for ( K = 0; BIT(K) < n; ++K ) ;
		/*assert( BIT(K) > n && (K == 0 || BIT(K-1) <= n) );*/
		for ( n = 1; s[n]; sink = update(s[n++]-'a') ) ;
		for ( head=tail=q,i = 0; i < ptr-pool; ++i )
			if ( !pool[i].count ) *tail++ = pool+i;
		for (;head<tail;(y=(x=*head++)->slink)?(!(y->freq+=x->freq,--y->count)?*tail++=y:NULL):NULL);
		for ( scanf("%d",&qr); qr-- && 1 == scanf("%s",s+1); ) {
			for ( m = strlen(s+1), i = 1, j = m+1; i <= m; s[j++] = s[i++] ) ;
			set<int> st;
			for ( ans = 0, x = root, k = 0, i = 1; i <= m+m; ++i ) {
				//assert( x && x->len >= k );
				for ( ch = s[i]-'a'; x && !TST(x->u,ch); x = x->slink ) ;
				if ( !x ) {
					x = root, k = 0;
					continue ;
				}
				if ( k > x->len ) k = x->len;
				x = x->son[ch], ++k;
				if ( k < m ) continue ;
				/*assert( x->len >= k );
				assert( k >= m );*/
				if ( !x->slink || x->slink->len < m ) {
					st.insert(x-pool);
					continue ;
				}
				for ( y = x->slink; y && y->len >= m; x = y, y = y->slink ) ;
				if ( k > x->len ) k = x->len;
				st.insert(x-pool);
			}
			for ( set<int> :: iterator it = st.begin(); it != st.end(); ans += pool[*it++].freq ) ;
			printf("%I64d\n",ans);
		}
	}
	return 0;
}

