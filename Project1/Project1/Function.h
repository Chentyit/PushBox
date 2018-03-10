#include<conio.h>
#include<iostream>
#include<time.h>
#include<string>
#include "Point.h"
using namespace std;

void makeMap(char map[8][8], int *r, int *c) {					//生成地图-1
	srand((unsigned)time(NULL));
	for (int i = 0; i < 8; i+=7){
		for (int j = 0; j < 8; j++) {
			map[i][j] = '#';
		}
	}
	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 7; j++) {
			map[i][j] = ' ';
		}
		for (int j = 0; j < 8; j += 7) {
			map[i][j] = '#';
		}
	}
	map[1][3] = map[4][1] = map[6][4] = map[3][6] = '#';
	/*初始化目的地*/
	//r[4] = { 4, 2, 5, 3 }, c[4] = { 2, 3, 4, 5 };
	r[0] = 4, r[1] = 2, r[2] = 5, r[3] = 3;
	c[0] = 2, c[1] = 3, c[2] = 4, c[3] = 5;
}

void Refresh(char map[8][8], const int *r, const int *c) {
	for (int i = 0; i < 4; i++) {
		int k = 0;
		if (map[r[i]][c[i]] != '@') {
			if (map[r[i]][c[i]] == 'A' || map[r[i]][c[i]] == 'B' || map[r[i]][c[i]] == 'C' || map[r[i]][c[i]] == 'D') {
				map[r[i]][c[i]] = '@';
			}
			else {
				map[r[i]][c[i]] = '*';
			}
		}
		else {
			map[r[i]][c[i]] = '@';
		}
	}
}

void ShowMap(char map[8][8], const int *r, const int *c) {					//刷新地图
	Refresh(map, r, c);
	system("cls");
	cout << ' ' << " =================================================" << endl;
	cout << ' ' << "‖     操作速度要慢！要慢！要慢！不然会出BUG     ‖" << endl;
	cout << ' ' << "‖       键盘数据接收没这么快，会产生错误！      ‖" << endl;
	cout << ' ' << " =================================================" << endl;
	for (int i = 0; i < 8; i++) {
		cout << endl << '\t';
		for (int j = 0; j < 8; j++) {
			cout <<map[i][j];
		}
	}
	cout << endl << endl;
	cout << ' ' << " ====================" << endl;
	cout << ' ' << "‖     8 - 向上     ‖" << endl;
	cout << ' ' << "‖     2 - 向下     ‖" << endl;
	cout << ' ' << "‖     4 - 向左     ‖" << endl;
	cout << ' ' << "‖     6 - 向右     ‖" << endl;
	cout << ' ' << "‖     7 - 撤回     ‖" << endl;
	cout << ' ' << " ====================" << endl;
}

void PushBox(char map[8][8], int &xb, int &yb, Point b, 
	int &xbbuf, int &ybbuf, stack<Point> &box, int &flagbuf, char name) {			//盒子路径压栈
	switch (name) {
	case 'A':
		map[xb][yb] = 'A';
		b.x = xbbuf;
		b.y = ybbuf;
		xbbuf = xb;
		ybbuf = yb;
		box.push(b);
		flagbuf = 1;
		break;
	case 'B':
		map[xb][yb] = 'B';
		b.x = xbbuf;
		b.y = ybbuf;
		xbbuf = xb;
		ybbuf = yb;
		box.push(b);
		flagbuf = 2;
		break;
	case 'C':
		map[xb][yb] = 'C';
		b.x = xbbuf;
		b.y = ybbuf;
		xbbuf = xb;
		ybbuf = yb;
		box.push(b);
		flagbuf = 3;
		break;
	case 'D':
		map[xb][yb] = 'D';
		b.x = xbbuf;
		b.y = ybbuf;
		xbbuf = xb;
		ybbuf = yb;
		box.push(b);
		flagbuf = 4;
		break;
	default:
		break;
	}
}

void PushPath(char map[8][8], Point p, int &xr, int &yr,
	int &xrbuf, int &yrbuf, int &flagbuf, stack<Point> &path) {			//角色路径压栈
	p.x = xrbuf;
	p.y = yrbuf;
	p.d = flagbuf;
	xrbuf = xr;
	yrbuf = yr;
	flagbuf = 0;
	path.push(p);
}

void Step(char map[8][8], const int *r, const int *c) {					//所走路径
	string s;
	Point p, b;
	stack<Point> path;
	stack<Point> boxA;
	stack<Point> boxB;
	stack<Point> boxC;
	stack<Point> boxD;
	/*初始化角色起点*/
	int xr = 1, yr = 1, flag = 0;
	int xrbuf = 0, yrbuf = 0, flagbuf = 0;				//角色路径缓存区
	xrbuf = xr;
	yrbuf = yr;
	map[xr][yr] = 'O';
	/*初始化箱子1*/
	int xb1 = 2, yb1 = 2;
	map[xb1][yb1] = 'A';
	/*初始化箱子2*/
	int xb2 = 3, yb2 = 3;
	map[xb2][yb2] = 'B';
	/*初始化箱子3*/
	int xb3 = 3, yb3 = 2;
	map[xb3][yb3] = 'C';
	/*初始化箱子4*/
	int xb4 = 4, yb4 = 4;
	map[xb4][yb4] = 'D';
	int xbbuf = 0, ybbuf = 0;							//箱子路径缓存区
	ShowMap(map, r, c);
	while (_kbhit() == NULL) {
		switch (_getch() - '0') {
		case 2:								//向下
			xr++;
			if (map[xr][yr] != '#' && map[xr][yr] != '@' && map[xr][yr] != '*') {
				switch (map[xr][yr] ) {					//判断推动那个箱子
				case 'A':
					xb1 = xbbuf = xr;
					yb1 = ybbuf = yr;
					xb1 = xr + 1;
					if (map[xb1][yb1] != '#' && map[xb1][yb1] != 'A' && map[xb1][yb1] != 'B' 
						&& map[xb1][yb1] != 'C' && map[xb1][yb1] != 'D') {
						PushBox(map, xb1, yb1, b, xbbuf, ybbuf, boxA, flagbuf, map[xr][yr]);
					}
					else {
						xr--;
						xb1--;
					}
					break;
				case 'B':
					xb2 = xbbuf = xr;
					yb2 = ybbuf = yr;
					xb2 = xr + 1;
					if (map[xb2][yb2] != '#' && map[xb2][yb2] != 'A' && map[xb2][yb2] != 'B' 
						&& map[xb2][yb2] != 'C' && map[xb2][yb2] != 'D') {
						PushBox(map, xb2, yb2, b, xbbuf, ybbuf, boxB, flagbuf, map[xr][yr]);
					}
					else {
						xr--;
						xb2--;
					}
					break;
				case 'C':
					xb3 = xbbuf = xr;
					yb3 = ybbuf = yr;
					xb3 = xr + 1;
					if (map[xb3][yb3] != '#' && map[xb3][yb3] != 'A' && map[xb3][yb3] != 'B' 
						&& map[xb3][yb3] != 'C' && map[xb3][yb3] != 'D') {
						PushBox(map, xb3, yb3, b, xbbuf, ybbuf, boxC, flagbuf, map[xr][yr]);
					}
					else {
						xr--;
						xb3--;
					}
					break;
				case 'D':
					xb4 = xbbuf = xr;
					yb4 = ybbuf = yr;
					xb4 = xr + 1;
					if (map[xb4][yb4] != '#' && map[xb4][yb4] != 'A' && map[xb4][yb4] != 'B' 
						&& map[xb4][yb4] != 'C' && map[xb4][yb4] != 'D') {
						PushBox(map, xb4, yb4, b, xbbuf, ybbuf, boxD, flagbuf, map[xr][yr]);
					}
					else {
						xr--;
						xb4--;
					}
					break;
				default:
					break;
				}
				map[xr][yr] = 'O';
				map[xr - 1][yr] = ' ';
				PushPath(map, p, xr, yr, xrbuf, yrbuf, flagbuf, path);
				ShowMap(map, r, c);
			}
			else
				xr--;
			break;
		case 4:								//向左
			yr--;
			if (map[xr][yr] != '#' && map[xr][yr] != '@' && map[xr][yr] != '*') {
				switch (map[xr][yr]) {					//判断推动那个箱子
				case 'A':
					xb1 = xbbuf = xr;
					yb1 = ybbuf = yr;
					yb1 = yr - 1;
					if (map[xb1][yb1] != '#' && map[xb1][yb1] != 'A' && map[xb1][yb1] != 'B' 
						&& map[xb1][yb1] != 'C' && map[xb1][yb1] != 'D') {
						PushBox(map, xb1, yb1, b, xbbuf, ybbuf, boxA, flagbuf, map[xr][yr]);
					}
					else {
						yr++;
						yb1++;
					}
					break;
				case 'B':
					xb2 = xbbuf = xr;
					yb2 = ybbuf = yr;
					yb2 = yr - 1;
					if (map[xb2][yb2] != '#' && map[xb2][yb2] != 'A' && map[xb2][yb2] != 'B'
						&& map[xb2][yb2] != 'C' && map[xb2][yb2] != 'D') {
						PushBox(map, xb2, yb2, b, xbbuf, ybbuf, boxB, flagbuf, map[xr][yr]);
					}
					else {
						yr++;
						yb2++;
					}
					break;
				case 'C':
					xb3 = xbbuf = xr;
					yb3 = ybbuf = yr;
					yb3 = yr - 1;
					if (map[xb3][yb3] != '#' && map[xb3][yb3] != 'A' && map[xb3][yb3] != 'B' 
						&& map[xb3][yb3] != 'C' && map[xb3][yb3] != 'D') {
						PushBox(map, xb3, yb3, b, xbbuf, ybbuf, boxC, flagbuf, map[xr][yr]);
					}
					else {
						yr++;
						yb3++;
					}
					break;
				case 'D':
					xb4 = xbbuf = xr;
					yb4 = ybbuf = yr;
					yb4 = yr - 1;
					if (map[xb4][yb4] != '#' && map[xb4][yb4] != 'A' && map[xb4][yb4] != 'B' 
						&& map[xb4][yb4] != 'C' && map[xb4][yb4] != 'D') {
						PushBox(map, xb4, yb4, b, xbbuf, ybbuf, boxD, flagbuf, map[xr][yr]);
					}
					else {
						yr++;
						yb4++;
					}
					break;
				default:
					break;
				}
				map[xr][yr] = 'O';
				map[xr][yr + 1] = ' ';
				PushPath(map, p, xr, yr, xrbuf, yrbuf, flagbuf, path);
				ShowMap(map, r, c);
			}
			else
				yr++;
			break;
		case 6:								//向右
			yr++;
			if (map[xr][yr] != '#' && map[xr][yr] != '@' && map[xr][yr] != '*'){
				switch (map[xr][yr]) {					//判断推动那个箱子
				case 'A':
					xb1 = xbbuf = xr;
					yb1 = ybbuf = yr;
					yb1 = yr + 1;
					if (map[xb1][yb1] != '#' && map[xb1][yb1] != 'A' && map[xb1][yb1] != 'B' 
						&& map[xb1][yb1] != 'C' && map[xb1][yb1] != 'D') {
						PushBox(map, xb1, yb1, b, xbbuf, ybbuf, boxA, flagbuf, map[xr][yr]);
					}
					else {
						yr--;
						yb1--;
					}
					break;
				case 'B':
					xb2 = xbbuf = xr;
					yb2 = ybbuf = yr;
					yb2 = yr + 1;
					if (map[xb2][yb2] != '#' && map[xb2][yb2] != 'A' && map[xb2][yb2] != 'B'
						&& map[xb2][yb2] != 'C' && map[xb2][yb2] != 'D') {
						PushBox(map, xb2, yb2, b, xbbuf, ybbuf, boxB, flagbuf, map[xr][yr]);
					}
					else {
						yr--;
						yb2--;
					}
					break;
				case 'C':
					xb3 = xbbuf = xr;
					yb3 = ybbuf = yr;
					yb3 = yr + 1;
					if (map[xb3][yb3] != '#' && map[xb3][yb3] != 'A' && map[xb3][yb3] != 'B' 
						&& map[xb3][yb3] != 'C' && map[xb3][yb3] != 'D') {
						PushBox(map, xb3, yb3, b, xbbuf, ybbuf, boxC, flagbuf, map[xr][yr]);
					}
					else {
						yr--;
						yb3--;
					}
					break;
				case 'D':
					xb4 = xbbuf = xr;
					yb4 = ybbuf = yr;
					yb4 = yr + 1;
					if (map[xb4][yb4] != '#' && map[xb4][yb4] != 'A' && map[xb4][yb4] != 'B'
						&& map[xb4][yb4] != 'C' && map[xb4][yb4] != 'D') {
						PushBox(map, xb4, yb4, b, xbbuf, ybbuf, boxD, flagbuf, map[xr][yr]);
					}
					else {
						yr--;
						yb4--;
					}
					break;
				default:
					break;
				}
				map[xr][yr] = 'O';
				map[xr][yr - 1] = ' ';
				PushPath(map, p, xr, yr, xrbuf, yrbuf, flagbuf, path);
				ShowMap(map, r, c);
			}
			else
				yr--;
			break;
		case 8:								//向上
			xr--;
			if (map[xr][yr] != '#' && map[xr][yr] != '@' && map[xr][yr] != '*') {
				switch (map[xr][yr]) {					//判断推动那个箱子
				case 'A':
					xb1 = xbbuf = xr;
					yb1 = ybbuf = yr;
					xb1 = xr - 1;
					if (map[xb1][yb1] != '#' && map[xb1][yb1] != 'A' && map[xb1][yb1] != 'B' 
						&& map[xb1][yb1] != 'C' && map[xb1][yb1] != 'D') {
						PushBox(map, xb1, yb1, b, xbbuf, ybbuf, boxA, flagbuf, map[xr][yr]);
					}
					else {
						xr++;
						xb1++;
					}
					break;
				case 'B':
					xb2 = xbbuf = xr;
					yb2 = ybbuf = yr;
					xb2 = xr - 1;
					if (map[xb2][yb2] != '#' && map[xb2][yb2] != 'A' && map[xb2][yb2] != 'B' 
						&& map[xb2][yb2] != 'C' && map[xb2][yb2] != 'D') {
						PushBox(map, xb2, yb2, b, xbbuf, ybbuf, boxB, flagbuf, map[xr][yr]);
					}
					else {
						xr++;
						xb2++;
					}
					break;
				case 'C':
					xb3 = xbbuf = xr;
					yb3 = ybbuf = yr;
					xb3 = xr - 1;
					if (map[xb3][yb3] != '#' && map[xb3][yb3] != 'A' && map[xb3][yb3] != 'B' 
						&& map[xb3][yb3] != 'C' && map[xb3][yb3] != 'D') {
						PushBox(map, xb3, yb3, b, xbbuf, ybbuf, boxC, flagbuf, map[xr][yr]);
					}
					else {
						xr++;
						xb3++;
					}
					break;
				case 'D':
					xb4 = xbbuf = xr;
					yb4 = ybbuf = yr;
					xb4 = xr - 1;
					if (map[xb4][yb4] != '#' && map[xb4][yb4] != 'A' && map[xb4][yb4] != 'B' 
						&& map[xb4][yb4] != 'C' && map[xb4][yb4] != 'D') {
						PushBox(map, xb4, yb4, b, xbbuf, ybbuf, boxD, flagbuf, map[xr][yr]);
					}
					else {
						xr++;
						xb4++;
					}
					break;
				default:
					break;
				}
				map[xr][yr] = 'O';
				map[xr + 1][yr] = ' ';
				PushPath(map, p, xr, yr, xrbuf, yrbuf, flagbuf, path);
				ShowMap(map, r, c);
			}
			else
				xr++;
			break;
		case 7:								//撤回
			if (path.empty() != 1) {
				map[xr][yr] = ' ';
				Point px = path.top();
				xrbuf = xr = px.x;
				xrbuf = yr = px.y;
				switch (px.d) {
				case 1:
					if (boxA.empty() != 1) {
						map[xb1][yb1] = ' ';
						xbbuf = xb1 = boxA.top().x;
						ybbuf = yb1 = boxA.top().y;
						map[xb1][yb1] = 'A';
						boxA.pop();
					}
					break;
				case 2:
					if (boxB.empty() != 1) {
						map[xb2][yb2] = ' ';
						xbbuf = xb2 = boxB.top().x;
						ybbuf = yb2 = boxB.top().y;
						map[xb2][yb2] = 'B';
						boxB.pop();
					}
					break;
				case 3:
					if (boxC.empty() != 1) {
						map[xb3][yb3] = ' ';
						xbbuf = xb3 = boxC.top().x;
						ybbuf = yb3 = boxC.top().y;
						map[xb3][yb3] = 'C';
						boxC.pop();
					}
					break;
				case 4:
					if (boxD.empty() != 1) {
						map[xb4][yb4] = ' ';
						xbbuf = xb4 = boxD.top().x;
						ybbuf = yb4 = boxD.top().y;
						map[xb4][yb4] = 'D';
						boxD.pop();
					}
					break;
				}
				map[xr][yr] = 'O';
				path.pop();
				ShowMap(map, r, c);
			}
			break;
		default:
			break;
		}
	}
}