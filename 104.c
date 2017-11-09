/*
 * 104. Little Shop of Flowers
 * TOPIC: IOI, DP
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 0x80
#define oo (1<<29)

int m,n,a[N][N],z[N][N],place[N][N],*ptr,out[N];

int calc_z( int i, int j ) {
	int t;
	if ( i > j ) return z[i][j] = +oo;
	if ( z[i][j] < +oo )
		return z[i][j];
	assert( i >= 0 && j >= 0 );
	if ( !i ) return z[i][j] = 0;
	assert( i > 0 );
	for ( t = i-1; t <= j-1; ++t )
		if ( calc_z(i-1,t) < +oo && (z[i][j] == +oo || z[i][j] < z[i-1][t]+a[i][t+1]) )
			z[i][j] = z[i-1][t]+a[i][t+1], place[i][j] = t+1;
	return z[i][j];
}

void dump( int i, int j ) {
	int t;
	if ( i ) 
		t = place[i][j], dump(i-1,t-1), *ptr++ = t;
}

int main() {
	int i,j,k;
	for ( ;2 == scanf("%d %d",&m,&n); ) {
		for ( i = 1; i <= m; ++i )
			for ( j = 1; j <= n; scanf("%d",&a[i][j++]) ) ;
		for ( i = 0; i <= m; ++i )
			for ( j = 0; j <= n; z[i][j++] = +oo ) ;
		printf("%d\n",calc_z(m,n));
		for ( ptr = out, dump(m,n), i = 0; i < ptr-out-1; printf("%d ",out[i++]) ) ;
		printf("%d\n",out[i]);
	}
	return 0;
}

