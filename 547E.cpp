/*
 * E. Mike and Friends
 * TOPIC: suffix automata, DP, binary search
 * status: MLE on test 9
 */
#include <algorithm>
#include <map>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <queue>
#define T 0
#define L(k) ((k) & ((~(k))+1))
#define BIT(k) (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define SET(u,k) ((u)|=BIT(k))
#define TST(x,k) ((x) && (x)->son.find(ch) != (x)->son.end())
#define N (2*100001+7)
#define Q (2*N)
#define is_primary(x,ch) ((x)->len+1==(x)->son[ch]->len)
#define A 26
#define LIMIT (BIT(63))
//typedef unsigned long long u64;
typedef int u64;
using namespace std;

typedef struct cell {
	map<int,cell *> son;
	map<int,int> freq;
	cell *slink;
	cell() {};
	int len,count;
} cell;

cell *ptr,pool[Q],*sink,*root,*word[N],*q[Q],**head,**tail;
int delimiter,n,len[N],mm[N];
pair<int,u64> *vec[N];
bool is[Q];

cell *init( int len ) {
	cell *x = ptr++;
	x->count=0, x->len=len, x->son.clear(), x->freq.clear(), x->slink=NULL;
	return x;
}

void add_son( cell *x, int ch, cell *y ) { x->son[ch] = y; }

cell *split( cell *x, int ch ) {
	cell *z = init(x->len+1), *y = x->son[ch];
	for ( map<char,cell *> :: iterator it=y->son.begin(); it!=y->son.end(); ++it )
		z->son[it->first] = it->second;
	for ( add_son(x,ch,z); (x=x->slink) && TST(x,ch) && x->son[ch]==y; add_son(x,ch,z) ) ;
	z->slink = y->slink, y->slink = z, ++z->count;
	return z;
}

cell *update( int ch, int idx ) {
	cell *new_sink = init(sink->len+1), *x;
	for ( add_son(x=sink,ch,new_sink); (x=x->slink) && !TST(x,ch); add_son(x,ch,new_sink) ) ;
	new_sink->slink=(!x?root:is_primary(x,ch)?x->son[ch]:split(x,ch));
	++new_sink->slink->count, new_sink->freq[idx] = 1;
	return new_sink;
}

//queue<cell *> q;

/* largest index "i": such that vec[i].first <= x && vec[i+1].first > x
 */
int f( pair<int,u64> *vec, int m, int x ) {
	int i,j,k, low, high, mid;
	if ( vec[m-1].first <= x ) return m-1;
	if ( vec[0].first > x ) return -1;
	assert( vec[low = 0].first <= x && vec[high = m-1].first > x );
	for ( ;low+1 < high; vec[mid=(low+high)/2].first>x?(high=mid):(low=mid) );
	assert( vec[low].first <= x && vec[high].first > x );
	return low;
}

int main() {
	int i,j,k,qr,ch,l,r,left,right;
	cell *x,*y;
	for ( ;2 == scanf("%d %d\n",&n,&qr); ) {
		ptr = pool, root = sink = init(0);
		for ( delimiter = A, i = 1; i <= n; ++i ) {
			for ( ;(ch = getchar()) != EOF && ch != '\n' && !('a' <= ch && ch <= 'z'); ) ;
			assert( ch!=EOF && ch!='\n' ) ;
			sink = update(delimiter++,i);
			for ( k=1, sink=update(ch-'a',i); (ch=getchar())!=EOF && ('a'<=ch&&ch<='z'); sink=update(ch-'a',i), ++k ) ;
			word[i] = sink, len[i] = k;
		}
		assert( delimiter == A+n );
		head = tail = q;
		for ( x = pool+1; x < ptr; ++x )
			if ( !x->count ) *tail++ = x;
		/*
		for ( ;!q.empty(); q.pop() )
			if ( y=(x=q.front())->slink ) {
				for ( map<int,int>::iterator it=x->freq.begin(); it!=x->freq.end(); ++it )
					if ( y->freq.find(it->first) == y->freq.end() )
						y->freq[it->first] = it->second;
					else y->freq[it->first] += it->second;
				if ( !--y->count ) q.push(y);
			}
			*/
		for ( ;head < tail; )
			if ( y=(x=*head++)->slink ) {
				for ( map<int,int>::iterator it=x->freq.begin(); it!=x->freq.end(); ++it )
					if ( y->freq.find(it->first) == y->freq.end() )
						y->freq[it->first] = it->second;
					else y->freq[it->first] += it->second;
				if ( !--y->count ) *tail++ = y;
			}

		for ( i = 1; i <= n; ++i ) {
			mm[i] = 0;
			if ( word[i]->len == len[i] || word[i]->slink->len == len[i] ) {
				if ( word[i]->len != len[i] )
					word[i] = word[i]->slink;
				is[word[i]-pool] = true;
			}
			else {
				assert( word[i]->len > len[i] );
			}
		}
		for ( x = pool; x < ptr; ++x )
			if ( !is[x-pool] ) x->freq.clear(), x->son.clear();
		for ( i = 1; i <= n; ++i ) {
			u64 sum  = 0;
#if !T
			mm[i] = word[i]->freq.size();
			vec[i] = new pair<int,int>[mm[i]];
			j = 0;
			for ( map<int,int> :: iterator it = word[i]->freq.begin(); it != word[i]->freq.end(); ++it ) {
				vec[i][j++] = make_pair(it->first,sum+it->second);
				assert( sum < LIMIT-it->second );
				sum += it->second;
			}
#endif
		}
		while ( qr-- && 3 == scanf("%d %d %d",&l,&r,&k) ) {
			--l;
#if !T
			assert( word[k] );
			if ( word[k]->len!=len[k] || !mm[k] ) {
				puts(l<k&&k<=r?"1":"0");
				continue ;
			}
#endif
#if T
			u64 ans = 0;
			for ( map<int,int> :: iterator it = word[k]->freq.begin(); it != word[k]->freq.end() && it->first <= r; ++it )
				if ( l < it->first && it->first <= r )
					ans += it->second;
			//printf("%I64d\n",ans);
			printf("%d\n",ans);
#else
			right = f(vec[k],mm[k],r), left = f(vec[k],mm[k],l);
			if ( right == -1 ) {
				puts(l<k&&k<=r?"1":"0");
				continue ;
			}
			//printf("%I64d\n",vec[k][right].second-(left==-1?0:vec[k][left].second));
			printf("%d\n",vec[k][right].second-(left==-1?0:vec[k][left].second));
#endif
		}
	}
	return 0;
}

