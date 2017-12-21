/*
 * 115. Calendar
 * TOPIC: ad hoc
 * status: Accepted
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 512

int day[N],
	m[12] = {31,28,31,30,31,30,31,31,30,31,30,31},
	rdd[12][0x40];

int main() {
	int i,j,k,t;
	for ( k = 0, i = 0; i < 12; ++i )
		for ( j = 0; j < m[i]; ++j, ++k ) {
			if ( k == 0 ) {
				day[k] = 0, rdd[i][j+1] = 0;
				continue ;
			}
			day[k] = (day[k-1]+1)%7, rdd[i][j+1] = k;
		}
	for ( ;2 == scanf("%d %d",&j,&i); ) {
		if ( m[--i] < j ) {
			puts("Impossible");
			continue ;
		}
		t = day[rdd[i][j]];
		printf("%d\n",t+1);
	}
	return 0;
}

