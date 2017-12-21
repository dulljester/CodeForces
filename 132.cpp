/*
 * 132. Another Chocolate Maniac
 * TOPIC: bitmasks, DP, number systems
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#define Q (1<<21)
#define N (1<<7)
#define oo (0xfffffffful)
#define BIT(k) (1ULL<<(k))
#define MASK(k) ((BIT(k))-1ULL)
#define enc(x,y,z) ((x) | ((y)<<7) | ((z)<<14))
#include <set>
enum { NONE = 0, HOR = 1, VER = 2 };
using namespace std;

unsigned int g[0x80];
int m,n,deg[8];
bool is_good[8][1<<7];
unsigned char z[2][1<<8][1<<8],bts[1<<8];

unsigned int 
combine( unsigned int ww, unsigned int www, unsigned int u, int row, unsigned int *rk, int *k ) {
	int i,j,digit;
	unsigned int nu = u;
	for ( *k = 0, *rk = g[row+1], i = 0; i < n && ww; ww >>= 1, ++i ) {
		if ( !(digit = (ww&1)) ) continue ;
		digit = (www&1)?VER:HOR;
		if ( ((nu>>i)&1) ) return +oo;
		++(*k), www >>= 1;
		if ( digit == HOR ) {
			if ( i == n-1 || ((nu>>(i+1))&1) ) return +oo;
			nu |= (3 << i);
		}
		else if ( digit == VER ) {
			if ( (*rk) & (1<<i) ) return +oo;
			*rk |= (1<<i), nu |= (1<<i);
		}
	}
	return nu;
}

void dfs( int t, int row, unsigned int ri, unsigned int rrj, unsigned int rk, int col, int cost ) {

	if ( (~ri & ~rrj) & MASK(col) ) return ;
	if ( !is_good[col][rrj & MASK(col)] ) return ;

	if ( col == n ) {
		if ( is_good[n][rrj] && z[t][rrj][rk] > cost )
			z[t][rrj][rk] = cost;
		return ;
	}

	assert( col < n );

	dfs(t,row,ri,rrj,rk,col+1,cost);

	if ( (rrj>>col)&1 ) 
		return ;

	if ( col+1 < n && !((rrj>>(col+1))&1) ) 
		dfs(t,row,ri,rrj|(3<<col),rk,col+2,cost+1);

	if ( !((rk>>col)&1) ) 
		dfs(t,row,ri,rrj|(1<<col),rk|(1<<col),col+1,cost+1);
}

int main() {
	int i,j,k,row,t,currow;
	char tmp[0x80];
	unsigned int u,v,base,uu,ri,rj,rrj,rk,w,ans,ww,www,base2;
	for ( deg[0] = 1, k = 0; k <= 7; deg[k] = 3*deg[k-1], ++k )
		for ( u = 0; u < (1<<k); ++u ) 
			for ( is_good[k][u] = true, i = 0; i < k-1 && is_good[k][u]; ++i )
				if ( 0 == ((u>>i)&3) )
					is_good[k][u] = false;
	for ( u = 1; u < (1<<8); bts[u] = bts[u>>1]+(u&1), ++u ) ;
	for ( ;2 == scanf("%d %d",&m,&n); printf("%u\n",ans) ) {
		memset(g,0,sizeof g), memset(z,0xff,sizeof z);
		for ( i = 1; i <= m; ++i ) 
			for ( scanf("%s",tmp), j = 0; j < n; ++j )
				g[i] |= ((tmp[j]=='*'?1:0)<<j);
		for ( t = 0, g[0]=MASK(n), ans = +oo, z[t][g[0]][g[1]] = 0, currow = 1; currow <= m; ++currow ) {
			for ( t ^= 1, ri = 0; ri < (1<<n); ++ri )
				for ( rj = 0; rj < (1<<n); ++rj )
					z[t][ri][rj] = 0xfful;
			for ( row = currow, ri = 0; ri < (1<<n); ++ri )
				if ( is_good[n][ri] )
					for ( rj = 0; rj < (1<<n); ++rj ) 
						if ( z[t^1][ri][rj] < 0xfful ) 
							dfs(t,row,ri,rj,g[row+1],0,z[t^1][ri][rj]);
							/*for ( ww = base = (~rj)&MASK(n);; ww = (ww-1)&base ) {
								for ( www = 0; www < (1<<bts[ww]); ++www ) {
									rrj = combine(ww,www,rj,row,&rk,&k);
									if ( rrj == +oo || !is_good[n][rrj] ) continue ;
									if ( (~ri & ~rrj) & MASK(n) ) continue ;
									if ( z[t][rrj][rk] > z[t^1][ri][rj]+k ) 
										z[t][rrj][rk] = z[t^1][ri][rj]+k;
								}
								if ( !ww ) break ;
							}
							*/
		}
		for ( ri = 0; ri < (1<<n); ++ri )
			if ( is_good[n][ri] )
				if ( z[t][ri][0] < ans )
					ans = z[t][ri][0];
	}
	return 0;
}

