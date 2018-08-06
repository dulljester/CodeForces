/*
 * TOPIC: centroid decomposition, LCA
 * status: Accepted
 */
#include <unistd.h>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <set>
#define ROOT (0)
#define N (1<<17)
#define MAXE (N<<1)
#define MAXK (20)
#define oo (1<<30)
#define FAST_IO 0
#define SLOW_LCA 1
typedef unsigned long long u64;
typedef int node_type;
typedef int size_type;
using namespace std;

char buffer[1<<23],*ptr;
int counter,EOF_REACHED,rem[N];

int get_num() {
	static int dig[256]= {0};
	int n= 0,ch;
	if ( !dig['0'] )
		for ( ch= '0'; ch <= '9'; dig[ch++]= 1 ) ;
#if !FAST_IO
	for ( ;(ch = getchar()) != EOF && !dig[ch]; ) ;
	for ( n= ch-'0'; (ch= getchar()) != EOF && dig[ch]; n= 10*n+ch-'0' ) ;
#else
up:
	for (;!EOF_REACHED && counter && !dig[ch= *ptr]; --counter, ++ptr ) ;
	if ( !counter && !EOF_REACHED ) {
		counter= read(STDIN_FILENO,buffer,sizeof buffer), ptr= buffer;
		if ( counter <= 0 ) {
			EOF_REACHED= 1;
			return 0;
		}
		goto up;
	}
nx:
	for (;!EOF_REACHED && counter && dig[ch= *ptr]; --counter, ++ptr, n= 10*n+ch-'0' ) ;
	if ( !counter && !EOF_REACHED ) {
		counter= read(STDIN_FILENO,buffer,sizeof buffer), ptr= buffer;
		if ( counter <= 0 ) {
			EOF_REACHED= 1;
			return n;
		}
		goto nx;
	}
#endif
	return n;
}

node_type to[MAXE],parent[N],anc[N][MAXK];
vector<node_type> pr[N];
size_type E,K,d[N],V,card[N];
int n,qr,_next[MAXE],last[N],p[N],e[N],seen[N],yes;
bool blocked[MAXE];
char msb[N];

class fast_lca {
private:
	node_type euler_tour[N<<1];
	size_type cur,BS,level[N<<1],first_occurrence[N],
			  type_of_block[N],LOGLOG,num_blocks;
	bool visited[N];
	void euler( node_type x ) {
		size_type i; node_type y;
		assert( !visited[x] );
		euler_tour[cur++]= x, first_occurrence[x]= cur-1;
		for ( visited[x]= true, i= last[x]; i >= 0; i= _next[i] )
			if ( !visited[y= to[i]] ) {
				d[y]= d[x]+1, euler(y), euler_tour[cur++]= x;
			}
	}

	inline int argmin( int i, int j ) {
		return level[i]<level[j]?i:j;
	}

	int ***small_block, **large_block;

	int sparse_rmq( int bi, int bj ) {
		int k= msb[bj-bi+1],
			a= bi, b= a+(1<<k)-1,
			c= bj-(1<<k)+1, d= bj;
		assert( a <= c && c <= b && b <= d );
		return argmin(large_block[a][k],large_block[c][k]);
	}

public:

	node_type lca( node_type x, node_type y ) {
		size_type i= first_occurrence[x], 
				  j= first_occurrence[y];
		if ( i > j ) swap(i,j);
		size_type bi= i/BS, bj= j/BS;
		if ( bi == bj ) {
			return euler_tour[bi*BS+small_block[type_of_block[bi]][i%BS][j%BS]];
		}
		else {
			int nbi= bi+1, pbj= bj-1, k1= +oo;
			if ( nbi <= pbj )
				k1= sparse_rmq(nbi,pbj);
			int k2= bi*BS+small_block[type_of_block[bi]][i%BS][BS-1];
			int k3= bj*BS+small_block[type_of_block[bj]][0][j%BS];
			int k4= argmin(k2,k3);
			if ( k1 < +oo )
				k4= argmin(k1,k4);
			return euler_tour[k4];
		}
	}

	void preprocess() {
		size_type i,j,k,t;
		memset(visited,0,sizeof visited), cur= 0;
		euler(ROOT);
		assert( cur == 2*n-1 );
		for ( BS= 0; (1 << BS) <= cur; ++BS ) ;
		for ( i= 0; i < cur; level[i]= d[euler_tour[i]], ++i ) ;
		for ( BS>>= 1; cur%BS; level[cur]= level[cur-1]+1, ++cur ) ;

		small_block= (int ***)malloc((1<<BS)*sizeof *small_block);
		unsigned int u;
		for ( u= 0; u < (1<<BS); ++u ) {
			small_block[u]= (int **)malloc(BS*sizeof *small_block[u]);
			for ( i= 0; i < BS; ++i )
				small_block[u][i]= (int *)malloc(BS*sizeof *small_block[u][i]);
		}
		int val[0x10];
		for ( u= 0; u < (1<<(BS-1)); ++u ) {
			for ( val[0]= 0, i= 1; i < BS; ++i )
				val[i]= val[i-1]+((u>>(i-1))&1)?1:-1;
			for ( i= 0; i < BS; ++i )
				small_block[u][i][i]= i;
			for ( k= 2; k <= BS; ++k )
				for ( i= 0; (j= i+k-1) < BS; ++i ) 
					small_block[u][i][j]= val[small_block[u][i][j-1]]<val[small_block[u][i+1][j]]?small_block[u][i][j-1]:small_block[u][i+1][j];
		}
		num_blocks= cur/BS;
		for ( i= 0; i < num_blocks; ++i ) 
			for ( type_of_block[i]= 0, j= 0, t= i*BS+1; t < (i+1)*BS; ++t, ++j )
				type_of_block[i]|= ((level[t]==level[t-1]+1)?1:0)<<j;

		for ( LOGLOG= 0; (1<<LOGLOG) <= num_blocks; ++LOGLOG ) ;

		large_block= (int **)malloc(num_blocks*sizeof *large_block);
		for ( i= 0; i < num_blocks; ++i )
			large_block[i]= (int *)malloc(LOGLOG*sizeof *large_block[i]);

		for ( i= 0; i < num_blocks; ++i )
			large_block[i][0]= i*BS+small_block[type_of_block[i]][0][BS-1];
		for ( j= 1; j < LOGLOG; ++j ) {
			for ( i = 0; i < num_blocks && i+(1<<j) <= num_blocks; ++i ) {
				k= i+(1<<(j-1));
				assert( k+(1<<(j-1)) == i+(1<<j) );
				large_block[i][j]= argmin(large_block[i][j-1],large_block[k][j-1]);
			}
		}
	}
};

fast_lca flca;

#if SLOW_LCA
node_type up( node_type x, unsigned int u ) {
	int k= 0;
	for ( ;u; ++k, u >>= 1 )
		if ( u&1 )
			x= anc[x][k];
	return x;
}

node_type lca( node_type x, node_type y ) {
	if ( d[x] > d[y] )
		return lca(up(x,d[x]-d[y]),y);
	if ( d[x] < d[y] )
		return lca(y,x);
	assert( d[x] == d[y] );
	if ( x == y )
		return x;
	for ( int k= K-1; k; --k ) {
		assert( anc[x][k] == anc[y][k] );
		if ( anc[x][k-1] != anc[y][k-1] )
			x= anc[x][k-1], y= anc[y][k-1];
	}
	return anc[x][0];
}
#endif

void add_arcs( node_type x, node_type y ) {
	int i= E++, j= E++;
	to[i]= y, _next[i]= last[x], last[x]= i;
	to[j]= x, _next[j]= last[y], last[y]= j;
	blocked[i]= blocked[j]= false ;
}

size_type dist( node_type x, node_type y ) { 
	node_type z;
#if !SLOW_LCA
	z= flca.lca(x,y);
#else
	z= lca(x,y);
#endif
	return d[x]+d[y]-2*d[z];
}

size_type dfs( node_type x ) {
	int i,k;
	node_type y;
	assert( !card[x] );
	for ( card[x]= 1, i= last[x]; i >= 0; i= _next[i] )
		if ( !card[y= to[i]] ) {
#if SLOW_LCA
			for ( d[y]= d[x]+1, p[y]= i, anc[y][0]= x, k= 1; anc[y][k-1] >= 0; anc[y][k]= anc[anc[y][k-1]][k-1], ++k ) ;
#endif
			p[y]= i, card[x]+= dfs(y);
		}
		else {
			assert( p[x] == (i^1) ) ;
		}
	return card[x];
}

size_type find_card( node_type x ) {
	int i,k;
	node_type y;
	assert( seen[x] != yes );
	for ( seen[x]= yes, card[x]= 1, i= last[x]; i >= 0; i= _next[i] )
		if ( !blocked[i] && seen[y= to[i]] != yes ) 
			p[y]= i, card[x]+= find_card(y);
	return card[x];
}

node_type find_centroid( node_type x, size_type limit ) {
	int i,j= -1; node_type y;
	for ( i= last[x]; i >= 0; i= _next[i] )
		if ( !blocked[i] )
			if ( p[y= to[i]] == i )
				if ( card[y] > limit && (j == -1 || card[y] > card[to[j]]) )
					j= i;
	return j==-1?x:find_centroid(to[j],limit);
}

node_type centroid_decomposition( node_type x, size_type limit ) {
	node_type root= find_centroid(x,limit), y, z;
	++yes;
	for ( int i= last[root]; i >= 0; i= _next[i] )
		if ( !blocked[i] ) {
			assert( p[y= to[i]] == i || p[root] == (i^1) );
			blocked[i]= blocked[i^1]= true;
			assert( seen[y] != yes );
			find_card(y);
			z= centroid_decomposition(y,(limit<<1)/3);
			parent[z]= root;
		}
	return root;
}

void update( node_type x ) {
	for ( node_type y= x; y >= 0; e[y]= min(e[y],dist(x,y)), y= parent[y] ) ;
}

size_type query( node_type x ) {
	size_type ans= +oo;
	for ( node_type y= x; y >= 0; y= parent[y] ) 
		if ( e[y] < +oo )
			ans= min(ans,dist(x,y)+e[y]);
	return ans;
}

char output[1<<21],*qtr= output;

void wrt( int x ) {
	if ( x < 10 )
		*qtr++= x+'0';
	else wrt(x/10), *qtr++= rem[x]+'0';
}

int main() {
	int i,j,k,comm;
	node_type x,y,r;
	for ( k= 0; k < N; rem[k]= (k%10), ++k ) ;
	for ( k= 1; k < N; msb[k++]= j )
		for ( j= 16; !((k>>j)&1); --j ) ;
#if FAST_IO
	counter= read(STDIN_FILENO,buffer,sizeof buffer), ptr= buffer;
#endif
	for (;;) {
		n= get_num(), qr= get_num();
		for ( E= 0, i= 0; i < n; e[i]= +oo, last[i++]= -1 ) ;
		for ( k= 0; k < n-1; ++k ) 
			i= get_num(), j= get_num(), add_arcs(--i,--j); 
		for ( K= 0; (1<<K) < n; ++K ) ;
#if SLOW_LCA
		for ( x= 0; x < n; ++x )
			for ( k= 0; k < K; anc[x][k++]= -1 ) ;
#endif
		memset(parent,-1,sizeof parent);
		memset(card,0,sizeof card), d[ROOT]= 0, dfs(ROOT), flca.preprocess();
		r= centroid_decomposition(ROOT,1<<K);
		for ( update(ROOT); qr--; ) {
			comm= get_num(), x= get_num();
			switch ( comm ) {
				case 1:  update(x-1); break ;
				//case 2:  wrt(query(x-1)), *qtr++= '\n'; break ;
				case 2:  printf("%d\n",query(x-1)); break ;
				default: assert( 0 );
			}
		}
		break ;
	}
	//if ( qtr > output ) *--qtr= '\0';
	//fflush(stdout);
	//write(1,output,qtr-output);
	return 0;
}

