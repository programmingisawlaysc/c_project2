#include <iostream>
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
	printf("hello world BaekDaeHyeon");
	printf("hello world shinwon");
	printf("hello world hyeonseo");
	printf("hello world BaekKyungMin");
	printf("hello world BaeGyoeongTae");
}