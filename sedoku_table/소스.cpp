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

extern int hint_count_easy = 3; //쉬움 난이도 힌트 갯수
extern int hint_count_medium = 2; // 중간 난이도 힌트 갯수
extern int hint_count_hard = 1; // 어려움 난이도 힌트 갯수
bool result = false;
int main() {
	


	while (result != true) {
		titleDraw();
		int menuCode = menuDraw();

		if (menuCode == 0) { //게임시작

			int q = maplistDraw();
			gamedraw(q);
			system("cls");
			
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

//게임 시작 전 백트래킹 관련 함수

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
		cout << "사용가능한 숫자: ";
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
		//해당코드는 확인하고 싶을때만 주석처리를 해줍니다.print_sedoku(count_num);
		return;
	}

	int x = xy[cnt].first;
	int y = xy[cnt].second;
	bool can[9] = { false,false,false,false,false,false,false,false,false };
	check1(can, x, count_num, 1);

	check2(can, y, count_num, 1);

	check3(can, x, y, count_num, 1);


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
// 끝






//게임 시작 함수
void infoDraw() {
	system("cls"); //화면 모두 지우기
	printf("게임설명\n");
	printf("스도쿠는 가로줄과 세로줄에서 겹치는 숫자 없이 1부터 9까지 입력하는 게임입니다.\n");
	printf("메인화면과 난이도 선택화면에서는 WASD로 방향을 움직입니다. 스페이스바로 선택할 수 있습니다.\n");
	printf("게임화면에서는 방향키로 방향을 움직입니다.\n");
	printf("0으로 표시된 칸에 숫자를 입력할 수 있습니다.\n");

	while (1) {
		if (keyControl() == SUBMIT) {
			sound_button_click(); //소리 재생
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
				sound_button_change(); //소리 재생
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}

		case DOWN: {
			if (y < 14) {
				sound_button_change(); //소리 재생
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			sound_button_click(); //소리 재생
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
				sound_button_change(); //소리 재생
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}
		case DOWN: {
			if (y < 9) {
				sound_button_change(); //소리 재생
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case SUBMIT: {
			sound_button_click(); //소리 재생
			return y - 6;
		}
		}
	}
}

// 끝

//게임 진행 화면 함수
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
	{
		{	
			
			int x = 45;
			int y = 2;
			printf("\n");
			gotoxy(x - 2, y);
			printf("              조작법              \n");
			printf("\n\n");
			gotoxy(x, y + 2);
			printf("숫자 변경 : 숫자 패드 1~9 선택\n");
			gotoxy(x, y + 3);
			printf("칸 이동 : 화살표 키\n");
			gotoxy(x, y + 4);
			printf("힌트 : c\n");


			if (sedoku_quiz / 5 == 0) {
				gotoxy(x, y + 6);
				printf("난이도 : 쉬움");
				gotoxy(x, y + 9);
				printf("남은 힌트 횟수 : %d", hint_count_easy);
			} else if (sedoku_quiz / 5 == 1) {
				gotoxy(x, y + 6);
				printf("난이도 : 중간");
				gotoxy(x, y + 9);
				printf("남은 힌트 횟수 : %d", hint_count_medium);
			} else {
				gotoxy(x, y + 6);
				printf("난이도 : 어려움");
				gotoxy(x, y + 9);
				printf("남은 힌트 횟수 : %d", hint_count_hard);
			}
			gotoxy(x, y + 7);
			printf("경과시간: %0.3lf\n", gametime);
			ablenum(x, y);
			gotoxy(x, y + 12);
			printf("메인 메뉴 : m");
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
	textcolor(14); //14: 노란색
	printf("\b%d", num);
	textcolor(15); //15: 흰색
	int x = 45;
	int y = 2;
	if (sedoku_quiz / 5 == 0) {
		gotoxy(x, y + 6);
		printf("난이도 : 쉬움");
		gotoxy(x, y + 9);
		printf("남은 힌트 횟수 : %d", hint_count_easy);
	}
	else if (sedoku_quiz / 5 == 1) {
		gotoxy(x, y + 6);
		printf("난이도 : 중간");
		gotoxy(x, y + 9);
		printf("남은 힌트 횟수 : %d", hint_count_medium);
	}
	else {
		gotoxy(x, y + 6);
		printf("난이도 : 어려움");
		gotoxy(x, y + 9);
		printf("남은 힌트 횟수 : %d", hint_count_hard);
	}
	gotoxy(x, y + 7);
	printf("경과시간: %0.3lf\n", gametime);
	gotoxy(x, y + 12);
	printf("메인 메뉴 : m");
	
}

void move_arrow_key(char key, int* x1, int* y1, int x_b, int y_b)
{
	switch (key)
	{
	case 72:// 위쪽(상) 방향의 화살표 키 입력
		sound_button_change(); //소리 재생
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
		sound_button_change(); //소리 재생
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
		sound_button_change(); //소리 재생
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
		sound_button_change(); //소리 재생
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
	case 48: //숫자키 0 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 0;  //해당하는 배열의 수를 0로 변경
			break;
		}
		else
			break;
	case 49: //숫자키 1 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 1;  //해당하는 배열의 수를 1로 변경
			break;
		}
		else
			break;
	case 50: //숫자키 2 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 2;  //해당하는 배열의 수를 2로 변경
			break;
		}
		else
			break;
	case 51: //숫자키 3 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 3;  //해당하는 배열의 수를 3로 변경
			break;
		}
		else
			break;
	case 52: //숫자키 4 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 4;  //해당하는 배열의 수를 4로 변경
			break;
		}
		else
			break;
	case 53: //숫자키 5 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 5;  //해당하는 배열의 수를 5로 변경
			break;
		}
		else
			break;
	case 54: //숫자키 6 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 6;  //해당하는 배열의 수를 6로 변경
			break;
		}
		else
			break;
	case 55: //숫자키 7 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 7;  //해당하는 배열의 수를 7로 변경
			break;
		}
		else
			break;
	case 56: //숫자키 8 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 8;  //해당하는 배열의 수를 8로 변경
			break;
		}
		else
			break;
	case 57: //숫자키 9 입력
		sound_button_change2(); //소리 재생
		if (sedoku_table[sedoku_quiz][sedoku_default][numy][numx] == 0) //배열의 수가 0일 경우
		{
			sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = 9;  //해당하는 배열의 수를 9로 변경
			break;
		}
		else
			break;

	case 99: //영어 c 버튼 입력
		if (sedoku_quiz /5 == 0 ) //난이도 쉬움일 경우
		{
			sound_button_change2(); //소리 재생
			if (hint_count_easy == 0)
				break;
			else if (sedoku_table[sedoku_quiz][sedoku_change][numy][numx] != sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]) //배열의 수가 정답이 아닐 경우
			{
				sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]; //해당하는 배열의 수를 정답으로 변경
				hint_count_easy = hint_count_easy - 1; //힌트 갯수 차감
				break;
			}
			else
				break;
		}
		if (sedoku_quiz/5 == 1) //난이도 중간일 경우
		{
			sound_button_change2(); //소리 재생
			if (hint_count_medium == 0)
				break;
			else if (sedoku_table[sedoku_quiz][sedoku_change][numy][numx] != sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]) //배열의 수가 정답이 아닐 경우
			{
				sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]; //해당하는 배열의 수를 정답으로 변경
				hint_count_medium = hint_count_medium - 1; //힌트 갯수 차감
				break;
			}
			else
				break;
		}
		if (sedoku_quiz / 5 == 2) //난이도 어려움일 경우
		{
			sound_button_change2(); //소리 재생
			if (hint_count_hard == 0)
				break;
			else if (sedoku_table[sedoku_quiz][sedoku_change][numy][numx] != sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]) //배열의 수가 정답이 아닐 경우
			{
				sedoku_table[sedoku_quiz][sedoku_change][numy][numx] = sedoku_table[sedoku_quiz][sedoku_answer][numy][numx]; //해당하는 배열의 수를 정답으로 변경
				hint_count_hard = hint_count_hard - 1; //힌트 갯수 차감
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
				sound_button_click(); //소리 재생
				return;
			}
		}
		system("cls");
		*sedokuhint[n] = hintcount[n];
		timeend = clock();
		result = false;
		timeresult = (double)(gametime) / CLOCKS_PER_SEC;
		sound_success(); //성공 소리 재생
		printf("경과시간: %0.3lf\n", gametime);
		printf("스도쿠를 성공하셨습니다\n");
		printf("아무키나 입력하여 메뉴화면으로 돌아가십시요");
		Sleep(1000);
		getchar();
		sound_button_click(); //소리 재생
	}
	else {
		sound_success(); //성공 소리 재생
		system("cls");
		cout << "더 풀 문제가  없습니다. 다른 문제를 선택하세요";
		getchar();
		system("cls");
		
	}
	

}

//끝
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