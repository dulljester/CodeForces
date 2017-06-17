/*
 * C. Deletion of Repeats
 * TOPIC: repetition finding, Crochemore (1981), primitively rooted repeats
 * status: Accepted
 */
#include <map>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <memory>
#define MAXLOG (18)
#define N (100000+19)
#define BIT(k)  (1ULL<<(k))
#define MASK(k) (BIT(k)-1ULL)
#define MAXC (2*N)
#define SH (30)
using namespace std;
typedef long long i64;
enum { L, R };

typedef struct repetition {
	int i,p,e;
	repetition( int i, int p, int e ) {
		this->i = i, this->p = p, this->e = e;
	};
	repetition() {};
} repetition;

typedef struct cell {
	struct cell *next,*prev;
	int val;
} cell;

cell *init_cell( int val ) {
	cell *x = (cell *)malloc(sizeof *x);
	assert( x );
	x->val = val, x->prev = x->next = NULL;
	assert( x->val == val );
	return x;
}

void add_after( cell **item, cell *x ) {
	x->prev = x->next = NULL;
	if ( !(*item) )
		(*item) = x;
	else {
		if ( x->next = (*item)->next )
			x->next->prev = x;
		x->prev = *item, (*item)->next = x;
	}
}

typedef struct list {
	cell *head,*tail;
	int count;
	bool is_empty() {
		return !count;
	};
} list;

void remove( list *q, cell *x ) {
	cell *prev,*next;
	if ( !q || !x ) return ;
	assert( q->count );
	if ( q->head->val == x->val ) {
		if ( q->head = q->head->next )
			q->head->prev = NULL;
	}
	else if ( q->tail->val == x->val ) {
		if ( q->tail = q->tail->prev )
			q->tail->next = NULL;
	}
	else {
		prev = x->prev, next = x->next;
		if ( prev )
			prev->next = next;
		if ( next )
			next->prev = prev;
	}
	if ( !--q->count )
		q->head = q->tail = NULL;
	x->prev = x->next = NULL;
}

cell *poll_first( list *q ) {
	if ( q->is_empty() )
		return NULL;
	cell *x = q->head;
	int k = q->count;
	remove(q,x);
	assert( q->count == k-1 );
	return x;
}

list *init_list() {
	list *lst = (list *)malloc(sizeof *lst);
	lst->head = lst->tail = NULL, lst->count = 0;
	return lst;
}

cell *add_last( list *q, cell *x ) {
	assert( q );
	add_after(&(q->tail),x);
	if ( !q->count++ ) 
		q->head = q->tail;
	else 
		q->tail = q->tail->next;
	assert( q->tail );
	return x;
}

int poll( list *q ) {
	assert( q->count ) ;
	int res = q->head->val;
	remove(q,q->head);
	return res;
}

int m,n,E[N],D[N],last_index[MAXC],newindex[MAXC],*top,s[N],oo,period,
	SMALL[MAXC],*s_top,
	was_split[MAXC],yes,
	SPLIT[MAXC],*split;
list *ECLASS[MAXC],*DCLASS[N],*SUBCLASS[MAXC];
cell *pe[N],*pd[N];
map<int,int> seen_before;
repetition e[N*MAXLOG];
i64 q[MAXC],*head,*tail;

void initialize() {
	int i,j,k;
	cell *x;
	for ( m = 0, top = newindex, k = 2*n; k >= 1; ECLASS[*++top = k] = init_list(), SUBCLASS[k--] = init_list() ) ;
	for ( i = 1; i <= n; DCLASS[i++] = init_list() ) ;
	oo = (n+7), DCLASS[+oo] = init_list();
	for ( s_top = SMALL, seen_before.clear(), i = 1; i <= n; ++i ) {
		if ( !seen_before.count(s[i]) ) 
			pe[i] = add_last(ECLASS[E[seen_before[s[i]]=i]=(*++s_top=k=*top--)],init_cell(i));
		else 
			pe[i] = add_last(ECLASS[E[i]=E[seen_before[s[i]]]],init_cell(i));
		if ( x = pe[i]->prev ) {
			j = x->val;
			remove(DCLASS[D[j]],pd[j]), pd[j] = NULL;
			D[j] = i-j, pd[j] = add_last(DCLASS[D[j]],!pd[j]?init_cell(j):pd[j]);
		}
		pd[i] = add_last(DCLASS[D[i] = +oo],init_cell(i));
	}
}

void rep() {
	int i,j,k,t,cnt,klass,ni,ii,largest_class_id,largest_size,
		exponent;
	i64 u,v;
	cell *x,*y;

	for ( initialize(), period = 1; s_top > SMALL; ) {
		for ( ;!DCLASS[period]->is_empty(); ) {
			i = DCLASS[period]->head->val;
			assert( D[i] == period ) ;
			while ( D[i+=period]==period ) ;
			for ( exponent = 1; !(i-period<=0 || D[i-period]!=period); i -= period, ++exponent ) ;
			if ( exponent >= 2 && !(i>=2 && s[i-1] == s[i+period-1]) )
				e[m].i = i, e[m].p = period, e[m++].e = exponent, ++k;
			for ( remove(DCLASS[period],pd[i]), pd[i] = NULL; (i+=period) <= n && D[i] == period; remove(DCLASS[period],pd[i]), pd[i] = NULL ) ;
		//	printf("i = %d, e = %d\n",i,exponent);
		}
		if ( ++period > n/2 ) break ;
		for ( split = SPLIT, ++yes, head=tail=q; s_top>SMALL; ) 
			for ( x=ECLASS[t=*s_top--]->head; x; x=x->next ) {
				if ( (j = x->val) == 1 ) continue ;
				k=E[i=j-1];
				if ( was_split[k] != yes ) 
					was_split[k] = yes, last_index[k] = -1, add_last(SUBCLASS[k],init_cell(k)), *++split = k;
				*tail++ = (j|(((i64)t)<<SH));
			}
		for ( ;head<tail; ) {
			u=*head++, j=(u&MASK(SH)), t=(u>>SH);
			assert( j >= 2 );
			k = E[i=j-1];
			if ( last_index[k] != t ) {
				assert( top > newindex );
				assert( SUBCLASS[k] );
				last_index[k] = t, add_last(SUBCLASS[k],init_cell(ni = *top--));
			}
			assert( SUBCLASS[k] && !SUBCLASS[k]->is_empty() );
			klass = SUBCLASS[k]->tail->val;
			if ( pe[i]->prev ) {
				ii = pe[i]->prev->val;
				remove(DCLASS[D[ii]],pd[ii]), D[ii] = (D[i]<+oo?D[ii]+D[i]:+oo) , pd[ii] = add_last(DCLASS[D[ii]],!pd[ii]?init_cell(ii):pd[ii]);
			}
			remove(DCLASS[D[i]],pd[i]), pd[i] = add_last(DCLASS[D[i] = +oo],!pd[i]?init_cell(i):pd[i]);
			remove(ECLASS[E[i]],pe[i]), pe[i] = add_last(ECLASS[E[i] = klass],pe[i]);
			assert( pe[i] );
			if ( pe[i]->prev ) {
				ii = pe[i]->prev->val;
				remove(DCLASS[D[ii]],pd[ii]), D[ii] = i-ii,	pd[ii] = add_last(DCLASS[D[ii]],!pd[ii]?init_cell(ii):pd[ii]);
			}
		}
		assert( s_top == SMALL );
		for ( ;split > SPLIT; ) {
			k = *split--, largest_class_id = -1, largest_size = -1;
			if ( ECLASS[k]->is_empty() ) {
				*++top = k;
				assert( x = poll_first(SUBCLASS[k]) );
				assert( x->val == k );
			}
			assert( SUBCLASS[k]->is_empty() || SUBCLASS[k]->head );
			for ( x = SUBCLASS[k]->head; x; x = x->next )
				if ( ECLASS[x->val]->count > largest_size )
					largest_size = ECLASS[largest_class_id = x->val]->count;
			assert( largest_class_id != -1 || SUBCLASS[k]->is_empty() );
			for ( ;!SUBCLASS[k]->is_empty(); )
				if ( (x = poll_first(SUBCLASS[k])) && x->val != largest_class_id )
					*++s_top = x->val;
		}
	}
}

int main() {
	int i,j,k,left,l,r;
	for ( ;1 == scanf("%d",&n); ) {
		for ( i = 1; i <= n; scanf("%d",&s[i++]) ) ;
		for ( rep(), left = 1, i = 0; i < m; ++i ) {
			j = e[i].i+e[i].p*(e[i].e-1);
			if ( left < j ) left = j;
		}
		printf("%d\n",n-left+1);
		for ( i = left; i <= n; ++i )
			printf("%d ",s[i]);
		putchar('\n');
	}
	return 0;
}

