/*
 * 199. Beautiful People
 * TOPIC: LIS, one of the best, batch LIS, tricky
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
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define L(k) ((k)&((~(k))+1ULL))
#define tol (1e-13)
using namespace std;
typedef unsigned long long u64;
typedef long long i64;
#define N (1<<17)
#define value(x) ((x).second.first)

pair<int,pair<int,int> > x[N];
int n,len,a[N],p[N],largest[N],start[N];
bool is_border[N];

bool equal( int i, int j ) {
	//assert( i < j );
	return x[i].first == x[j].first || x[i].first < x[j].first && value(x[i]) == value(x[j]);
}

bool is_less( int i, int j ) {
	//assert( i < j );
	return x[i].first < x[j].first && value(x[i]) < value(x[j]);
}

bool is_greater( int i, int j ) {
	//assert( i < j );
	return x[i].first < x[j].first && value(x[i]) > value(x[j]);
}

void dump( int k ) {
	if ( k >= 0 ) {
		dump(p[k]);
		printf("%d ",x[k].second.second);
	}
}

struct comp {
	bool operator () ( const pair<int,pair<int,int> > &a, const pair<int,pair<int,int> > &b ) {
		if ( a.first == b.first ) {
			if ( a.second.first == b.second.first ) 
				return a.second.second < b.second.second;
			return a.second.first < b.second.first;
		}
		return a.first < b.first;
	}
};

int pred[N];

void update_map( unordered_map<int,int> &m, int place, int i, int prev ) {
	if ( m.find(place) == m.end() ) 
		m[place] = i, pred[i] = prev;
}

int main() {
	int i,j,k,ts,cs = 0,low,high,mid;
	vector<pair<int,int> > blocks;
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 0; i < n; ++i )
			scanf("%d %d",&x[i].first,&x[i].second.first), x[i].second.second = (i+1);
		for ( blocks.clear(), sort(x,x+n,comp()), i = 0; i < n; i = j ) {
			for ( j = i; j < n && x[i].first == x[j].first; ++j ) ;
			for ( k = i; k < j; start[k] = i, ++k )
				largest[k] = value(x[j-1]);
			is_border[j-1] = true;
			blocks.push_back(make_pair(i,j-1));
		}
		len = 0;
		for ( int block = 0; block < (int)blocks.size(); ++block ) {
				unordered_map<int,int> mp;
				for ( mp.clear(), i = blocks[block].first; i <= blocks[block].second; ++i ) {
					if ( !len || is_less(a[len-1],i) ) {
						//p[i] = !len?-1:a[len-1];
						//a[len++] = i;
						update_map(mp,len,i,len==0?-1:a[len-1]);
						continue ;
					}
					assert( equal(a[len-1],i) || is_greater(a[len-1],i) ); // <=
					if ( is_greater(a[0],i) || equal(a[0],i) ) {
						//if ( is_greater(a[0],i) && (largest[i] <= value(x[a[0]])) )
						//	a[0] = i, p[i] = -1;
						if ( is_greater(a[0],i) )
							update_map(mp,0,i,-1);
						continue ;
					}
					assert( is_less(a[0],i) ); // <
					// x[a[low]] < x[i] <= x[a[high]]
					for ( low = 0, high = len-1; low+1 < high; ) {
						mid = (low+high)>>1;
						if ( is_less(a[mid],i) )
							low = mid;
						else high = mid;
					}
					if ( is_greater(a[high],i) )
						//p[i] = a[low], a[high] = i;
						update_map(mp,high,i,a[low]);
				}
				for ( unordered_map<int,int> :: iterator it = mp.begin(); it != mp.end(); ++it ) {
					i = it->second, j = it->first;
					a[j] = i, p[i] = pred[i];
					if ( j == len ) ++len;
				}
		}
		printf("%d\n",len), dump(a[len-1]), putchar('\n');
	}
	return 0;
}

