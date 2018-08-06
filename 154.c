/*
 * 154. Factorial
 * TOPIC: binary search
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long i64;

i64 f( i64 n ) {
	i64 sum = 0, p = 5;
	for ( sum += n/p; p <= n/5; p *= 5, sum += n/p ) ;
	return sum;
}

int main() {
	int i,j,k,q;
	i64 low, high, mid;
	for ( ;1 == scanf("%d",&q); ) {
		if ( q == 0 ) {
			puts("1");
			continue ;
		}
		assert( q >= 1 );
		for ( low = 0, high = (1LL<<60); low+1 < high; f(mid = (low+high)>>1) < q ? (low = mid):(high = mid) ) ;
		if ( f(high) == q )
			printf("%lld\n",high);
		else puts("No solution");
	}
	return 0;
}

