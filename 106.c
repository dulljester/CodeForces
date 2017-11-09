/*
 * 106. The Equation
 * TOPIC:  Diophantine Equation
 * status: Accepted
 */
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tol (1e-13)
typedef long long i64;

i64 gcd( i64 x, i64 y ) { return !y?x:gcd(y,x%y); }

void solve( i64 a, i64 b, i64 c, i64 *x0, i64 *y0 ) {
	if ( !b ) {
		assert( !(c%a) );
		*x0 = (c/a), *y0 = 0;
	}
	else {
		solve(b,a%b,c,y0,x0);
		*y0 -= (*x0)*(a/b);
	}
}

i64 max( i64 x, i64 y ) { return x < y ? y:x; }
i64 min( i64 x, i64 y ) { return x > y ? y:x; }

i64 F( i64 x, i64 y ) {
	i64 z = x/y;
	if ( !(x%y) ) return z;
	return (i64)(floor((x+0.00)/y)+tol);
}

i64 C( i64 x, i64 y ) {
	i64 z = x/y;
	if ( !(x%y) ) return z;
	return (i64)(ceil((x+0.00)/y));
}

int main() {
	int i,j,k;
	i64 a,b,c,x,y,d,X1,X2,Y1,Y2,x0,y0;
	/*printf("%lld %lld\n",F(-3,2),C(-3,2));*/
	for ( ;7 == scanf("%lld %lld %lld %lld %lld %lld %lld",&a,&b,&c,&X1,&X2,&Y1,&Y2); ) {
		if ( a == 0 && b == 0 ) {
			if ( c == 0 ) {
				printf("%lld\n",(X2-X1+1)*(Y2-Y1+1));
			}
			else {
				puts("0");
			}
			continue ;
		}
		if ( a == 0 ) {
			if ( c%b ) { 
				puts("0");
				continue ;
			}
			y0 = c/b;
			if ( Y1 <= y0 && y0 <= Y2 )
				printf("%lld\n",X2-X1+1);
			else puts("0");
			continue ;
		}
		if ( b == 0 ) {
			if ( c%a ) {
				puts("0");
				continue ;
			}
			x0 = c/a;
			if ( X1 <= x0 && x0 <= X2 )
				printf("%lld\n",Y2-Y1+1);
			else puts("0");
			continue ;
		}
		assert( a != 0 && b != 0 );
		d = gcd(a,b);
		if ( c%d ) {
			puts("0");
			continue ;
		}
		a /= d, b /= d, c /= d, c = -c;
		solve(a,b,c,&x0,&y0);
		/* x = x0-bt, y = y0+at */
		if ( a > 0 && b > 0 ) {
			printf("%lld\n",max(0LL,min(F(Y2-y0,a),F(x0-X1,b)) - max(C(Y1-y0,a),C(x0-X2,b)))+1);
		}
		else if ( a > 0 && b < 0 ) {
			printf("%lld\n",max(0LL,min(F(Y2-y0,a),F(x0-X2,b)) - max(C(Y1-y0,a),C(x0-X1,b)))+1);
		}
		else if ( a < 0 && b > 0 ) {
			printf("%lld\n",max(0LL,min(F(Y1-y0,a),F(x0-X1,b)) - max(C(Y2-y0,a),C(x0-X2,b)))+1);
		}
		else {
			printf("%lld\n",max(0LL,min(F(Y1-y0,a),F(x0-X2,b)) - max(C(Y2-y0,a),C(x0-X1,b)))+1);
		}
	}
	return 0;
}

