#include <iostream>
#include <stdio.h>
#include <Windows.h>
extern void draw_check02(int column, int row);


using namespace std;
// 해당 스도쿠 테이블값들은 데이터베이스와 알고리즘 없이도 쉽게 코딩을 할수 있도록 설정해놓은 값들입니다. 해당값들을 이용하여 스도쿠 게임을 제작하세요.

int sedoku_table_easy[10][10] = { {0, 3, 5, 4 ,6 ,9 ,2 ,7, 8},{7, 8 ,2 ,1 ,0 ,5 ,6 ,0, 9
},{0, 6, 0, 2, 7, 8, 1, 3, 5},{3, 2 ,1 ,0 ,4 ,6 ,8 ,9 ,7 },{ 8, 0, 4, 9, 1, 3, 5, 0, 6}, {5, 9, 6, 8, 2, 0, 4, 1, 3}, { 9 ,1 ,7 ,6, 5, 2, 0, 8, 0}, {6 ,0 ,3 ,7 ,0, 1, 9, 5, 2},
	{2, 5, 8, 3, 9, 4, 7, 6, 0}
};
int sedoku_table_easy_answer[10][10] = { {1, 3, 5, 4 ,6 ,9 ,2 ,7, 8},{7, 8 ,2 ,1 ,3 ,5 ,6 ,4, 9
},{4, 6, 9, 2, 7, 8, 1, 3, 5},{3, 2 ,1 ,5 ,4 ,6 ,8 ,9 ,7 },{ 8, 7, 4, 9, 1, 3, 5, 2, 6}, {5, 9, 6, 8, 2, 7, 4, 1, 3}, { 9 ,1 ,7 ,6, 5, 2, 3, 8, 4}, {6 ,4 ,3 ,7 ,8, 1, 9, 5, 2},
	{2, 5, 8, 3, 9, 4, 7, 6, 1}
};

int main() {
	//github desktop을 이용해서 push와 pull을 해봤으니 hello문을 지웠습니다.
	int row, column;
	printf("확장된 바둑판 그리기\n\n");
	printf("가로와 세로의 길이를 space로\n");
	printf("분라하여 입력하고 Enter>");
	cin >> column >> row;
	draw_check02(column ,row);
	return 0;


}
void draw_check02(int c, int r)
{
	int i, j;
	unsigned char a = 0xa6;
	unsigned char b[12];
	for (i = 1; i < 12; i++)
	{
		b[i] = 0xa0 + i;
	}
	// The following code prints the first row.
	printf("%c%c", a, b[3]);
	// The following line was added to double the horizontal line
	printf("%c%c", a, b[1]);
	for (i = 0; i < c - 1; i++)
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
	for (i = 0; i < r - 1; i++)
	{
		printf("%c%c", a, b[2]);
		for (j = 0; j < c; j++)
		{
			printf(" ");
			printf("1"); //<- 내가 수정한 부분
			printf(" ");
			printf("%c%c", a, b[2]);
		}
		printf("\n");
		printf("%c%c", a, b[7]);
		for (j = 0; j < c - 1; j++)
		{
			printf("%c%c%c%c%c%c", a, b[1], a, b[1], a, b[1]);
			printf("%c%c", a, b[11]);
		}
		// printf("%c%c", a, b[1]);
		printf("%c%c%c%c%c%c", a, b[1], a, b[1], a, b[1]);
		printf("%c%c", a, b[9]);
		printf("\n");
	}
	// The following code prints the last line of the grid.
	printf("%c%c", a, b[2]);
	for (j = 0; j < c; j++)
	{
		printf(" ");
		printf("1");//<- 내가 수정한부분
		printf(" ");
		printf("%c%c", a, b[2]);
	}
	printf("\n");
	printf("%c%c", a, b[6]);
	for (i = 0; i < c - 1; i++)
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
