/*
 * 163. Wise King
 * TOPIC: greedy, sorting, super-easy
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
#define tol (1e-13)
using namespace std;

struct comp01 {
	bool operator () ( const int &a, const int &b ) {
		return a > b;
	}
};

struct comp02 {
	bool operator () ( const int &a, const int &b ) {
		return abs(a) > abs(b);
	}
};

struct comp03 {
	bool operator () ( const int &a, const int &b ) {
		return a > b;
	}
};

int n,c[0x80],m;

int main() {
	int i,j,k,ans;
	for ( ;2 == scanf("%d %d",&n,&m); ) {
		for ( i = 0; i < n; ++i )
			scanf("%d",c+i);
		if ( m == 1 || m == 3 ) sort(c,c+n,comp01());
		else if ( m == 2 ) sort(c,c+n,comp02());
		if ( m == 2 ) {
			for ( ans = 0, i = 0; i < n; ++i )
				ans += c[i]*c[i];
		}
		else {
			for ( ans = 0, i = 0; i < n && c[i] > 0; ++i )
				ans += (m==3?c[i]*c[i]*c[i]:c[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}

