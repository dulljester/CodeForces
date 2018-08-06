/*
 * 146. the Runner
 * TOPIC: ad hoc, modulo
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (20100)
typedef long long i64;

i64 min( i64 x, i64 y ) { return x < y ? x:y; }

i64 t[N],v[N],L,s;
int n;

int main() {
	int i,j,k;
	double ll;
	for ( ;2 == scanf("%lf %d",&ll,&n); ) {
		L = (i64)(10000*(ll+1e-9));
		for ( s = 0, i = 0; i < n; ++i )
			scanf("%lld %lld",t+i,v+i), t[i] *= 10000, s += (t[i]*v[i])%L;
		s %= L;
		printf("%.4lf\n",min(s,L-s)/10000.00+1e-9);
	}
	return 0;
}

