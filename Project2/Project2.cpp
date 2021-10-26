/*
#include <mysql.h>
#include <iostream>
using namespace std;
int q_estado;

// db 에서 스도쿠 테이블을 꺼내오는 함수 mysql 데이터베이스가 c에 연결되진 않았을떄 사용하지마세요!
int main() {

	
	MYSQL* conectar;
	MYSQL_ROW fila;
	MYSQL_RES* result;
	string a;
	conectar = mysql_init(0);
	conectar = mysql_real_connect(conectar, "localhost", "root", "1417", "sedoku_table", 3306, NULL, 0);
	if (conectar) {
		string consulta = "select * from sedoku";
		const char* c = consulta.c_str();

		q_estado = mysql_query(conectar, c);
		if (!q_estado) {
			result = mysql_store_result(conectar);
			cout << result << "\n";
			while (fila = mysql_fetch_row(result)) {
				cout << fila[2];
				a = fila[2];
				getchar();
				

			}
			cout << a;

		}

		
	}


	
	




}
*/