/*
 * 170. Particles
 * TOPIC: greedy
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (5005)
typedef long long i64;

int x[2][N],n,c[2],m[2];
char s[2][N];

int main() {
	int i,j,k,t,l;
	i64 ans;
	for ( ;2 == scanf("%s %s",s[0],s[1]); ) {
		for ( t = 0; t <= 1; ++t )
			for ( m[t] = c[t] = 0, i = 0; s[t][i]; ++m[t], ++i )
				if ( s[t][i] == '+' )
					x[t][c[t]++] = i;
		if ( c[0] != c[1] || m[0] != m[1] ) {
			puts("-1");
			continue ;
		}
		for ( ans = 0, i = 0; i < c[0]; ++i )
			ans += (i64)abs(x[0][i]-x[1][i]);
		printf("%lld\n",ans);
	}
	return 0;
}

