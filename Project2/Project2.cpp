﻿#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include<vector>
#include<stdlib.h>
#include<utility>
#include<string>
#include <time.h>
#include<mysql.h>
using namespace std;
/*함수 선언*/
int keyControl();
void init();
void titleDraw(); //게임 제목 출력)
int menuDraw();
void textcolor(int color_number);
int maplistDraw();
void infoDraw();
void CursorView();
extern void draw_plate(int column, int row);
void move_arrow_key(char chr, int* x, int* y, int x_b, int y_b);
void gotoxy(int x, int y);
void print_sedoku(int count_num);
void check1(bool check[], int x, int count_num);
void check2(bool check[], int y, int count_num);
void check3(bool check[], int x, int y, int count_num);
void dfs(int cnt, int count_num);
void find_sedoku();
int sedoku_table[16][3][9][9];
vector<pair<int, int>> xy;
vector<string>  sedoku_set[16];
int q_estado;
bool isture = false;
bool abc(int Sedoku_quiz)
{
	int x;
	int y;
	for (x = 0; x < 9; x++) {
		for (y = 0; y < 9; y++)
			if (sedoku_table[Sedoku_quiz][2][x][y] != sedoku_table[Sedoku_quiz][1][x][y]) {
				return false;
			}
	}
	return true;
}

// 스도쿠 배열에 대해서 전역변수를 선언했습니다. 전역변수를 최대한 사용하지않게 추후에 고치겠습니다.


#define X_MAX 35// 가로(열) 방향의 최대값
#define Y_MAX 18// 세로(행) 방향의 최대값
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // 선택(스페이스바)





extern int numx = 0; // 배열 위치 선정
extern int numy = 0;

extern int sedoku_quiz = 0; // 스도쿠 난이도 선택 0 ~ 14

extern int sedoku_default = 0;
extern int sedoku_answer = 1; // 스도쿠 초기값(0), 정답(1), 현재값(2)
extern int sedoku_change = 2;

int main() {
	bool result = false;
	find_sedoku();
	srand(time(NULL));
	//github desktop을 이용해서 push와 pull을 해봤으니 hello문을 지웠습니다.

	//게임 시작화면 - 시작화면 코딩할때는 주석풀고하세용.
	/*
	init();
	titleDraw();
	int menuCode = menuDraw();
	printf("선택한 메뉴: %d\n", menuCode);
	system("cls");
	CursorView(); // <- 메뉴코드에서 커서 숨김처리 되서 이걸로 다시 커서 나타내요
	*/
	// 게임 진행하면 - 코딩할때는 별표 주석풀고하세요
	char key;
	int x = 3, y = 2;


	while (result != true) {
		titleDraw();
		int menuCode = menuDraw();

		if (menuCode == 0) { //게임시작

			int n = maplistDraw();
			system("cls");
			if (n == 0) {
				//쉬움
				printf("쉬움 선택함\n");
				sedoku_quiz = rand() % 5;
				system("cls");

				while (result != true) {

					draw_plate(9, 9);
					gotoxy(x, y);
					key = _getch();
					move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
					Sleep(10);
					system("cls");
					result = abc(sedoku_quiz);

				}
				printf("스도쿠를 성공하셨습니다\n");
				printf("아무키나 입력하여 메뉴화면으로 돌아가십시요");
				getchar();
				system("cls");
				result = false;
				Sleep(1000);
			}
			else if (n == 1) {
				//쉬움
				printf("중간 선택함\n");
				sedoku_quiz = rand() % 5 + 5;

				system("cls");

				while (result != true) {

					draw_plate(9, 9);
					gotoxy(x, y);
					key = _getch();
					move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
					Sleep(10);
					system("cls");
					result = abc(sedoku_quiz);
				}
				printf("스도쿠를 성공하셨습니다\n");
				printf("아무키나 입력하여 메뉴화면으로 돌아가십시요");
				getchar();
				system("cls");
				result = false;
				Sleep(1000);
			}
			else if (n == 2) {
				//쉬움
				printf("어려움 선택함\n");
				sedoku_quiz = rand() % 5 + 10;

				system("cls");

				while (result != true) {

					draw_plate(9, 9);
					gotoxy(x, y);
					key = _getch();
					move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
					Sleep(10);
					system("cls");
					result = abc(sedoku_quiz);

				}
				printf("스도쿠를 성공하셨습니다\n");
				printf("아무키나 입력하여 메뉴화면으로 돌아가십시요");
				getchar();
				system("cls");
				result = false;
				Sleep(1000);
			}
		}
		else if (menuCode == 1) {
			infoDraw(); //게임정보
		}
		else if (menuCode == 2) {
			return 0; //종료
		}
		system("cls");
	}
	return 0;
}
void draw_plate(int column, int row) // 스도쿠 판 출력 함수
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[12];
	for (i = 1; i < 12; i++) // 스도쿠 테두리 모양 저장 ex) {"┏", "━", "┯", "┓"},
	{
		b[i] = 0xa0 + i;
	}
	// The following code prints the first row.
	printf("%c%c", a, b[3]);
	// The following line was added to double the horizontal line
	printf("%c%c", a, b[1]);
	for (i = 0; i < column - 1; i++)
	{
		printf("%c%c%c%c", a, b[1], a, b[1]);
		printf("%c%c", a, b[8]);
		// the following was added to double the horizontal line
		printf("%c%c", a, b[1]);
	}
	printf("%c%c%c%c", a, b[1], a, b[1]);
	printf("%c%c", a, b[4]);
	printf("\n");
	// the following code print the middle grids.
	for (i = 0; i < row - 1; i++)
	{
		printf("%c%c", a, b[2]);
		for (j = 0; j < column; j++)
		{
			textcolor(15);
			printf(" "); // 스도쿠 칸 오른쪽 공백
			if (sedoku_table[sedoku_quiz][sedoku_default][i][j] == 0) { //원래의 값이 0이면 색깔을 노란색으로
				textcolor(14); //14: 노란색
				printf("%d", sedoku_table[sedoku_quiz][sedoku_change][i][j]); // sedoku_table 배열 숫자 출력
			}
			else {
				textcolor(15); //15: 흰색
				printf("%d", sedoku_table[sedoku_quiz][sedoku_change][i][j]); // sedoku_table 배열 숫자 출력
			}
			textcolor(15);
			printf(" "); // 스도쿠 칸 왼쪽 공백
			printf("%c%c", a, b[2]);
		}
		printf("\n");
		printf("%c%c", a, b[7]);
		for (j = 0; j < column - 1; j++)
		{
			printf("%c%c%c%c%c%c", a, b[1], a, b[1], a, b[1]);
			printf("%c%c", a, b[11]);
		}
		printf("%c%c%c%c%c%c", a, b[1], a, b[1], a, b[1]);
		printf("%c%c", a, b[9]);
		printf("\n");
	}
	// The following code prints the last line of the grid.
	printf("%c%c", a, b[2]);
	for (j = 0; j < column; j++)
	{
		textcolor(15);
		printf(" "); // 스도쿠 칸 오른쪽 공백
		if (sedoku_table[sedoku_quiz][sedoku_default][i][j] == 0) { //원래의 값이 0이면 색깔을 노란색으로
			textcolor(14); //14: 노란색
			printf("%d", sedoku_table[sedoku_quiz][sedoku_change][i][j]); // sedoku_table 배열 숫자 출력
		}
		else {
			textcolor(15); //15: 흰색
			printf("%d", sedoku_table[sedoku_quiz][sedoku_change][i][j]); // sedoku_table 배열 숫자 출력
		}
		textcolor(15);
		printf(" "); // 스도쿠 칸 왼쪽 공백
		printf("%c%c", a, b[2]);
	}
	printf("\n");
	printf("%c%c", a, b[6]);
	for (i = 0; i < column - 1; i++)
	{
		printf("%c%c%c%c%c%c", a, b[1], a, b[1], a, b[1]);
		printf("%c%c", a, b[10]);
	}
	printf("%c%c%c%c%c%c", a, b[1], a, b[1], a, b[1]);
	printf("%c%c", a, b[5]);
	printf("\n");
}

void move_arrow_key(char key, int* x1, int* y1, int x_b, int y_b)
{
	switch (key)
	{
	case 72:// 위쪽(상) 방향의 화살표 키 입력
		*y1 = *y1 - 2;
		if (*y1 < 2) {
			*y1 = 2; // y좌표의 최솟값
			numy = 0; // 좌표값이 최대일 경우 배열 값도 최대를 넘지 않도록 고정
			break;
		}
		else {
			numy = numy - 1; // 커서의 움직임에 따라 배열 위치 선택
			break;
		}
	case 75:// 왼쪽(좌) 방향의 화살표 키 입력
		*x1 = *x1 - 4;
		if (*x1 < 3) {
			*x1 = 3; // x 좌표의 최솟값
			numx = 0; // 좌표값이 최대일 경우 배열 값도 최대를 넘지 않도록 고정
			break;
		}
		else {
			numx = numx - 1; // 커서의 움직임에 따라 배열 위치 선택
			break;
		}
	case 77:// 오른쪽(우) 방향의 화살표 키 입력
		*x1 = *x1 + 4;
		if (*x1 > x_b) {
			*x1 = x_b; // x 좌표의 최대값
			numx = 8; // 좌표값이 최대일 경우 배열 값도 최대를 넘지 않도록 고정
			break;
		}
		else {
			numx = numx + 1; // 커서의 움직임에 따라 배열 위치 선택
			break;
		}
	case 80:// 아래쪽(하) 방향의 화살표 키 입력
		*y1 = *y1 + 2;
		if (*y1 > y_b) {
			*y1 = y_b;// y 좌표의 최대값
			numy = 8; // 좌표값이 최대일 경우 배열 값도 최대를 넘지 않도록 고정
			break;
		}
		else {
			numy = numy + 1; // 커서의 움직임에 따라 배열 위치 선택
			break;
		}
	case 49:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 1;  //해당하는 배열의 수를 1로 변경
			break;
		}
		else
			break;
	case 50:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 2;  //해당하는 배열의 수를 2로 변경
			break;
		}
		else
			break;
	case 51:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 3;  //해당하는 배열의 수를 3로 변경
			break;
		}
		else
			break;
	case 52:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 4;  //해당하는 배열의 수를 4로 변경
			break;
		}
		else
			break;
	case 53:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 5;  //해당하는 배열의 수를 5로 변경
			break;
		}
		else
			break;
	case 54:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 6;  //해당하는 배열의 수를 6로 변경
			break;
		}
		else
			break;
	case 55:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 7;  //해당하는 배열의 수를 7로 변경
			break;
		}
		else
			break;
	case 56:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 8;  //해당하는 배열의 수를 8로 변경
			break;
		}
		else
			break;
	case 57:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 9;  //해당하는 배열의 수를 9로 변경
			break;
		}
		else
			break;
	default:
		return;
	}
}



void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void print_sedoku(int count_num) {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << sedoku_table[count_num][1][i][j] << " ";

		}
		cout << "\n";
	}
}
void check1(bool check[], int x, int count_num) {
	for (int i = 0; i < 9; i++) {
		if (sedoku_table[count_num][1][x][i] != 0) {
			int where = sedoku_table[count_num][1][x][i] - 1;
			check[where] = true;
		}
	}

}

void check2(bool check[], int y, int count_num) {
	for (int i = 0; i < 9; i++) {
		if (sedoku_table[count_num][1][i][y] != 0) {
			int where = sedoku_table[count_num][1][i][y] - 1;
			if (check[where] == false) {
				check[where] = true;
			}
		}
	}
}
void check3(bool check[], int x, int y, int count_num) {
	int xx = x / 3;
	int yy = y / 3;
	for (int i = 3 * xx; i < 3 * xx + 3; i++) {
		for (int j = 3 * yy; j < yy * 3 + 3; j++) {
			if (sedoku_table[count_num][1][i][j] != 0) {
				int where = sedoku_table[count_num][1][i][j] - 1;
				if (check[where] == false) {
					check[where] = true;
				}

			}
		}
	}

}
bool istrue = false;
void dfs(int cnt, int count_num) {

	if (istrue == true) {
		return;
	}
	if (cnt == xy.size()) {
		istrue = true;
		//해당코드는 확인하고 싶을때만 주석처리를 해줍니다.print_sedoku(count_num);
		return;
	}

	int x = xy[cnt].first;
	int y = xy[cnt].second;
	bool can[9] = { false,false,false,false,false,false,false,false };
	check1(can, x, count_num);

	check2(can, y, count_num);

	check3(can, x, y, count_num);


	//xy좌표로 가능한 리스트 불러온다
	for (int i = 0; i < 9; i++) {
		if (can[i] == false) {
			sedoku_table[count_num][1][x][y] = i + 1;
			dfs(cnt + 1, count_num);
			if (istrue == true) {
				return;
			}
			sedoku_table[count_num][1][x][y] = 0;



		}
	}
}
void find_sedoku() {

	MYSQL* conectar;
	MYSQL_ROW fila;
	MYSQL_RES* result;
	string a;
	vector<string>  sedoku_set[16];
	conectar = mysql_init(0);
	conectar = mysql_real_connect(conectar, "localhost", "root", "1417", "sedoku_table", 3306, NULL, 0);
	if (conectar) {
		string consulta = "select * from sedoku";
		const char* c = consulta.c_str();
		int cnt = 0;
		q_estado = mysql_query(conectar, c);
		if (!q_estado) {
			result = mysql_store_result(conectar);
			while (fila = mysql_fetch_row(result)) {
				char ch[81];
				a = fila[2];
				for (int i = 0; i < 81; i++) {
					ch[i] = a[i];
				}
				sedoku_set[cnt].push_back(ch);
				cnt++;
			}
		}
	}


	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 1; j++) {
			for (int p = 0; p < 9; p++) {
				for (int q = 0; q < 9; q++) {
					int num = sedoku_set[i][j][p * 9 + q] - '0';
					sedoku_table[i][j][p][q] = num;
					sedoku_table[i][1][p][q] = num;
					sedoku_table[i][2][p][q] = num;
				}
			}
		}
	}
	// 끝

	//각요소들에 대해 백트래킹으로 돌리고 그값을 받아온는 부분
	for (int q = 0; q < 15; q++) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (sedoku_table[q][1][i][j] == 0) xy.push_back(make_pair(i, j));
			}
		}
		dfs(0, q);
		xy.clear();
		vector<pair<int, int>>().swap(xy);//vector 초기화
		istrue = false;

	}
}
int keyControl()
{
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{
		return SUBMIT;
	}
}

void init() // 콘솔 창 설정 함수 
{
	system("mode con cols=100 lines=20 | title 게 임 제 목"); // 창 넓이

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 커서 숨김 처리
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
void CursorView()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 커서 숨김 처리
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = true;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void textcolor(int color_number) // 문자 색상 변경 실수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void titleDraw()
{
	printf("\n\n\n\n");
	printf("   ■■■     ■■■■   ■■■       ■■     ■   ■   ■    ■     \n");
	printf("  ■          ■         ■    ■   ■    ■   ■ ■     ■    ■     \n");
	printf("   ■■■     ■■■■   ■    ■   ■    ■   ■■      ■    ■     \n");
	printf("         ■   ■         ■    ■   ■    ■   ■ ■     ■    ■     \n");
	printf("   ■■■     ■■■■    ■■■      ■■     ■   ■     ■■       \n");
}

int menuDraw()
{
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y); // -2 한 이유는 > 를 출력해야하기 때문에
	printf("> 게임시작");
	gotoxy(x, y + 1);
	printf("게임정보");
	gotoxy(x, y + 2);
	printf("종료");

	while (1)
	{ // 무한반복
		int n = keyControl();
		switch (n) {
		case UP: { //입력한 키와 값이 UP인 경우 (w)
			if (y > 12) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}

		case DOWN: {
			if (y < 14) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 12; }
		}
	}
}

int maplistDraw() {
	int x = 24;
	int y = 6;
	system("cls");
	printf("\n\n");
	printf("                     [ 맵 선택 ]\n\n");

	gotoxy(x - 2, y);
	printf("> 쉬움");
	gotoxy(x, y + 1);
	printf("중간");
	gotoxy(x, y + 2);
	printf("어려움");
	gotoxy(x, y + 3);
	printf("뒤로");

	while (1) {
		int n = keyControl();
		switch (n) {
		case UP: {
			if (y > 6) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < 9) {
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			return y - 6;
		}
		}
	}
}

void infoDraw() {
	system("cls"); //화면 모두 지우기
	printf("게임설명");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}

