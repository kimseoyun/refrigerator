#pragma comment(lib, "libmySQL.lib")
#pragma comment(lib, "ws2_32.lib")
#include <iostream>
#include <string>
//MySQL ���� �������
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
	//������'
	string find;
	string f_name, date;
	string quantity;
	cout << "                          ��� �̸� �Է�" << endl; cin >> f_name;
	cout << "                          ������� �Է�" << endl; cin >> date;
	cout << "                           ���� �Է�" << endl; cin >> quantity;
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
	//fruit ���̺� ��� �ڷ� �˻�
	/*if (mysql_query(d.connection, s_query.c_str())) {
		fprintf(stderr, "%s ", mysql_error(d.connection));
		exit(1);
	}
	else{
		cout << "��� ����" << endl;
		//�� ���� ���� ��� �� ���
		d.sql_result = mysql_use_result(d.connection);
		int num_fields = 0;
		num_fields = mysql_num_fields(d.sql_result);
		d.sql_row = mysql_fetch_row(d.sql_result);
		//�����ͺ��̽� �˻� ��(row)�� ������ ������ �� ������ ����Ѵ�.
		for (int i = 0; i < num_fields; i++){
			cout << d.sql_row[i] << endl;
		}
	}
	*/
	/* close connection */
	mysql_close(d.connection);
}