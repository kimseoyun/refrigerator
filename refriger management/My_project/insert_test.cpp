#pragma comment(lib, "libmySQL.lib")
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <string>
//MySQL 관련 헤더파일
#include <my_global.h>
#include <mysql.h>
using namespace std;
class db{
public:

	MYSQL       *connection = NULL, conn;
	MYSQL_RES   *sql_result;
	MYSQL_ROW   sql_row;
	int query_stat;
	void db_conn(){
		mysql_init(&conn);
		mysql_set_character_set(&conn, "euckr");

		connection = mysql_real_connect(&conn, "localhost", "root", "1234", "refrigerator", 3306, (char *)NULL, 0);

	}
};
int main(int argc, char **argv)
{
	db d;
	d.db_conn();
	string s_query;
	//쿼리문'
	string find;
	string f_name, date;
	string quantity;
	cout << "                          재료 이름 입력" << endl; cin >> f_name;
	cout << "                          유통기한 입력" << endl; cin >> date;
	cout << "                           수량 입력" << endl; cin >> quantity;
	//s_query = "insert into freezer (f_name, sell_by_date, quantity) values('"; s_query += f_name; s_query += "','"; 
	//s_query += date; s_query += "',"; s_query += quantity; s_query += ")";
	char query_2[256];
	sprintf(query_2, "INSERT into freezer(f_name,sell_by_date,quantity) values ('%s','%s',%d);", f_name, date, quantity);
	d.query_stat = mysql_query(d.connection, query);
	if (d.query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&d.conn));
		return 1;
	}
	/* send SQL query */
	//fruit 테이블 모든 자료 검색
	/*if (mysql_query(d.connection, s_query.c_str())) {
		fprintf(stderr, "%s ", mysql_error(d.connection));
		exit(1);
	}
	else{
		cout << "결과 있음" << endl;
		//총 구매 가격 계산 후 출력
		d.sql_result = mysql_use_result(d.connection);
		int num_fields = 0;
		num_fields = mysql_num_fields(d.sql_result);
		d.sql_row = mysql_fetch_row(d.sql_result);
		//데이터베이스 검색 값(row)과 수량의 곱으로 총 가격을 계산한다.
		for (int i = 0; i < num_fields; i++){
			cout << d.sql_row[i] << endl;
		}
	}
	*/
	/* close connection */
	mysql_close(d.connection);
}