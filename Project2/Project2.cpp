#include <mysql.h>
#include <iostream>
#include<vector>
#include<stdlib.h>
#include<utility>

using namespace std;
int q_estado;
int sedoku_table[16][2][9][9];
vector<pair<int,int>> xy;


void print_sedoku(int count_num ) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sedoku_table[count_num][1][i][j] << " ";

        }
        cout << "\n";
    }
}
void check1(bool check[], int x,int count_num) {
    for (int i = 0; i < 9; i++) {
        if (sedoku_table[count_num][1][x][i] != 0) {
            int where = sedoku_table[count_num][1][x][i] - 1;
            check[where] = true;
        }
    }

}

void check2(bool check[], int y , int count_num) {
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
void dfs(int cnt,int count_num) {

    if (istrue == true) {
        return;
    }
    if (cnt == xy.size()) {
        istrue = true;
        print_sedoku(count_num);
        return;
    }

    int x = xy[cnt].first;
    int y = xy[cnt].second;
    bool can[9] = { false,false,false,false,false,false,false,false };
    check1(can, x,count_num);

    check2(can, y,count_num);

    check3(can, x, y,count_num);


    //xy좌표로 가능한 리스트 불러온다
    for (int i = 0; i < 9; i++) {
        if (can[i] == false) {
            sedoku_table[count_num][1][x][y] = i + 1;
            dfs(cnt + 1,count_num);
            sedoku_table[count_num][1][x][y] = 0;



        }
    }
}



// db 에서 스도쿠 테이블을 꺼내오는 함수 mysql 데이터베이스가 c에 연결되진 않았을떄 사용하지마세요!
int main() {

	//db에서 스도쿠들의 소스코드를 받아오는 코드
    MYSQL* conectar;
	MYSQL_ROW fila;
	MYSQL_RES* result;
	string a;
	vector<string>  sedoku_set[16] ;
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

    
    
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 1; j++) {
			for (int p = 0; p < 9; p++) {
				for (int q = 0; q < 9; q++) {
					int num = sedoku_set[i][j][ p*9+q ] - '0';
					sedoku_table[i][j][p][q] = num;
					sedoku_table[i][1][p][q] = num;
				}
			}
		}
	}
  

    // 끝
 
   
for (int q = 0; q < 4; q++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (sedoku_table[q][1][i][j] == 0) xy.push_back(make_pair(i, j));
            }
        }
        dfs(0,q);
        xy.clear();
        vector<pair<int, int>>().swap(xy);//vector 초기화
        istrue = false;

    }
    


	


	
}
