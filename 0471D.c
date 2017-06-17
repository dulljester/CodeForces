/*
 * D. MUH and Cube Walls
 * TOPIC: kmp
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (2*100000+7)

int p[N],x[N],y[N],m,n;

int main() {
	int i,j,k,ans;
	while ( 2 == scanf("%d %d",&n,&m) ) {
		for ( scanf("%d",&k), i = 1; i <= n-1; ++i )
			scanf("%d",&j), y[i] = j-k, k = j;
		for ( scanf("%d",&k), i = 1; i <= m-1; ++i )
			scanf("%d",&j), x[i] = j-k, k = j;
		if ( m == 1 ) {
			printf("%d\n",n);
			continue ;
		}
		for ( --m, --n, p[0] = j = -1, i = 1; i <= m; p[i++] = ++j )
			for ( ;j+1 && x[j+1] != x[i]; j = p[j] ) ;
		for ( ans = 0, j = 0, i = 1; i <= n; ++i ) {
			for ( ;j+1 && x[j+1] != y[i]; j = p[j] ) ;
			if ( ++j == m ) 
				++ans, j = p[j];
		}
		printf("%d\n",ans);
	}
	return 0;
}

