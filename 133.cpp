/*
 * 133. Border
 * TOPIC: event-driven simulation, sorting, binary heap
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
#include <queue>
#define N (1<<15)
#define oo ((int)((1LL<<31)-1LL))
using namespace std;
#define bubble (swap(pos[heap[i]],pos[heap[j]]),swap(heap[i],heap[j]))

int n,x[2][N],heap[N<<1],_cnt,pos[N];

void push( int entry ) {
	int i,j;
	if ( pos[entry] < 0 )
		pos[heap[_cnt] = entry] = _cnt, ++_cnt;
	for ( j = pos[entry]; j && x[0][heap[i = (j-1)>>1]] > x[0][heap[j]]; bubble, j = i ) ;
}

int pop() {
	int entry = *heap, i,j;
	if ( _cnt += (pos[entry] = -1) ) 
		pos[*heap = heap[_cnt]] = 0;
	for ( j = 0; (i=j,j<<=1,++j) < _cnt; bubble ) {
		if ( j < _cnt-1 && x[0][heap[j]] > x[0][heap[j+1]] ) ++j;
		if ( x[0][heap[i]] <= x[0][heap[j]] ) break ;
	}
	return entry;
}

int peek() { return *heap; }

struct event {
	int idx;
	char type;
	bool operator < ( const event &rhs ) const {
		if ( x[type][idx] == x[rhs.type][rhs.idx] ) {
			return type == 1;
		}
		return x[type][idx] < x[rhs.type][rhs.idx];
	}
	event( int i, int t ) {
		idx = i, type = t;
	}
};

struct comp {
	bool operator () ( const event &a, const event &b ) {
		return b < a;
	}
};

priority_queue<event,vector<event>,comp> pq;

int main() {
	int i,j,k;
	for ( ;1 == scanf("%d",&n); ) {
		for ( _cnt = 0, i = 0; i < n; ++i ) {
			scanf("%d %d",&x[0][i],&x[1][i]);
			pq.push(event(i,0)), pos[i] = -1;
		}
		for ( k = 0; !pq.empty(); ) {
			event e = pq.top(); pq.pop();
			if ( e.type == 0 ) {
				pq.push(event(e.idx,1));
				push(e.idx);
				continue ;
			}
			j = x[0][e.idx], x[0][e.idx] = -oo, push(e.idx), pop();
			if ( _cnt && x[0][peek()] < j ) 
				++k;
		}
		printf("%d\n",k);
		break ;
	}
	return 0;
}

