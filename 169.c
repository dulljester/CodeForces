/*
 * 169. Numbers
 * TOPIC: number theory, necessary condition
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int len;

int modulus( int n, int d ) {
	int i,j,k,rem,carry,tmp;
	for ( rem = 0, i = n-1; i >= 0; --i ) 
		rem = (10*rem+(i==0?0:1))%d;
	return rem;
}

int main() {
	int i,j,k,n,d,ans;
	for ( ;1 == scanf("%d",&n); ) {
		for ( ans = 1, d = 2; d <= 8; ++d ) 
			if ( modulus(n,d*(d+1)) == 0 ) ++ans;
		printf("%d\n",ans);
	}
	return 0;
}

