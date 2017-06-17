/*
 * D. Messenger
 * TOPIC: kmp
 * status: Accepted
 */
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N (200100)
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
using namespace std;
typedef long long i64;

int m,n,p[N];
i64 x[N],y[N],z[N];
pair<int,i64> t[N],a[N],b[N],c[N];

void compress( i64 *x, pair<int,i64> *res, int *n ) {
	i64 i,j,k = 0,l,m = 0;
	for ( i = 1; i <= *n; i = j ) {
		for ( j = i+1; j <= *n && (x[j]>>20) == (x[i]>>20); ++j ) ;
		for ( k = 0, l = i; l <= j-1; ++l ) k += (x[l]&MASK(20));
		t[++m] = make_pair(x[i]>>20,k);
	}
	for ( *n = m, i = 1; i <= m; res[i] = t[i], ++i ) ;
}

int main() {
	int i,j,k,left,right;
	i64 ans;
	char tmp[0x10],tmp2[0x10],tmpp[0x2];
	for ( ;2 == scanf("%d %d",&n,&m); ) {
		for ( i = 1; i <= n; ++i ) {
			scanf("%[^-]-%[a-z]",tmp,tmp2), y[i] = atoi(tmp)|((0[tmp2]-'a')<<20);
			//printf("%s %s, %d\n",tmp,tmp2,atoi(tmp));
		}
		for ( i = 1; i <= m; ++i )
			scanf("%[^-]-%[a-z]",tmp,tmp2), x[i] = atoi(tmp)|((0[tmp2]-'a')<<20);
		compress(x,a,&m), compress(y,b,&n);

		if ( m == 1 ) {
			for ( ans = 0, i = 1; i <= n; ++i )
				if ( (a[1].second) <= (b[i].second) && (a[1].first) == (b[i].first) ) 
					ans += (b[i].second)+1-(a[1].second);
			printf("%I64d\n",ans);
			continue ;
		}
		if ( m == 2 ) {
			for ( ans = 0, i = 1; i <= n-1; ++i )
				if ( a[1].first == b[i].first && a[1].second <= b[i].second )
					if ( a[2].first == b[i+1].first && a[2].second <= b[i+1].second )
						++ans;
			printf("%I64d\n",ans);
			continue ;
		}

		for ( j = 1, i = 2; i <= m-1; c[j++] = a[i++] ) ;
		for ( p[0] = j = -1, i = 1; i <= m-2; p[i++] = ++j )
			for ( ;j+1 && !(c[j+1].first == c[i].first && c[j+1].second == c[i].second); j = p[j] ) ;
		for ( ans = 0, k = 0, i = 1; i <= n; ++i ) {
			for ( ;k+1 && !(c[k+1].first == b[i].first && c[k+1].second == b[i].second); k = p[k] ) ;
			if ( ++k == m-2 ) {
				left = (i-(m-2)+1), right = i;
				if ( left >= 2 && (b[left-1].second) >= (a[1].second) && (b[left-1].first) == (a[1].first) )
					if ( right+1 <= n && (b[right+1].second) >= (a[m].second) && (b[right+1].first) == (a[m].first) )
						++ans;
				k = p[k];
			}
		}
		printf("%I64d\n",ans);
	}
	return 0;
}

