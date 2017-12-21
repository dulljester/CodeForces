/*
 * 168. Matrix
 * TOPIC: DP
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define N 0x400
#define oo (1<<30)

int m,n;
int a[N][N],b[N][N],dp[N][N],c[N];

int min( int x, int y ) { return x>y?y:x; }

int main() {
	int i,j,k;
	for ( ;2 == scanf("%d %d",&m,&n); ) {
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; ++j )
				scanf("%d",&a[i][j]);
		for ( i = 0; i <= m+1; ++i )
			for ( j = 0; j <= n+1; ++j )
				dp[i][j] = b[i][j] = +oo;
		for ( k = m+n; k >= 2; --k ) {
			for ( j = n; j >= 1 && !((i=k-j) >= 1 && i <= m); --j ) ;
			for ( dp[i][j] = a[i][j], --j; j >= 1 && 1 <= (i=k-j) && i <= m; dp[i][j] = min(a[i][j],dp[k-(j+1)][j+1]), --j ) ;
		}
		for ( j = n; j >= 1; --j ) 
			for ( c[m+1] = +oo, i = m; i >= 1; --i ) {
				b[i][j] = min(b[i][j+1],dp[i][j]);
				c[i] = min(a[i][j],c[i+1]);
				b[i][j] = min(b[i][j],c[i]);
			}
		for ( i = 1; i <= m; printf("%d\n",b[i++][j]) )
			for ( j = 1; j <= n-1; ++j )
				printf("%d ",b[i][j]);
	}
	return 0;
}

