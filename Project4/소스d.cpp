#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include<vector>
#include<stdlib.h>
#include<utility>
#include<string>
#include <time.h>
using namespace std;
/*�Լ� ����*/
int keyControl();
void init();
void titleDraw(); //���� ���� ���)
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


// ������ �迭�� ���ؼ� ���������� �����߽��ϴ�. ���������� �ִ��� ��������ʰ� ���Ŀ� ��ġ�ڽ��ϴ�.
int sedoku_table[16][3][9][9];
vector<pair<int, int>> xy;
vector<string>  sedoku_set[16];
bool isture = false;

#define X_MAX 35// ����(��) ������ �ִ밪
#define Y_MAX 18// ����(��) ������ �ִ밪
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // ����(�����̽���)


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

extern int sedoku_quiz = 0; // ������ ���̵� ���� 0 ~ 14

extern int sedoku_default = 0;
extern int sedoku_answer = 1; // ������ �ʱⰪ(0), ����(1), ���簪(2)
extern int sedoku_change = 2;

int main() {
	find_sedoku();
	srand(time(NULL));
	//github desktop�� �̿��ؼ� push�� pull�� �غ����� hello���� �������ϴ�.

	//���� ����ȭ�� - ����ȭ�� �ڵ��Ҷ��� �ּ�Ǯ���ϼ���.
	/*
	init();
	titleDraw();
	int menuCode = menuDraw();
	printf("������ �޴�: %d\n", menuCode);
	system("cls");
	CursorView(); // <- �޴��ڵ忡�� Ŀ�� ����ó�� �Ǽ� �̰ɷ� �ٽ� Ŀ�� ��Ÿ����
	*/
	// ���� �����ϸ� - �ڵ��Ҷ��� ��ǥ �ּ�Ǯ���ϼ���
	char key;
	int x = 3, y = 2;


	while (1) {
		titleDraw();
		int menuCode = menuDraw();

		if (menuCode == 0) { //���ӽ���

			int n = maplistDraw();
			system("cls");
			if (n == 0) {
				//����
				printf("���� ������\n");
				sedoku_quiz = rand() % 5;
				system("cls");

				while (1) {

					draw_plate(9, 9);
					gotoxy(49, 10);
					printf("%d %d", x, y);
					gotoxy(x, y);
					key = _getch();
					move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
					Sleep(10);
					system("cls");

				}
				Sleep(1000);
			}
			else if (n == 1) {
				//����
				printf("�߰� ������\n");
				sedoku_quiz = rand() % 5 + 5;

				system("cls");

				while (1) {

					draw_plate(9, 9);
					gotoxy(49, 10);
					printf("%d %d", x, y);
					gotoxy(x, y);
					key = _getch();
					move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
					Sleep(10);
					system("cls");

				}
				Sleep(1000);
			}
			else if (n == 2) {
				//����
				printf("����� ������\n");
				sedoku_quiz = rand() % 5 + 10;

				system("cls");

				while (1) {

					draw_plate(9, 9);
					gotoxy(49, 10);
					printf("%d %d", x, y);
					gotoxy(x, y);
					key = _getch();
					move_arrow_key(key, &x, &y, X_MAX, Y_MAX);
					Sleep(10);
					system("cls");

				}
				Sleep(1000);
			}
		}
		else if (menuCode == 1) {
			infoDraw(); //��������
		}
		else if (menuCode == 2) {
			return 0; //����
		}
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
			textcolor(15);
			printf(" "); // ������ ĭ ������ ����
			if (sedoku_table[sedoku_quiz][sedoku_default][i][j] == 0) { //������ ���� 0�̸� ������ ���������
				textcolor(14); //14: �����
				printf("%d", sedoku_table[sedoku_quiz][sedoku_change][i][j]); // sedoku_table �迭 ���� ���
			}
			else {
				textcolor(15); //15: ���
				printf("%d", sedoku_table[sedoku_quiz][sedoku_change][i][j]); // sedoku_table �迭 ���� ���
			}
			textcolor(15);
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
		textcolor(15);
		printf(" "); // ������ ĭ ������ ����
		if (sedoku_table[sedoku_quiz][sedoku_default][i][j] == 0) { //������ ���� 0�̸� ������ ���������
			textcolor(14); //14: �����
			printf("%d", sedoku_table[sedoku_quiz][sedoku_change][i][j]); // sedoku_table �迭 ���� ���
		}
		else {
			textcolor(15); //15: ���
			printf("%d", sedoku_table[sedoku_quiz][sedoku_change][i][j]); // sedoku_table �迭 ���� ���
		}
		textcolor(15);
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
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 1;  //�ش��ϴ� �迭�� ���� 1�� ����
			break;
		}
		else
			break;
	case 50:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 2;  //�ش��ϴ� �迭�� ���� 2�� ����
			break;
		}
		else
			break;
	case 51:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 3;  //�ش��ϴ� �迭�� ���� 3�� ����
			break;
		}
		else
			break;
	case 52:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 4;  //�ش��ϴ� �迭�� ���� 4�� ����
			break;
		}
		else
			break;
	case 53:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 5;  //�ش��ϴ� �迭�� ���� 5�� ����
			break;
		}
		else
			break;
	case 54:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 6;  //�ش��ϴ� �迭�� ���� 6�� ����
			break;
		}
		else
			break;
	case 55:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 7;  //�ش��ϴ� �迭�� ���� 7�� ����
			break;
		}
		else
			break;
	case 56:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 8;  //�ش��ϴ� �迭�� ���� 8�� ����
			break;
		}
		else
			break;
	case 57:
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 9;  //�ش��ϴ� �迭�� ���� 9�� ����
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
		//�ش��ڵ�� Ȯ���ϰ� �������� �ּ�ó���� ���ݴϴ�.print_sedoku(count_num);
		return;
	}

	int x = xy[cnt].first;
	int y = xy[cnt].second;
	bool can[9] = { false,false,false,false,false,false,false,false };
	check1(can, x, count_num);

	check2(can, y, count_num);

	check3(can, x, y, count_num);


	//xy��ǥ�� ������ ����Ʈ �ҷ��´�
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

	sedoku_set[0].push_back("004130020900000600802509000001003000000890406400000093730904162150000800240718059");
	sedoku_set[1].push_back("106009000000300010290000406607095843532018690040073000005900301020006000000504760");
	sedoku_set[2].push_back("000200086100890007030000912345170600090052000706943058000004005007519043004306000");
	sedoku_set[3].push_back("070000060000067105005029304009076501700000000310045820038001090507693018090480050");
	sedoku_set[4].push_back("006157800010390005053080090827009000649800000030070900000400308074920501180060029");
	sedoku_set[5].push_back("900000083000082409870940000030097005500020000600105890056000300000356947000000500");
	sedoku_set[6].push_back("910056003000800000260000500009420008806000030540080000004100805000090070380700029");
	sedoku_set[7].push_back("840000102502008000000032084050790000384000759090000000900050308028007960000009001");
	sedoku_set[8].push_back("030000694740000010006080000070400209500000070020700001004002100250001046003049008");
	sedoku_set[9].push_back("130400000500060030000000209407013060000204190900080002800340900300006801000001003");
	sedoku_set[10].push_back("003600000900800207000000000040150830070004000820000000090005308500760400000000560");
	sedoku_set[11].push_back("000000030105000040300209650753000010000063000090500000000095000031720004049010500");
	sedoku_set[12].push_back("900402500000901000050000007400020080002000734508006000000800020700000001090260000");
	sedoku_set[13].push_back("308900010029005700061000020030400157045010000006003200000500000200000030600007009");
	sedoku_set[14].push_back("000201000002005009050080006000000000300050090080070004040090070020000010008710030");


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
	// ��

	//����ҵ鿡 ���� ��Ʈ��ŷ���� ������ �װ��� �޾ƿ´� �κ�
	for (int q = 0; q < 15; q++) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (sedoku_table[q][1][i][j] == 0) xy.push_back(make_pair(i, j));
			}
		}
		dfs(0, q);
		xy.clear();
		vector<pair<int, int>>().swap(xy);//vector �ʱ�ȭ
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

void init() // �ܼ� â ���� �Լ� 
{
	system("mode con cols=100 lines=20 | title �� �� �� ��"); // â ����

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // Ŀ�� ���� ó��
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
void CursorView()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // Ŀ�� ���� ó��
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = true;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void textcolor(int color_number) // ���� ���� ���� �Ǽ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void titleDraw()
{
	printf("\n\n\n\n");
	printf("   ����     �����   ����       ���     ��   ��   ��    ��     \n");
	printf("  ��          ��         ��    ��   ��    ��   �� ��     ��    ��     \n");
	printf("   ����     �����   ��    ��   ��    ��   ���      ��    ��     \n");
	printf("         ��   ��         ��    ��   ��    ��   �� ��     ��    ��     \n");
	printf("   ����     �����    ����      ���     ��   ��     ���       \n");
}

int menuDraw()
{
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y); // -2 �� ������ > �� ����ؾ��ϱ� ������
	printf("> ���ӽ���");
	gotoxy(x, y + 1);
	printf("��������");
	gotoxy(x, y + 2);
	printf("����");

	while (1)
	{ // ���ѹݺ�
		int n = keyControl();
		switch (n) {
		case UP: { //�Է��� Ű�� ���� UP�� ��� (w)
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
	printf("                     [ �� ���� ]\n\n");

	gotoxy(x - 2, y);
	printf("> ����");
	gotoxy(x, y + 1);
	printf("�߰�");
	gotoxy(x, y + 2);
	printf("�����");
	gotoxy(x, y + 3);
	printf("�ڷ�");

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
	system("cls"); //ȭ�� ��� �����
	printf("���Ӽ���");

	while (1) {
		if (keyControl() == SUBMIT) {
			break;
		}
	}
}