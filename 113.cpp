/*
 * 113. Nearly Prime Numbers
 * TOPIC: primes, precalc
 * status: Accepted
 */
#include <cassert>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unordered_map>
#define tol (1e-13)
using namespace std;
#define N (1<<19)
typedef long long i64;

int n,c[0x10],len;
bool prime[N],ans[0x10];
i64 *p;
unordered_map<i64,bool> s;

bool is_prime( i64 x ) {
	if ( x < N ) return prime[x];
	if ( s.find(x) != s.end() )
		return s[x];
	for ( int i = 0; i < len && p[i]*p[i] <= x; ++i )
		if ( !(x%p[i]) )
			return s[x] = false ;
	return s[x] = true; 
}

int main() {
	int i,j,k,up;
	for ( prime[2] = true, i = 3; i < N; i += 2 )
		prime[i] = true ;
	for ( i = 3; i < N; i += 2 )
		for ( j = i+i; j < N && prime[i]; prime[j] = false, j += i ) ;
	for ( k = 0, i = 0; i < N; ++i )
		if ( prime[i] ) ++k;
	p = new i64[len = k];
	for ( i = 0, j = 0; i < N; ++i )
		if ( prime[i] )
			p[j++] = i;
	for ( ;1 == scanf("%d",&k); ) {
		for ( up = -1, i = 0; i < k; ++i ) {
			scanf("%d",&c[i]);
			if ( up < c[i] ) up = c[i];
		}
		memset(ans,0,sizeof ans);
		for ( j = 0; p[j]*p[j] <= up; ++j ) 
			for ( i = 0; i < k; ++i )
				if ( !ans[i] )
					if ( !(c[i]%p[j]) && is_prime(c[i]/p[j]) )
						ans[i] = true ;
		for ( i = 0; i < k; ++i )
			puts(ans[i]?"Yes":"No");
	}
	return 0;
}

