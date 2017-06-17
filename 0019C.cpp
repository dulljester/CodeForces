/*
 * 19C: Deletion of Repeats
 * TOPIC: suffix automata, repeats
 * status:
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <map>
#define N (100000+7)
#define Q (3*N)
using namespace std;

typedef struct cell {
	cell *slink;
	map<int,cell *> son;
	int len, pos;
	cell() {}
} cell;

cell *ptr, pool[Q];

int main() {
	int i,j,k;
	return 0;
}

