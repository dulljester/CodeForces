/*
 * 131. Hardwood Floors
 * TOPIC: bitmasks, DP
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 9
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
typedef unsigned long long u64;

u64 z[N+2][1<<N];
int m,n;

void dfs( int row, unsigned int nu, unsigned int v, int col, u64 weight ) {
	if ( col == n ) {
		assert( nu == MASK(n) );
		z[row+1][v] += weight;
		return ;
	}
	assert( col < n );
	if ( nu&BIT(col) )
		dfs(row,nu,v,col+1,weight);
	else {
		if ( col+1<n && !(nu&BIT(col+1)) ) {
			dfs(row,nu|(3<<col),v,col+2,weight); /* 1x2 bar horisontally */
			if ( !(v&BIT(col)) && row+1 <= m )
				dfs(row,nu|(3<<col),v|BIT(col),col+2,weight);
			if ( !(v&BIT(col+1)) && row+1 <= m )
				dfs(row,nu|(3<<col),v|BIT(col+1),col+2,weight);
		}
		if ( row+1<=m ) {
			if ( !(v&BIT(col)) )
				dfs(row,nu|BIT(col),v|BIT(col),col+1,weight);
			if ( col+1 < n && !(v&(3<<col)) )
				dfs(row,nu|BIT(col),v|(3<<col),col+1,weight);
			if ( col >= 1 && !(v&(3<<(col-1))) )
				dfs(row,nu|BIT(col),v|(3<<(col-1)),col+1,weight);
		}
	}
}

int main() {
	int i,j,k;
	unsigned int u;
	for ( ;2 == scanf("%d %d",&m,&n); printf("%llu\n",z[m+1][0]) ) {
		memset(z,0,sizeof z);
		if ( m == 1 ) {
			printf("%d\n",1-(n&1));
			continue ;
		}
		assert( m >= 2 );
		for ( z[1][0] = 1, i = 1; i <= m; ++i ) 
			for ( u = 0; u < (1<<n); ++u )
				if ( z[i][u] )
					dfs(i,u,0,0,z[i][u]);
	}
	return 0;
}

