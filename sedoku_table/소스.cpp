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
#include <mmsystem.h>
#include <tchar.h>
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
void buffer_print(int sedoku_table[16][3][9][9]);
void buff_sedoku_print(int j, int i, int num);
void move_arrow_key(char chr, int* x, int* y, int x_b, int y_b);
void gotoxy(int x, int y);
void print_sedoku(int count_num);
void check1(bool check[], int x, int count_num, int cnt);
void check2(bool check[], int y, int count_num, int cnt);
void check3(bool check[], int x, int y, int count_num, int cnt);
void dfs(int cnt, int count_num);
void find_sedoku();
void cheat(int num);
void ablenum(int x, int y);
void gamedraw(int n);
void sound_button_change();
void sound_button_change2();
void sound_button_click();
void sound_success();


clock_t timestart, timeend;
double timeresult;
double gametime;
enum {
	BLAK,
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKY_BLUE,
	DARK_RED,
	DARK_VIOLET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKY_BLUE,
	RED,
	VIOLET,
	YELLOW,
	WHITE,
};

int Out_Color = BLUE;
int In_Color = DARK_GRAY;
int G_Color = GREEN;
int W_Color = WHITE;

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int sedoku_table[16][3][9][9];
int front_buffer[16][1][9][9];
vector<pair<int, int>> xy;
vector<string>  sedoku_set[16];
bool finished[15] = { false ,false, false, false, false, false, false, false, false, false, false, false, false, false, false };


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
	finished[Sedoku_quiz] = true;
	return true;

}

bool count(int sedoku_quiz) {

	int range = sedoku_quiz / 5;
	for (int i = 0; i < range + 5; i++) {
		if (finished[i] == false) {
			return false;
		}
	}
	return true;
}

// ������ �迭�� ���ؼ� ���������� �����߽��ϴ�. ���������� �ִ��� ��������ʰ� ���Ŀ� ��ġ�ڽ��ϴ�.


#define X_MAX 35// ����(��) ������ �ִ밪
#define Y_MAX 18// ����(��) ������ �ִ밪
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4 // ����(�����̽���)





extern int numx = 0; // �迭 ��ġ ����
extern int numy = 0;

extern int sedoku_quiz = 0; // ������ ���̵� ���� 0 ~ 14

extern int sedoku_default = 0;
extern int sedoku_answer = 1; // ������ �ʱⰪ(0), ����(1), ���簪(2)
extern int sedoku_change = 2;

extern int hint_count_easy = 3; //���� ���̵� ��Ʈ ����
extern int hint_count_medium = 2; // �߰� ���̵� ��Ʈ ����
extern int hint_count_hard = 1; // ����� ���̵� ��Ʈ ����
bool result = false;
int main() {
	printf("hello UniUnter")


	while (result != true) {
		titleDraw();
		int menuCode = menuDraw();

		if (menuCode == 0) { //���ӽ���

			int q = maplistDraw();
			gamedraw(q);
			system("cls");
			
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

//���� ���� �� ��Ʈ��ŷ ���� �Լ�

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void check1(bool check[], int x, int count_num, int cnt) {
	for (int i = 0; i < 9; i++) {
		if (sedoku_table[count_num][cnt][x][i] != 0) {
			int where = sedoku_table[count_num][cnt][x][i] - 1;
			check[where] = true;
		}
	}

}

void check2(bool check[], int y, int count_num, int cnt) {
	for (int i = 0; i < 9; i++) {
		if (sedoku_table[count_num][cnt][i][y] != 0) {
			int where = sedoku_table[count_num][cnt][i][y] - 1;
			if (check[where] == false) {
				check[where] = true;
			}
		}
	}
}
void check3(bool check[], int x, int y, int count_num, int cnt) {
	int xx = x / 3;
	int yy = y / 3;
	for (int i = 3 * xx; i < 3 * xx + 3; i++) {
		for (int j = 3 * yy; j < yy * 3 + 3; j++) {
			if (sedoku_table[count_num][cnt][i][j] != 0) {
				int where = sedoku_table[count_num][cnt][i][j] - 1;
				if (check[where] == false) {
					check[where] = true;
				}

			}
		}
	}

}

void ablenum(int x, int y) {
	bool canable[9] = { false, false, false, false, false, false, false, false, false };
	check1(canable, numy, sedoku_quiz, 2);
	check2(canable, numx, sedoku_quiz, 2);
	check3(canable, numy, numx, sedoku_quiz, 2);
	gotoxy(x, y + 8);
	if (sedoku_table[sedoku_quiz][0][numy][numx] == 0) {
		cout << "��밡���� ����: ";
		for (int i = 0; i < 9; i++) {

			if (canable[i] == false) {
				cout << i + 1 << ' ';
			}
		}
		cout << "                       ";
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
	bool can[9] = { false,false,false,false,false,false,false,false,false };
	check1(can, x, count_num, 1);

	check2(can, y, count_num, 1);

	check3(can, x, y, count_num, 1);


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
					front_buffer[i][0][p][q] = sedoku_table[i][2][p][q];
				}
			}
		}
	}



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
// ��






//���� ���� �Լ�
void infoDraw() {
	system("cls"); //ȭ�� ��� �����
	printf("���Ӽ���\n");
	printf("�������� �����ٰ� �����ٿ��� ��ġ�� ���� ���� 1���� 9���� �Է��ϴ� �����Դϴ�.\n");
	printf("����ȭ��� ���̵� ����ȭ�鿡���� WASD�� ������ �����Դϴ�. �����̽��ٷ� ������ �� �ֽ��ϴ�.\n");
	printf("����ȭ�鿡���� ����Ű�� ������ �����Դϴ�.\n");
	printf("0���� ǥ�õ� ĭ�� ���ڸ� �Է��� �� �ֽ��ϴ�.\n");

	while (1) {
		if (keyControl() == SUBMIT) {
			sound_button_click(); //�Ҹ� ���
			break;
		}
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
				sound_button_change(); //�Ҹ� ���
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}

		case DOWN: {
			if (y < 14) {
				sound_button_change(); //�Ҹ� ���
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			sound_button_click(); //�Ҹ� ���
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
				sound_button_change(); //�Ҹ� ���
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < 9) {
				sound_button_change(); //�Ҹ� ���
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			sound_button_click(); //�Ҹ� ���
			return y - 6;
		}
		}
	}
}

// ��

//���� ���� ȭ�� �Լ�
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
	{
		{	
			
			int x = 45;
			int y = 2;
			printf("\n");
			gotoxy(x - 2, y);
			printf("              ���۹�              \n");
			printf("\n\n");
			gotoxy(x, y + 2);
			printf("���� ���� : ���� �е� 1~9 ����\n");
			gotoxy(x, y + 3);
			printf("ĭ �̵� : ȭ��ǥ Ű\n");
			gotoxy(x, y + 4);
			printf("��Ʈ : c\n");


			if (sedoku_quiz / 5 == 0) {
				gotoxy(x, y + 6);
				printf("���̵� : ����");
				gotoxy(x, y + 9);
				printf("���� ��Ʈ Ƚ�� : %d", hint_count_easy);
			} else if (sedoku_quiz / 5 == 1) {
				gotoxy(x, y + 6);
				printf("���̵� : �߰�");
				gotoxy(x, y + 9);
				printf("���� ��Ʈ Ƚ�� : %d", hint_count_medium);
			} else {
				gotoxy(x, y + 6);
				printf("���̵� : �����");
				gotoxy(x, y + 9);
				printf("���� ��Ʈ Ƚ�� : %d", hint_count_hard);
			}
			gotoxy(x, y + 7);
			printf("����ð�: %0.3lf\n", gametime);
			ablenum(x, y);
			gotoxy(x, y + 12);
			printf("���� �޴� : m");
		}
	}
}

void buffer_print(int sedoku_table[][3][9][9]) {
	int i, j, j2, i2;
	for (i = 0, i2 = 2; i < 9; i++) {
		for (j = 0, j2 = 4; j < 9; j++)
		{
			if (front_buffer[sedoku_quiz][0][i][j] != sedoku_table[sedoku_quiz][2][i][j])
			{
				buff_sedoku_print(j2, i2, sedoku_table[sedoku_quiz][2][i][j]);
				front_buffer[sedoku_quiz][0][i][j] = sedoku_table[sedoku_quiz][2][i][j];
			}
			j2 += 4;
		}
		i2 += 2;
	}
}

void buff_sedoku_print(int j, int i, int num) {
	gotoxy(j, i);
	textcolor(14); //14: �����
	printf("\b%d", num);
	textcolor(15); //15: ���
	int x = 45;
	int y = 2;
	if (sedoku_quiz / 5 == 0) {
		gotoxy(x, y + 6);
		printf("���̵� : ����");
		gotoxy(x, y + 9);
		printf("���� ��Ʈ Ƚ�� : %d", hint_count_easy);
	}
	else if (sedoku_quiz / 5 == 1) {
		gotoxy(x, y + 6);
		printf("���̵� : �߰�");
		gotoxy(x, y + 9);
		printf("���� ��Ʈ Ƚ�� : %d", hint_count_medium);
	}
	else {
		gotoxy(x, y + 6);
		printf("���̵� : �����");
		gotoxy(x, y + 9);
		printf("���� ��Ʈ Ƚ�� : %d", hint_count_hard);
	}
	gotoxy(x, y + 7);
	printf("����ð�: %0.3lf\n", gametime);
	gotoxy(x, y + 12);
	printf("���� �޴� : m");
	
}

void move_arrow_key(char key, int* x1, int* y1, int x_b, int y_b)
{
	switch (key)
	{
	case 72:// ����(��) ������ ȭ��ǥ Ű �Է�
		sound_button_change(); //�Ҹ� ���
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
		sound_button_change(); //�Ҹ� ���
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
		sound_button_change(); //�Ҹ� ���
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
		sound_button_change(); //�Ҹ� ���
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
	case 48: //����Ű 0 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 0;  //�ش��ϴ� �迭�� ���� 0�� ����
			break;
		}
		else
			break;
	case 49: //����Ű 1 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 1;  //�ش��ϴ� �迭�� ���� 1�� ����
			break;
		}
		else
			break;
	case 50: //����Ű 2 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 2;  //�ش��ϴ� �迭�� ���� 2�� ����
			break;
		}
		else
			break;
	case 51: //����Ű 3 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 3;  //�ش��ϴ� �迭�� ���� 3�� ����
			break;
		}
		else
			break;
	case 52: //����Ű 4 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 4;  //�ش��ϴ� �迭�� ���� 4�� ����
			break;
		}
		else
			break;
	case 53: //����Ű 5 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 5;  //�ش��ϴ� �迭�� ���� 5�� ����
			break;
		}
		else
			break;
	case 54: //����Ű 6 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 6;  //�ش��ϴ� �迭�� ���� 6�� ����
			break;
		}
		else
			break;
	case 55: //����Ű 7 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 7;  //�ش��ϴ� �迭�� ���� 7�� ����
			break;
		}
		else
			break;
	case 56: //����Ű 8 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 8;  //�ش��ϴ� �迭�� ���� 8�� ����
			break;
		}
		else
			break;
	case 57: //����Ű 9 �Է�
		sound_button_change2(); //�Ҹ� ���
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //�迭�� ���� 0�� ���
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 9;  //�ش��ϴ� �迭�� ���� 9�� ����
			break;
		}
		else
			break;

	case 99: //���� c ��ư �Է�
		if (sedoku_quiz /5 == 0 ) //���̵� ������ ���
		{
			sound_button_change2(); //�Ҹ� ���
			if (hint_count_easy == 0)
				break;
			else if (sedoku_table[sedoku_quiz][sedoku_change][numy][numx] != sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]) //�迭�� ���� ������ �ƴ� ���
			{
				sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]; //�ش��ϴ� �迭�� ���� �������� ����
				hint_count_easy = hint_count_easy - 1; //��Ʈ ���� ����
				break;
			}
			else
				break;
		}
		if (sedoku_quiz/5 == 1) //���̵� �߰��� ���
		{
			sound_button_change2(); //�Ҹ� ���
			if (hint_count_medium == 0)
				break;
			else if (sedoku_table[sedoku_quiz][sedoku_change][numy][numx] != sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]) //�迭�� ���� ������ �ƴ� ���
			{
				sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]; //�ش��ϴ� �迭�� ���� �������� ����
				hint_count_medium = hint_count_medium - 1; //��Ʈ ���� ����
				break;
			}
			else
				break;
		}
		if (sedoku_quiz / 5 == 2) //���̵� ������� ���
		{
			sound_button_change2(); //�Ҹ� ���
			if (hint_count_hard == 0)
				break;
			else if (sedoku_table[sedoku_quiz][sedoku_change][numy][numx] != sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]) //�迭�� ���� ������ �ƴ� ���
			{
				sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]; //�ش��ϴ� �迭�� ���� �������� ����
				hint_count_hard = hint_count_hard - 1; //��Ʈ ���� ����
				break;
			}
			else
				break;
		}
		else
			break;
	case 90:
		if (true) {
			cheat(sedoku_quiz);
			break;

		}
		else {
			break;
		}
	default:
		return;
	}

}






void gamedraw(int n) {
	if (n == 3) {
		return;
	}

	find_sedoku();
	srand(time(NULL));
	char key;
	int xx= 3, yy= 2;
	numx = 0;
	numy = 0;
	int sedokuarr[3] = { 0,1,2 };
	int* sedokuhint[3] = { &hint_count_easy, &hint_count_medium, &hint_count_hard };
	int hintcount[3] = { 3,2,1 };
	int plate_printed = 0;
	sedoku_quiz = rand() % 5 + sedokuarr[n] * 5;
	if (count(sedoku_quiz) == false) {

		while (finished[sedoku_quiz] == true) {
			sedoku_quiz = rand() % 5  + sedokuarr[n] * 5;
		}
		system("cls");
		
		timestart = clock();
		timeend = clock();

		while (result != true) {

			timestart = clock() - timeend;
			gametime = (double)(timestart) / CLOCKS_PER_SEC;
			if (plate_printed < 3) {
				system("cls");
				draw_plate(9, 9);
				plate_printed++;
			} else {
				buffer_print(sedoku_table);
				ablenum(45,2);
			}
			gotoxy(xx, yy);
			key = _getch();
			move_arrow_key(key, &xx, &yy, X_MAX, Y_MAX);
			Sleep(10);
			result = abc(sedoku_quiz);
			timestart = clock();
			if (key == 109)
			{
				sound_button_click(); //�Ҹ� ���
				return;
			}
		}
		system("cls");
		*sedokuhint[n] = hintcount[n];
		timeend = clock();
		result = false;
		timeresult = (double)(gametime) / CLOCKS_PER_SEC;
		sound_success(); //���� �Ҹ� ���
		printf("����ð�: %0.3lf\n", gametime);
		printf("�������� �����ϼ̽��ϴ�\n");
		printf("�ƹ�Ű�� �Է��Ͽ� �޴�ȭ������ ���ư��ʽÿ�");
		Sleep(1000);
		getchar();
		sound_button_click(); //�Ҹ� ���
	}
	else {
		sound_success(); //���� �Ҹ� ���
		system("cls");
		cout << "�� Ǯ ������  �����ϴ�. �ٸ� ������ �����ϼ���";
		getchar();
		system("cls");
		
	}
	

}

//��
void cheat(int num) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			sedoku_table[num][2][i][j] = sedoku_table[num][1][i][j];
		}
	}

}

void sound_button_change() {
	PlaySound(_T("button_change.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sound_button_change2() {
	PlaySound(_T("button_change2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sound_button_click() {
	PlaySound(_T("button_click.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void sound_success() {
	PlaySound(_T("success.wav"), NULL, SND_FILENAME | SND_ASYNC);
}