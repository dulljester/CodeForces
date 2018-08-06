/*
 * 114. Telecasting Station
 * TOPIC: greedy, median
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
#define N (1<<15)

pair<double,int> p[N];
int n,total;
double x0;

double getRank( int r ) {
	int i,j,k = -1;
	for ( i = 0; i < n; ++i ) {
		assert( k < r );
		if ( k+p[i].second < r ) {
			k += p[i].second;
			continue ;
		}
		return p[i].first;
	}
}

int main() {
	int i,j,k,ts,cs = 0;
	for ( ;1 == scanf("%d",&n); ) {
		for ( total = 0, i = 0; i < n; ++i ) {
			scanf("%lf %d",&p[i].first,&p[i].second);
			total += p[i].second;
		}
		sort(p,p+n);
		if ( total&1 ) {
			double a = getRank(total/2);
			printf("%.5lf\n",a);
		}
		else {
			double a = getRank(total/2), b = getRank(total/2-1);
			printf("%.5lf\n",(a+b)/2);
		}
	}
	return 0;
}

