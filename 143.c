/*
 * 143. Long Live the Queen
 * TOPIC: DP on trees, classics
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (16001)
#define MAXE (N<<1)
#define oo (1<<30)

int max( int x, int y ) { return x<y?y:x; }

int E,V,n,to[MAXE],next[MAXE],last[N],weight[N],
	z[2][N],p[N],*head,*tail,q[N],seen[N],yes;

void add_arcs( int x, int y ) {
	int i = E++, j = E++;
	to[i] = y, next[i] = last[x], last[x] = i;
	to[j] = x, next[j] = last[y], last[y] = j;
}

int calc_z( int t, int x ) {
	int i,y;
	if ( z[t][x] > -oo )
		return z[t][x];
	if ( t == 0 ) {
		for ( z[t][x] = 0, i = last[x]; i >= 0; i = next[i] )
			if ( p[y = to[i]] == i )
				z[t][x] = max(z[t][x],max(calc_z(0,y),calc_z(1,y)));
	}
	else {
		for ( z[t][x] = weight[x], i = last[x]; i >= 0; i = next[i] )
			if ( p[y = to[i]] == i ) 
				z[t][x] = max(z[t][x],z[t][x]+calc_z(1,y));
	}
	return z[t][x];
}

int main() {
	int i,j,k,x,y,ans;
	for ( ;1 == scanf("%d",&n); ) {
		for ( E = 0, i = 0; i < n; scanf("%d",&weight[i]), p[i] = -1, last[i++] = -1 ) ;
		for ( k = 0; k < n-1 && 2 == scanf("%d %d",&i,&j); add_arcs(--i,--j), ++k ) ;
		for ( head = tail = q, seen[*tail++ = 0] = ++yes; head < tail; )
			for ( i = last[x = *head++]; i >= 0; i = next[i] )
				if ( seen[y = to[i]] != yes )
					seen[*tail++ = y] = yes, p[y] = i;
		for ( x = 0; x < n; ++x )
			for ( k = 0; k < 2; z[k++][x] = -oo ) ;
		for ( ans = -oo, x = 0; x < n; ++x )
			ans = max(ans,calc_z(1,x));
		printf("%d",ans);
		break;
	}
	return 0;
}

