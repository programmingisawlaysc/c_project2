#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
extern void draw_plate(int column, int row);
void move_arrow_key(char chr, int* x, int* y, int x_b, int y_b);
void gotoxy(int x, int y);

#define X_MAX 35// 가로(열) 방향의 최대값
#define Y_MAX 18// 세로(행) 방향의 최대값

using namespace std;
// 해당 스도쿠 테이블값들은 데이터베이스와 알고리즘 없이도 쉽게 코딩을 할수 있도록 설정해놓은 값들입니다. 해당값들을 이용하여 스도쿠 게임을 제작하세요.

int sedoku_table_easy[10][10] = { 
	{0, 3, 5, 4 ,6 ,9 ,2 ,7, 8},
	{7, 8 ,2 ,1 ,0 ,5 ,6 ,0, 9},
	{0, 6, 0, 2, 7, 8, 1, 3, 5},
	{3, 2 ,1 ,0 ,4 ,6 ,8 ,9 ,7},
	{8, 0, 4, 9, 1, 3, 5, 0, 6},
	{5, 9, 6, 8, 2, 0, 4, 1, 3},
	{9 ,1 ,7 ,6, 5, 2, 0, 8, 0},
	{6 ,0 ,3 ,7 ,0, 1, 9, 5, 2},
	{2, 5, 8, 3, 9, 4, 7, 6, 0}
};
int sedoku_table_easy_answer[10][10] = { 
	{1, 3, 5, 4 ,6 ,9 ,2 ,7, 8},
	{7, 8 ,2 ,1 ,3 ,5 ,6 ,4, 9},
	{4, 6, 9, 2, 7, 8, 1, 3, 5},
	{3, 2 ,1 ,5 ,4 ,6 ,8 ,9 ,7},
	{8, 7, 4, 9, 1, 3, 5, 2, 6},
	{5, 9, 6, 8, 2, 7, 4, 1, 3},
	{9 ,1 ,7 ,6, 5, 2, 3, 8, 4},
	{6 ,4 ,3 ,7 ,8, 1, 9, 5, 2},
	{2, 5, 8, 3, 9, 4, 7, 6, 1}
};

extern int numx = 0; // 배열 위치 선정
extern int numy = 0;

int main() {
	//github desktop을 이용해서 push와 pull을 해봤으니 hello문을 지웠습니다.
	int row, column;
	char key;
	int x = 3, y = 2;
	row = 9;
	column = 9;
	
	
	while (1) {

		draw_plate(column, row);
		gotoxy(49, 10);
		printf("%d %d", x, y);
		gotoxy(x, y);
		key = _getch();
		move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
		Sleep(10);
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
			printf(" "); // 스도쿠 칸 오른쪽 공백
			printf("%d", sedoku_table_easy[i][j]); // sedoku_table_easy 배열 숫자 출력
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
		printf(" "); // 스도쿠 칸 오른쪽 공백
		printf("%d", sedoku_table_easy[8][j]); // sedoku_table_easy 배열 숫자 출력
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
		sedoku_table_easy[numy][numx] = 1;  //해당하는 배열의 수를 1로 변경
		break;
	case 50:
		sedoku_table_easy[numy][numx] = 2;  //해당하는 배열의 수를 2로 변경
		break;
	case 51:
		sedoku_table_easy[numy][numx] = 3;  //해당하는 배열의 수를 3으로 변경
		break;
	case 52:
		sedoku_table_easy[numy][numx] = 4;  //해당하는 배열의 수를 4로 변경
		break;
	case 53:
		sedoku_table_easy[numy][numx] = 5;  //해당하는 배열의 수를 5로 변경
		break;
	case 54:
		sedoku_table_easy[numy][numx] = 6;  //해당하는 배열의 수를 6으로 변경
		break;
	case 55:
		sedoku_table_easy[numy][numx] = 7;  //해당하는 배열의 수를 7로 변경
		break;
	case 56:
		sedoku_table_easy[numy][numx] = 8;  //해당하는 배열의 수를 8로 변경
		break;
	case 57:
		sedoku_table_easy[numy][numx] = 9;  //해당하는 배열의 수를 9로 변경
		break;
	default:
		return;
	}
}



void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}