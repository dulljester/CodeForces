/*
 * 127. Telephone Directory
 * TOPIC: sorting, greedy, simulation
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
#include <set>
#include <map>
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define tol (1e-13)
using namespace std;
typedef unsigned long long u64;
typedef long long i64;
#define N (8010)

int m,n,x[N];
char s[N][5];

int main() {
	int i,j,k,ts,cs = 0,ans;
	for ( ;2 == scanf("%d %d",&m,&n); printf("%d\n",ans+2) ) {
		for ( i = 0; i < n; scanf("%d",&x[i++]) ) ;
		for ( sort(x,x+n), i = 0; i < n; ++i )
			sprintf(s[i],"%d",x[i]);
		for ( ans = 0, i = 0; i < n; ++ans, i = j ) 
			for ( k = 1, j = i+1; j < n && s[i][0] == s[j][0] && k < m; ++j, ++k ) ;
	}
	return 0;
}

