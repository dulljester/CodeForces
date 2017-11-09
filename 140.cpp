/*
 * 140. Integer Sequence
 * TOPIC: linear Diophantine Equations, general case, number theory, recursion, modular inverse
 * status: Accepted
 */
#include <cassert>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define tol (1e-13)
#define N (0x80)
using namespace std;
typedef unsigned long long u64;
typedef long long i64;

i64 P,B;

i64 gcd( i64 x, i64 y ) { return !y?x:gcd(y,x%y); }

void ext_euclid( i64 x, i64 y, i64 *a, i64 *b, i64 *d ) {
	if ( !y )
		*a = 1, *b = 0, *d = x;
	else
		ext_euclid(y,x%y,b,a,d), *b -= (*a)*(x/y);
}

i64 inv( i64 x, i64 MOD ) {
	i64 a,b,d;
	for ( ext_euclid(x,MOD,&a,&b,&d); a < 0; a += MOD ) ;
	return a % MOD;
}

bool solve( i64 *a, int n, vector<i64> &x ) {
	i64 d;
	x.clear();
	if ( n == 1 ) {

		if ( a[0] == 0 ) {
			if ( B == 0 ) {
				x.push_back(0);
				return true ;
			}
			return false ;
		}

		assert( a[0] >= 1 );

		d = gcd(a[0],P);
		assert( d >= 1 );
		if ( d == 1 ) {
			x.push_back((B*inv(a[0],P))%P);
			return true ;
		}
		i64 rhs = (B*inv(a[0],P))%P;
		if ( rhs%d ) return false ;
		x.push_back(rhs/d);
		return true ;
	}
	assert( n >= 2 );
	if ( a[n-1] == 0 ) {
		vector<i64> xx;
		if ( !solve(a,n-1,xx) ) return false ;
		for ( int l = 0; l < (int)xx.size(); ++l )
			x.push_back(xx[l]);
		x.push_back(0);
		return true ;
	}
	i64 *tmp = new i64[n];
	for ( int l = 0; l < n; ++l ) tmp[l] = a[l];
	for ( int l = 1; l < n; ++l )
		a[l] = tmp[l-1]%tmp[n-1];
	a[0] = tmp[n-1];
	vector<i64> xx;
	if ( !solve(a,n,xx) ) {
		delete tmp;
		return false ;
	}
	for ( int l = 0; l < n; ++l ) a[l] = tmp[l];
	delete tmp;
	for ( int l = 0; l < n-1; ++l )
		x.push_back(xx[l+1]);
	i64 last_x = xx[0];
	for ( int l = 1; l < n; ++l )
		last_x -= (a[l-1]/a[n-1]*xx[l])%P, last_x += P, last_x %= P;
	x.push_back(last_x);
	return true ;
}

i64 a[N];
int n;

int main() {
	int i,j,k,ts,cs = 0;
	for ( ;3 == scanf("%d %lld %lld",&n,&P,&B); ) {
		for ( B %= P, i = 0; i < n; ++i )
			scanf("%lld",a+i), a[i] %= P;
		vector<i64> x;
		if ( !solve(a,n,x) ) {
			puts("NO");
			continue ;
		}
		for ( puts("YES"), i = 0; i < n-1; ++i )
			printf("%lld ",x[i]);
		printf("%lld\n",x[i]);
	}
	return 0;
}

