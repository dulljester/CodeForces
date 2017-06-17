/*
 * E. Martian Strings
 * TOPIC: suffix automata, first occurrence, last occurrence
 * status: Accepted
 * NOTES: I wonder if this can be sped up with O(logn) structure as for jumping the suffix links, similar to LCA
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N (100000+7)
#define L(k) ((k) & ((~(k))+1ULL))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define TST(u,k) ((u)&BIT(k))
#define SET(u,k) ((u)|=BIT(k))
#define A 26
#define N (100000+7)
#define is_primary(x,y) ((x)->len+1==(y)->len)
#define Q (N*3*2)
#define M 0x400

typedef struct cell {
	unsigned int u;
	struct cell *son[A],*slink;
	int pos, len;
} cell;

cell *ptr,pool[Q];
char which[BIT(20)],s[N],p[M];
int m,n,ends[M],begins[M];
int who( unsigned int u ) { return u>=BIT(20)?20+which[u>>20]:which[u]; }

cell *init( int len, int pos ) {
	cell *x = ptr++;
	x->len=len, x->pos=pos, x->slink=NULL, x->u=0;
	return x;
}

void add_son( cell *x, int ch, cell *y ) { SET(x->u,ch),x->son[ch]=y; }

cell *split( cell *x, int ch, int pos ) {
	unsigned int u,i;
	cell *z = init(x->len+1,pos), *y = x->son[ch];
	for ( add_son(x,ch,z); (x=x->slink) && TST(x->u,ch) && x->son[ch] == y; add_son(x,ch,z) ) ;
	z->slink = y->slink, y->slink = z;
	for ( u=z->u=y->u; u; i=who(L(u)), add_son(z,i,y->son[i]), u &= ~L(u) ) ;
	return z;
}

cell *update( cell *root, cell *sink, int ch, int pos ) {
	cell *new_sink = init(sink->len+1,pos), *x;
	for ( add_son(x = sink,ch,new_sink); (x=x->slink) && !TST(x->u,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink=(!x?root:is_primary(x,x->son[ch])?x->son[ch]:split(x,ch,x->son[ch]->pos));
	return new_sink;
}

int min( int x, int y ) { return x<y?x:y; }
int max( int x, int y ) { return x<y?y:x; }

int main() {
	int i,j,k,t,ans;
	cell *root[2],*sink[2],*x,*y;
	for ( i = 0; i < 20; which[BIT(i)] = i, ++i ) ;
	while ( 1 == scanf("%s",s+1) ) {
		for ( ptr = pool, t = 0; t <= 1; root[t]=sink[t]=init(0,-1), ++t ) ;
		for ( n = 1; s[n]; s[n] = toupper(s[n]), ++n ) ;
		for ( --n, i = 1; i <= n; ++i ) 
			sink[0] = update(root[0],sink[0],s[i]-'A',i);
		for ( j = 1, i = n; i >= 1; --i, ++j )
			sink[1] = update(root[1],sink[1],s[i]-'A',j);
		for ( ans = 0, scanf("%d",&k); k-- && 1 == scanf("%s",p+1); ans += j ) {
			m = strlen(p+1);
			for ( i = 1; i <= m; ++i )
				begins[i] = ends[i] = -1;
			for ( x = root[0], i = 1; i <= m-1; ++i ) {
				for (;x && !TST(x->u,p[i]-'A'); x=x->slink ) ;
				if ( !x || x->len < i-1 ) break ;
				y = x->son[p[i]-'A'];
				assert( y->len >= i );
				for ( ends[i] = y->pos, x = y; (y=y->slink) && y->len>=i; ends[i] = min(ends[i],y->pos), x = y ) ;
			}
			for ( x = root[1], i = m; i >= 2; --i ) {
				for (;x && !TST(x->u,p[i]-'A'); x=x->slink ) ;
				if ( !x || x->len < m-i ) break ;
				y = x->son[p[i]-'A'];
				assert( y->len >= m-i+1 );
				for ( begins[i] = n-y->pos+1, x = y; (y=y->slink) && y->len>=m-i+1; begins[i] = max(begins[i],n-y->pos+1), x = y ) ;
			}
			for ( j = 0, i = 1; !j && i <= m-1; ++i ) {
				if ( ends[i] != -1 && begins[i+1] != -1 && ends[i] < begins[i+1] && ++j ) ;
				/*
				if ( ends[i] != -1 )
					printf("prefix %d of %s ends at %d\n",i,p+1,ends[i]);
				if ( begins[i+1] != -1 )
					printf("suffix %d of %s begins at %d\n",i+1,p+1,begins[i+1]);
					*/
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

