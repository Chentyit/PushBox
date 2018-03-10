#include<iostream>
#include<conio.h>
#include<stack>
#include<cmath>
#include "Function.h"
using namespace std;

int main() {
	char map[8][8];
	int r[3], c[4];
	makeMap(map, r, c);
	Step(map, r, c);
	return 0;
}