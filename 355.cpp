/*
 * 355. Numbers Painting
 * TOPIC: greedy, binary search, topological sorting
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
#define N (1<<16)
using namespace std;

set<int> s[N];
int n,color[N],c[N],*head,*tail,q[N],vec[N],m;

void decide_color( int x ) {
	m = 0;
	for ( set<int> :: iterator it = s[x].begin(); it != s[x].end(); vec[++m] = *it++ ) ;
	int low, high, mid;
	if ( vec[1] > 1 ) {
		color[x] = 1;
		return ;
	}
	if ( vec[m] == m ) {
		color[x] = m+1;
		return ;
	}
	assert( vec[m] > m );
	for ( low = 1, high = m; low+1 < high; vec[mid = (low+high)>>1] <= low ? (low = mid):(high = mid) ) ;
	assert( vec[low] == low );
	assert( vec[high] > high );
	color[x] = high+1;
}

int main() {
	int i,j,k,x,y,ans;
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 1; i <= n; c[i] = 0, s[i++].clear() );
		for ( i = 1; i <= n; ++i )
			for ( j = i+i; j <= n; ++c[j], j += i ) ;
		for ( color[1] = 1, head = tail = q, *tail++ = 1; head < tail; )
			for ( x = *head++, y = x+x; y <= n; y += x ) {
				s[y].insert(color[x]);
				if ( !--c[y] ) 
					decide_color(y), *tail++ = y;
			}
		for ( ans = 0, i = 1; i <= n; ++i )
			ans = max(ans,color[i]);
		printf("%d\n",ans);
		for ( x = 1; x <= n-1; ++x )
			printf("%d ",color[x]);
		printf("%d\n",color[x]);
	}
	return 0;
}

