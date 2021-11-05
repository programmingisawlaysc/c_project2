#include <iostream>
#include <stdio.h>
#include <Windows.h>
extern void draw_plate(int column, int row);


using namespace std;
// �ش� ������ ���̺����� �����ͺ��̽��� �˰��� ���̵� ���� �ڵ��� �Ҽ� �ֵ��� �����س��� �����Դϴ�. �ش簪���� �̿��Ͽ� ������ ������ �����ϼ���.

int sedoku_table_easy[10][10] = { {0, 3, 5, 4 ,6 ,9 ,2 ,7, 8},{7, 8 ,2 ,1 ,0 ,5 ,6 ,0, 9
},{0, 6, 0, 2, 7, 8, 1, 3, 5},{3, 2 ,1 ,0 ,4 ,6 ,8 ,9 ,7 },{ 8, 0, 4, 9, 1, 3, 5, 0, 6}, {5, 9, 6, 8, 2, 0, 4, 1, 3}, { 9 ,1 ,7 ,6, 5, 2, 0, 8, 0}, {6 ,0 ,3 ,7 ,0, 1, 9, 5, 2},
	{2, 5, 8, 3, 9, 4, 7, 6, 0}
};
int sedoku_table_easy_answer[10][10] = { {1, 3, 5, 4 ,6 ,9 ,2 ,7, 8},{7, 8 ,2 ,1 ,3 ,5 ,6 ,4, 9
},{4, 6, 9, 2, 7, 8, 1, 3, 5},{3, 2 ,1 ,5 ,4 ,6 ,8 ,9 ,7 },{ 8, 7, 4, 9, 1, 3, 5, 2, 6}, {5, 9, 6, 8, 2, 7, 4, 1, 3}, { 9 ,1 ,7 ,6, 5, 2, 3, 8, 4}, {6 ,4 ,3 ,7 ,8, 1, 9, 5, 2},
	{2, 5, 8, 3, 9, 4, 7, 6, 1}
};

int main() {
	//github desktop�� �̿��ؼ� push�� pull�� �غ����� hello���� �������ϴ�.
	int row, column;
	row = 9;
	column = 9;

	draw_plate(column, row);
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
			printf(" "); // ������ ĭ ��� ����
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
		printf(" "); // ������ ĭ ��� ����
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
	getchar();
	getchar();

}
