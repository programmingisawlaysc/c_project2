#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
extern void draw_plate(int column, int row);
void move_arrow_key(char chr, int* x, int* y, int x_b, int y_b);
void gotoxy(int x, int y);

#define X_MAX 35// ����(��) ������ �ִ밪
#define Y_MAX 18// ����(��) ������ �ִ밪

using namespace std;
// �ش� ������ ���̺����� �����ͺ��̽��� �˰��� ���̵� ���� �ڵ��� �Ҽ� �ֵ��� �����س��� �����Դϴ�. �ش簪���� �̿��Ͽ� ������ ������ �����ϼ���.

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

extern int numx = 0; // �迭 ��ġ ����
extern int numy = 0;

int main() {
	//github desktop�� �̿��ؼ� push�� pull�� �غ����� hello���� �������ϴ�.
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

void draw_plate(int column, int row) // ������ �� ��� �Լ�
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[12];
	for (i = 1; i < 12; i++) // ������ �׵θ� ��� ���� ex) {"��", "��", "��", "��"},
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
			printf(" "); // ������ ĭ ������ ����
			printf("%d", sedoku_table_easy[i][j]); // sedoku_table_easy �迭 ���� ���
			printf(" "); // ������ ĭ ���� ����
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
		printf(" "); // ������ ĭ ������ ����
		printf("%d", sedoku_table_easy[8][j]); // sedoku_table_easy �迭 ���� ���
		printf(" "); // ������ ĭ ���� ����
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
	case 72:// ����(��) ������ ȭ��ǥ Ű �Է�
		*y1 = *y1 - 2;
		if (*y1 < 2) {
			*y1 = 2; // y��ǥ�� �ּڰ�
			numy = 0; // ��ǥ���� �ִ��� ��� �迭 ���� �ִ븦 ���� �ʵ��� ����
			break; 
		}
		else {
			numy = numy - 1; // Ŀ���� �����ӿ� ���� �迭 ��ġ ����
			break;
		}
	case 75:// ����(��) ������ ȭ��ǥ Ű �Է�
		*x1 = *x1 - 4;
		if (*x1 < 3) {
			*x1 = 3; // x ��ǥ�� �ּڰ�
			numx = 0; // ��ǥ���� �ִ��� ��� �迭 ���� �ִ븦 ���� �ʵ��� ����
			break;
		}
		else {
			numx = numx - 1; // Ŀ���� �����ӿ� ���� �迭 ��ġ ����
			break;
		}
	case 77:// ������(��) ������ ȭ��ǥ Ű �Է�
		*x1 = *x1 + 4;
		if (*x1 > x_b) {
			*x1 = x_b; // x ��ǥ�� �ִ밪
			numx = 8; // ��ǥ���� �ִ��� ��� �迭 ���� �ִ븦 ���� �ʵ��� ����
			break;
		}
		else {
			numx = numx + 1; // Ŀ���� �����ӿ� ���� �迭 ��ġ ����
			break;
		}
	case 80:// �Ʒ���(��) ������ ȭ��ǥ Ű �Է�
		*y1 = *y1 + 2;
		if (*y1 > y_b) {
			*y1 = y_b;// y ��ǥ�� �ִ밪
			numy = 8; // ��ǥ���� �ִ��� ��� �迭 ���� �ִ븦 ���� �ʵ��� ����
			break;
		}
		else {
			numy = numy + 1; // Ŀ���� �����ӿ� ���� �迭 ��ġ ����
			break;
		}
	case 49:
		sedoku_table_easy[numy][numx] = 1;  //�ش��ϴ� �迭�� ���� 1�� ����
		break;
	case 50:
		sedoku_table_easy[numy][numx] = 2;  //�ش��ϴ� �迭�� ���� 2�� ����
		break;
	case 51:
		sedoku_table_easy[numy][numx] = 3;  //�ش��ϴ� �迭�� ���� 3���� ����
		break;
	case 52:
		sedoku_table_easy[numy][numx] = 4;  //�ش��ϴ� �迭�� ���� 4�� ����
		break;
	case 53:
		sedoku_table_easy[numy][numx] = 5;  //�ش��ϴ� �迭�� ���� 5�� ����
		break;
	case 54:
		sedoku_table_easy[numy][numx] = 6;  //�ش��ϴ� �迭�� ���� 6���� ����
		break;
	case 55:
		sedoku_table_easy[numy][numx] = 7;  //�ش��ϴ� �迭�� ���� 7�� ����
		break;
	case 56:
		sedoku_table_easy[numy][numx] = 8;  //�ش��ϴ� �迭�� ���� 8�� ����
		break;
	case 57:
		sedoku_table_easy[numy][numx] = 9;  //�ش��ϴ� �迭�� ���� 9�� ����
		break;
	default:
		return;
	}
}



void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}