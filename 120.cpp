/*
 * 120. Archipelago
 * TOPIC: comp. geometry, vector rotations, angles
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
#define tol (1e-9)
using namespace std;
typedef unsigned long long u64;
typedef long long i64;
#define x first
#define y second
typedef pair<long double,long double> cell;
#define N (0x200)
#define pi (2*acosl(0.00))

cell operator - ( const cell &a, const cell &b ) {
	return make_pair(a.x-b.x,a.y-b.y);
}

cell operator + ( const cell &a, const cell &b ) {
	return make_pair(a.x+b.x,a.y+b.y);
}

cell operator * ( const cell &a, const long double t ) {
	return make_pair(a.x*t,a.y*t);
}

long double operator , ( const cell &a, const cell &b ) {
	return a.x*b.x + a.y*b.y;
}

long double operator ^ ( const cell &a, const cell &b ) {
	return a.x*b.y - a.y*b.x;
}

cell operator ^ ( const cell &a, long double t ) {
	long double c = cosl(t), s = sinl(t);
	return make_pair(a.x*c - a.y*s, a.x*s + a.y*c);
}

cell c[N];

int main() {
	int i,j,k,ts,cs = 0,n1,n2,n,r;
	long double len,alpha,angle;
	cell h,mid,origin;
	for ( ;3 == scanf("%d %d %d",&n,&n1,&n2); ) {
		--n1, --n2;
		scanf("%Lf %Lf",&c[n1].x,&c[n1].y), scanf("%Lf %Lf",&c[n2].x,&c[n2].y);
		if ( n1 > n2 ) swap(n1,n2);
		angle = 2*pi/n;
		mid = (c[n1]+c[n2])*0.5;
		alpha = angle*(n2-n1);
		if ( alpha < pi ) {
			h = ((c[n1]-mid)^(pi/2))+mid;
			len = sqrt((c[n1]-mid,c[n1]-mid));
			len = len/tan(alpha/2);
			origin = mid+(((h-mid)*(1/sqrt((h-mid,h-mid))))*len);
		}
		else if ( fabs(alpha-pi) < tol ) {
			origin = mid;
		}
		else {
			alpha = 2*pi-alpha;
			h = ((c[n2]-mid)^(pi/2))+mid;
			len = sqrt((c[n2]-mid,c[n2]-mid));
			len = len/tan(alpha/2);
			origin = mid+(((h-mid)*(1/sqrt((h-mid,h-mid))))*len);
		}
		for ( i = n1+1; i <= n2-1; ++i ) 
			c[i]=origin+((c[i-1]-origin)^(-angle));
		for ( i = n2+1; i <= n-1; ++i )
			c[i]=origin+((c[i-1]-origin)^(-angle));
		for ( i = 0; i <= n1-1; ++i )
			c[i]=origin+((c[(i-1+n)%n]-origin)^(-angle));
		for ( i = 0; i < n; ++i )
			printf("%.6Lf %.6Lf\n",c[i].x,c[i].y);
	}
	return 0;
}

