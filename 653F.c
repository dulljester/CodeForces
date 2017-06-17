/*
 * F. Paper Task
 * TOPIC: suffix automata
 * status:
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (500000+7)
#define L(k) ((k) & ((~(k))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define is_primary(x,ch) ((x)->len+1 == (x)->son[ch]->len)
#define A 2
#define Q (3*N)
#define TST(u,k) ((u) & BIT(k))
#define SET(u,k) ((u) |= BIT(k))
#define ACCESS(arr,k) (arr[(k)>>3]&BIT((k)&7))
#define SETBIT(arr,k) (arr[(k)>>3]|=BIT((k)&7))
#define oo (1<<30)

int min( int x, int y ) { return x<y?x:y; }

typedef struct cell {
	unsigned char u;
	struct cell *son[A],*slink;
	int len, pos, minw;
} cell;

cell *ptr, pool[Q], *sink, *root;

void add_son( cell *x, int ch, cell *y ) {
	SET(x->u,ch), x->son[ch] = y;
}

int who( unsigned char u ) {
	return u-1;
}

cell *init( int len, int pos ) {
	cell *x = ptr++;
	x->pos = pos, x->len = len, x->u = 0, x->slink = NULL, x->minw = +oo;
	return x;
}

cell *split( cell *x, int ch ) {
	cell *z = init(x->len+1,x->son[ch]->pos), *y = x->son[ch];
	unsigned char u,i;
	for ( u = z->u = y->u; u; i = who(L(u)), add_son(z,i,y->son[i]), u &= ~L(u) );
	for ( add_son(x,ch,z); (x = x->slink) && TST(x->u,ch) && x->son[ch] == y; add_son(x,ch,z) ) ;
	z->slink = y->slink, y->slink = z;
	return z;
}

cell *update( int ch, int pos ) {
	cell *new_sink = init(sink->len+1,pos), *x;
	for ( add_son(x = sink,ch,new_sink); (x = x->slink) && !TST(x->u,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink = (!x?root:is_primary(x,ch)?x->son[ch]:split(x,ch));
	return new_sink;
}

int n,prefix[N],P[N],tr[3*N];
unsigned char s[(N>>3)+8];

int build_tree( int v, int i, int j ) {
	int k = (i+j)/2;
	if ( i == j )
		return tr[v] = P[i];
	return tr[v] = min(build_tree(2*v,i,k),build_tree(2*v+1,k+1,j));
}

int query( int v, int i, int j, int qi, int qj ) {
	int k = (i+j)/2;
	if ( qi > j || qj < i ) return +oo;
	if ( qi <= i && j <= qj )
		return tr[v];
	return min(query(2*v,i,k,qi,qj),query(2*v+1,k+1,j,qi,qj));
}

int f( cell *x ) {
	int i,j,k;
	assert( x );
	if ( x->minw < +oo || !x->slink )
		return x->minw;
	j = x->pos, i = j-x->len+1, k = j-x->slink->len;
	x->minw = f(x->slink)<+oo?f(x->slink)+prefix[k]:+oo;
	for ( ;k >= i; --k )
		x->minw = min(x->minw,prefix[k]);
	return x->minw = (x->minw<+oo)?x->minw-prefix[i-1]:+oo;
}

int main() {
	int i,j,k,t,ans,minw;
	char ch;
	cell *x;
	for ( ;1 == scanf("%d\n",&n); ) {
		for ( i = 0; i <= (n>>3); s[i++] = 0 ) ;
		ptr = pool, root = sink = init(0,0);
		for ( i = 1; i <= n; ++i ) {
			while ( (ch = getchar()) != '(' && ch != ')' ) ;
			if ( ch == ')' ) SETBIT(s,i);
			sink=update(ch=='('?0:1,i);
			prefix[i]=prefix[i-1]+(ch=='('?1:-1);
		}
		for ( P[n+1] = 0, i = n; i >= 1; --i )
			P[i] = P[i+1]+(ACCESS(s,i)?1:-1);
		build_tree(1,1,n);
		for ( ans = 0, x = pool+1; x < ptr; ++x ) {
			j = x->pos, i = j-x->len+1, k = j-x->slink->len;
			if ( !ACCESS(s,j) || prefix[j]-prefix[k] > 0 || query(1,1,n,k+1,j) < P[j+1] ) continue ;
			for ( t = !((j-k+1)&1)?k:(k-1), minw = min(f(x->slink)<+oo?f(x->slink)+prefix[k]:+oo,prefix[k]), minw=(t==k-1)?min(minw,prefix[t]):minw; t >= i; t -= 2 ) {
				// printf("%d\n",++scanned[t]);
				assert( !((j-t+1)&1) );
				if ( prefix[j] == prefix[t-1] && !ACCESS(s,t) && minw >= prefix[t-1] ) {
					0&&printf("[%d,%d]\n",t,j);
					++ans;
				}
				if ( t-1 >= i ) minw = min(minw,prefix[t-1]);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

