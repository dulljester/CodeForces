/*
 * 123. The Sum
 * TOPIC: matrix expo
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 3
typedef long long i64;

i64 A[N][N] = {{1,1,1},{0,1,1},{0,1,0}},ax[N][N],t[N][N],x[N][N];

int main() {
	int i,j,k,n;
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 0; i < N; ++i )
			for ( j = 0; j < N; ++j )
				ax[i][j] = (i==j?1:0), x[i][j] = A[i][j];
		if ( n == 1 ) {
			puts("1");
			continue ;
		}
		if ( n == 2 ) {
			puts("2");
			continue ;
		}
		for ( n -= 2; n; n >>= 1 ) {
			if ( n & 1 ) {
				for ( i = 0; i < N; ++i )
					for ( j = 0; j < N; ++j )
						for ( t[i][j] = 0, k = 0; k < N; ++k )
							t[i][j] += ax[i][k]*x[k][j];
				for ( i = 0; i < N; ++i )
					for ( j = 0; j < N; ++j )
						ax[i][j] = t[i][j];
			}
			for ( i = 0; i < N; ++i )
				for ( j = 0; j < N; ++j )
					for ( t[i][j] = 0, k = 0; k < N; ++k )
						t[i][j] += x[i][k]*x[k][j];
			for ( i = 0; i < N; ++i )
				for ( j = 0; j < N; ++j )
					x[i][j] = t[i][j];
		}
		printf("%lld\n",2*ax[0][0]+ax[0][1]+ax[0][2]);
	}
	return 0;
}

