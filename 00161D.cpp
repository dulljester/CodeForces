/*
 * TOPIC: DP
 * status: Accepted
 */
#include <unistd.h>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <iostream>
#define N (1<<16)
#define MAXK (20)
#define MAXE (N<<1)
#define ROOT (0)
using namespace std;
typedef int node_type;
typedef int size_type;
typedef int idx_type;
typedef unsigned long long u64;
typedef long long i64;
#define FAST_IO 1

char buffer[1<<21],*ptr;
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


size_type n,last[N],_next[MAXE],E,m,d[N],K;
node_type to[MAXE];
idx_type p[N];
bool visited[N];
u64 ans;

void add_arcs( node_type x, node_type y ) {
	idx_type i= E++, j= E++;
	to[i]= y, _next[i]= last[x], last[x]= i;
	to[j]= x, _next[j]= last[y], last[y]= j;
}

void
dfs( node_type x ) {
	idx_type i,k;
	node_type y;
	assert( !visited[x] );
	for ( visited[x]= true, i= last[x]; i >= 0; i= _next[i] )
		if ( !visited[y= to[i]] ) {
			//for ( p[y]= i, d[y]= d[x]+1, anc[y][0]= x, k= 1; anc[y][k-1] >= 0; anc[y][k]= anc[anc[y][k-1]][k-1], ++k ) ;
			p[y]= i, dfs(y);
		}
}

unsigned int dp[N][0x200];

void calc_dp( node_type x ) {
	idx_type i;
	node_type y;

	if ( visited[x] ) return ;
	visited[x]= true;
	for ( size_type k= 0; k <= m; ++k )
		dp[x][k]= 0;
	for ( i= last[x]; i >= 0; i= _next[i] )
		if ( p[y= to[i]] == i ) {
			calc_dp(y);
			for ( size_type k= 0; k+1 <= m; ++k )
				dp[x][k+1]+= dp[y][k];
		}
	dp[x][0]= 1;
}

void f( node_type x ) {
	idx_type i;
	node_type y;
	assert( !visited[x] );
	visited[x]= true ;
	for ( i= last[x]; i >= 0; i= _next[i] )
		if ( p[y= to[i]] == i ) {
			f(y);
			for ( int k= 0,l; k+1 <= m; ++k ) {
				l= m-1-k;
				assert( l >= 0 && l <= m );
				u64 w= dp[y][k], u= dp[x][l]-(l?dp[y][l-1]:0);
				ans+= w*u;
			}
		}
	ans+= dp[x][m];
}

int main() {
	int i,j,k;
	node_type x,y,z,r;
	for ( ;; ) {
#if FAST_IO
	counter= read(STDIN_FILENO,buffer,sizeof buffer), ptr= buffer;
#endif
		n= get_num(), m= get_num();
		memset(p,-1,sizeof p);
		for ( E= 0, x= 0; x < n; last[x++]= -1 ) ;
		for ( k= 0; k < n-1; x= get_num(), y= get_num(), add_arcs(--x,--y), ++k ) ;
		memset(visited,0,sizeof visited);
		dfs(ROOT), ans= 0;
		memset(visited,0,sizeof visited);
		calc_dp(ROOT);
		memset(visited,0,sizeof visited);
		f(ROOT);
		cout << ans/2 << endl;
		break ;
	}
	return 0;
}

