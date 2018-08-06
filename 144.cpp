/*
 * 144. Meeting
 * TOPIC: probability, basic, esy, good for interview
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

double a,b,H,L;

int main() {
	int i,j,k,ts,cs = 0;
	for ( ;3 == scanf("%lf %lf %lf",&a,&b,&H); ) {
		L = (b-a)*60;
		printf("%.7lf\n",(2*L*H-H*H)/L/L);
	}
	return 0;
}

