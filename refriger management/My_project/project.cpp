#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include <mysql.h>
#include <iostream>
#include<conio.h>
#include <string>
#include <windows.h>
#pragma comment(lib,"libmysql.lib")	

#pragma comment(linker, "/HEAP:4000000000")

using namespace std;

void main_1();
void find_ingredients(); //��� ã��
void select(); //�õ��� ����� ����
void add(); //��� �߰�
void use();
void all_view(); //��� ��� ����
void gotoxy(int x, int y);
void textcolor(int color_number);
void cursor(int n);
void howto(); //�����
void random();
class db{
public:
	MYSQL       *connection = NULL, conn;
	MYSQL_RES   *res;
	MYSQL_ROW   sql_row;

	void db_conn(){

		mysql_init(&conn);
		mysql_set_character_set(&conn, "euckr");

		connection = mysql_real_connect(&conn, "localhost", "root", "1234", "refrigerator", 3306, (char *)NULL, 0);
	}
}; //db
void textcolor(int color_number)
{
	/*
	0 - ������ 1 - �Ķ��� 2 - �ʷϻ� 3 - ���� 4 - ������ 5 - ���ֻ� 6 - ����� 7 - ��� 8 - ȸ��
	9 - ���� �Ķ��� A - ���� �ʷϻ� B - ���� ���� C - ���� ������ D - ���� ���ֻ� E - ���� ����� F - ���� ���
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void cursor(int n) // Ŀ�� ���̱� & �����
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = n;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void find_ingredients(){
	system("MODE 70,50");
	system("cls");
	db d;
	d.db_conn();
	string find;
	textcolor(8);
	string s_query;
	mysql_set_character_set(&d.conn, "euckr");
	gotoxy(27, 0); cout << "2504 �輭��" << endl;
	string choice;
	string query;
	while (true){
		textcolor(15);
		cout << "                            ��� ã�� ��" << endl;
		cout << "                    1. �õ���            "; cout << "2. �����   " << endl;
		cout << "                            >> "; cin >> choice;
		cout << endl;
		cout << "                       ã�� ���� ��� : "; cin >> find;
		if (choice == "1" || choice == "�õ���"){
			query = "select * from freezer where f_name like '%"; query += find; query += "%';";
			string del = "delete from freezer where quantitiy =0";
			int query_stat = mysql_query(d.connection, ("select * from freezer where f_name like '%" + find + "%'").c_str());
		

			if (query_stat != 0){
				cout << "                                    ���� �߻�" << endl;
			}
			else{
				query = "select * from freezer where f_name = '"; query += find; query += "';";
				d.res = mysql_store_result(d.connection);

				d.sql_row = mysql_fetch_row(d.res);

				if (d.sql_row == NULL){
					cout << "                        ã�� ��ᰡ �����ϴ�" << endl << endl;
				}
				else{
					cout << "                               �õ���" << endl;
					cout << "        -------------------------------------------------------" << endl;
					printf("%16s %14s %14s %14s\n\n", "��ȣ", "�̸�", "�������", "����");
					while ((d.sql_row = mysql_fetch_row(d.res)) != NULL){

						printf("%15s %15s %15s %13s \n", d.sql_row[0], d.sql_row[1], d.sql_row[2], d.sql_row[3]);
					}
					string use;
					cout << endl;
					cout << "                    ����� ����� ��ȣ�� �Է��ϼ���. : "; cin >> use;
					string num;
					cout << "                     ����� ����� ������ �Է��ϼ��� : "; cin >> num;
					string use_q;

					int chk = mysql_query(d.connection, ("update freezer set quantity=quantity-" + num + " where id='" + use + "'").c_str());
					if (chk == 0){
						int chk2 = mysql_query(d.connection, "delete from freezer where quantity = '0'");
						cout << "                ��Ḧ ����Ͽ����ϴ�." << endl;
					}
					else{
						cout << "          ������ �߻��Ͽ����ϴ�." << endl;
					}

				}
			}

		}
		else {
			query = "select * from refriger where r_name like '%"; query += find; query += "%';";
			string del = "delete from refriger where quantitiy =0";

			int query_stat = mysql_query(d.connection, ("select * from refriger where r_name like '%" + find + "%'").c_str());


			if (query_stat != 0){
				cout << "                                    ���� �߻�" << endl;
			}
			else{
				query = "select * from refriger where r_name = '"; query += find; query += "';";
				d.res = mysql_store_result(d.connection);

				d.sql_row = mysql_fetch_row(d.res);

				if (d.sql_row == NULL){
					cout << "                        ã�� ��ᰡ �����ϴ�" << endl << endl;
				}
				else{
					cout << "                               �����" << endl;
					cout << "        -------------------------------------------------------" << endl;
					printf("%16s %14s %14s %14s\n\n", "��ȣ", "�̸�", "�������", "����");
					while ((d.sql_row = mysql_fetch_row(d.res)) != NULL){

						printf("%15s %15s %15s %13s \n", d.sql_row[0], d.sql_row[1], d.sql_row[2], d.sql_row[3]);
					}//else
					string use;
					cout << endl;
					cout << "                    ����� ����� ��ȣ�� �Է��ϼ���. : "; cin >> use;
					string num;
					cout << "                     ����� ����� ������ �Է��ϼ��� : "; cin >> num;
					string use_q;

					int chk = mysql_query(d.connection, ("update freezer set quantity=quantity-" + num + " where id='" + use + "'").c_str());
					if (chk == 0){
						int chk2 = mysql_query(d.connection, "delete from freezer where quantity = '0'");
						cout << "                     ��Ḧ ����Ͽ����ϴ�." << endl;
					}
					else{
						cout << "          ������ �߻��Ͽ����ϴ�." << endl;
					}//else

				}
			}
		}
	}
}
void all_view(){
	system("MODE 100,50");
	SetConsoleTitle("����� ����� :: ��� ��� ����");
	system("cls");
	db d;
	d.db_conn();
	string f_query, r_query;
	textcolor(8); cout << "                          2504 �輭��" << endl << endl;
	int query_stat = mysql_query(d.connection, "select * from freezer");
	//���� ��¥ ���� ����
	int del = mysql_query(d.connection, ("select * from freezer where sell_by_date <= DATE(NOW()) - INTERVAL 1 DAY"));

	d.res = mysql_store_result(d.connection);


	textcolor(15);
	if (query_stat != 0){
		cout << "               �õ��ǿ� ��ᰡ �����ϴ�." << endl;
	}
	else{
		cout << "                               �õ���" << endl;
		cout << "        -------------------------------------------------------" << endl;
		printf("%16s %14s %14s %14s\n\n", "��ȣ", "�̸�", "�������", "����");
		f_query = "select * from freezer";
		d.res = mysql_store_result(d.connection);
		while ((d.sql_row = mysql_fetch_row(d.res)) != NULL){
			printf("%15s %15s %15s %13s \n", d.sql_row[0], d.sql_row[1], d.sql_row[2], d.sql_row[3]);
		}
	}

	cout << endl;
	query_stat = mysql_query(d.connection, "select * from refriger");
	del = mysql_query(d.connection, ("select * from refriger where sell_by_date  <= DATE(NOW()) - INTERVAL 1 DAY"));

	d.res = mysql_store_result(d.connection);

	if (query_stat != 0){
		cout << "               ����ǿ� ��ᰡ �����ϴ�." << endl;
	}
	else{
		printf("%16s %14s %14s %14s\n\n", "��ȣ", "�̸�", "�������", "����");
		r_query = "select * from refriger";
		d.res = mysql_store_result(d.connection);
		while ((d.sql_row = mysql_fetch_row(d.res)) != NULL){
			printf("%15s %15s %15s %13s \n", d.sql_row[0], d.sql_row[1], d.sql_row[2], d.sql_row[3]);
		}

	}
	mysql_free_result(d.res);

}

void add(){
	cursor(1);
	SetConsoleTitle("����� ����� :: ��� �߰�");
	system("cls");
	int pointer = 0;
	db d;
	d.db_conn();
	mysql_set_character_set(d.connection, "euckr"); //�ѱ�
	string query;
	string choice;
	string f_name;
	string date;
	string quantity;
	string check;
	textcolor(8);
	cout << "                                                          2504 �輭��" << endl << endl;
	while (true){
		textcolor(15);
		 cout << "                             ��� �߰��� ��" << endl;
		cout << "                      1.�õ���            "; cout << "2. �����   " << endl;
		 cout << "                          >> "; cin >> choice;
		if (choice == "1" || choice =="�õ���"){
			 cout << "                            �õ��ǿ� ��� �߰�"<<endl;
			 cout << "                --------------------------------------" << endl;
			 cout << "                 �̸�(���� ���� �Է�) : "; cin>>f_name; 
			 cout << "                  �������(0000-00-00) : "; cin >> date; cout << endl;
			 cout << "                             ���� : "; cin >> quantity; cout << endl;
			///////////////////////////////////////////////////////////////////
			//���� �̸� ���� ���� ���� �ϱ�!!!!!!!!

			int chk_name = mysql_query(d.connection, ("select f_name from freezer where f_name = '" + f_name + "'").c_str());
			d.res = mysql_store_result(d.connection);
			d.sql_row = mysql_fetch_row(d.res);

			if (d.sql_row != 0){
				cout << endl;
				cout << "                        ���� �̸��� ��ᰡ �����մϴ�." << endl<<endl;

			}
			else{
				query = "insert into freezer(f_name, sell_by_date, quantity) values('"; query += f_name; query += "', '";
				query += date; query += "', '"; query += quantity; query += "');";


				if (mysql_query(d.connection, query.c_str())) {
					cout << "                          ����" << endl;
				}
				else{
					d.res = mysql_store_result(d.connection);
					cout << "                       �߰��� �Ϸ�Ǿ����ϴ�." << endl<<endl;

				}
			}
		}
		else if (choice == "2" || choice =="�����"){
			cout << "                            ����ǿ� ��� �߰�" << endl;
			cout << "                --------------------------------------" << endl;
			cout << "                 �̸�(���� ���� �Է�) : "; cin >> f_name;
			cout << "                  �������(0000-00-00) : "; cin >> date; cout << endl;
			cout << "                             ���� : "; cin >> quantity; cout << endl;
			///////////////////////////////////////////////////////////////////
			//���� �̸� ���� ���� ���� �ϱ�!!!!!!!!

			int chk_name = mysql_query(d.connection, ("select r_name from refriger where r_name = '" + f_name + "'").c_str());
			d.res = mysql_store_result(d.connection);
			d.sql_row = mysql_fetch_row(d.res);

			if (d.sql_row != 0){
				cout << endl;
				cout << "                        ���� �̸��� ��ᰡ �����մϴ�." << endl<<endl;

			}
			else{
				cout << chk_name << "else" << endl;
				query = "insert into refriger(r_name, sell_by_date, quantity) values('"; query += f_name; query += "', '";
				query += date; query += "', '"; query += quantity; query += "');";

				cout << f_name << endl;
				cout << date << endl;

				if (mysql_query(d.connection, query.c_str())) {
					cout << " ������." << endl;
					system("pause");
				}
				else{
					d.res = mysql_store_result(d.connection);
					cout << "�ȳ�" << endl;

				}
			}
		}
		else{
			cout << endl;
			cout << "                         �޴��� �߸� �Է��ϼ̽��ϴ�." << endl;
			cout << endl;
		}
	}
}
void random(){
	system("cls");
	cout << endl << endl << endl << endl;
	cout << "                        �� �� ��     ���" << endl;
	cout << "                        �� �� ��    ����" << endl;
	cout << "                        �� �� ��   �����" << endl;
	cout << "                        �����    ����" << endl;
	cout << "                           ��         ��" << endl;
	cout << "                           ��         ��" << endl;
	cout << "                           ��         ��" << endl;
	cout << "                           ��         ��" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "                           ��õ �޴���?" << endl;
	
	srand(time(NULL));
	int num;

	num = (rand()%10)+1;
	cout << num << endl;
	db d;
	string str = to_string(num);
	string query = "select menu_name from random where id = '" + str + "'";
	int chk_name = mysql_query(d.connection, query.c_str());
	
	d.res = mysql_store_result(d.connection);
	d.sql_row = mysql_fetch_row(d.res);
	while ((d.sql_row = mysql_fetch_row(d.res)) != NULL){
		printf("%15s \n", d.sql_row[0]);
	}
}
void howto(){
	SetConsoleTitle("����� �����::��� ���");
	system("mode con lines=30 cols=80");
	system("cls");
	textcolor(8);
	cout << endl << endl;
	cout << "                                  HOW TO USE" << endl;
	cout << "                        ------------------------------" << endl;
	textcolor(9);
	cout << "                             �ѳ���� ��Ź�آ�" << endl;
	textcolor(15);
	cout << "                  ����� ���� ���ĵ��� ���� ������ �� �ֵ��� ���� " << endl;
	cout << "                          �������Գ� �ʿ��ϰ� ���� ���α׷�" << endl;
	cout << "           ����������������������������������������������������" << endl;
	cout << "           ��                  "; textcolor(9); cout << " �¸޴� �Ұ���                 "; textcolor(15); cout << "��" << endl;
	textcolor(15);
	cout << "           ��              1. ��� �˻� & ���               ��" << endl;
	cout << "           ��     ����ڰ� �߰��س��� �����, �õ��� ����    ��" << endl;
	cout << "           ��             ��Ḧ �˻��� �� �ִ� �޴�         ��" << endl;
	cout << "           ��                                                ��" << endl;
	cout << "           ��                  2. ��� �߰�                  ��" << endl;
	cout << "           ��      ����ڰ� ����� �߰��ϰ���� ������     ��" << endl;
	cout << "           ��             ������ �õ��� �ӿ� �߰�          ��" << endl;
	cout << "           ��                                                ��" << endl;
	cout << "           ��                3. ��� ��� ����               ��" << endl;
	cout << "           ��           ����ڰ� ����� ��� ������          ��" << endl;
	cout << "           ��             ������� �� �� �ִ� �޴�           ��" << endl;
	cout << "           ��                                                ��" << endl;
	cout << "           ��                   4. �޴� ��õ                 ��" << endl;
	cout << "           ��           ����ڰ� ����� ��� ������          ��" << endl;
	cout << "           ��             ������� �� �� �ִ� �޴�           ��" << endl;
	cout << "           ����������������������������������������������������" << endl;
	cout << "                              �ƹ� Ű�� ��������." << endl;
	
	
	
}
void main_1(){
	SetConsoleTitle("����� �����");
	system("mode  con lines=30 cols=70");
	system("color 0F");
	int pointer;
	textcolor(15);
	//�ٹ̱�

	cout << endl << endl << endl << endl;
	cout << "                        �� �� ��     ���" << endl;
	cout << "                        �� �� ��    ����" << endl;
	cout << "                        �� �� ��   �����" << endl;
	cout << "                        �����    ����" << endl;
	cout << "                           ��         ��" << endl;
	cout << "                           ��         ��" << endl;
	cout << "                           ��         ��" << endl;
	cout << "                           ��         ��" << endl;


	cout << endl;
	textcolor(15);
	cout << "             --------------------------------------------" << endl;
	textcolor(14);
	cout << "                           ����� �����" << endl;
	textcolor(15);
	cout << "             --------------------------------------------" << endl << endl;


	textcolor(8);
	cout << endl << endl << endl << endl << endl << endl << endl;
	gotoxy(25, 30); cout << "                          2504 �輭��";
	textcolor(15);
	gotoxy(27, 16); cout << "1. ��� �˻� & ���" << endl;
	gotoxy(27, 17); cout << "2. ��� �߰�" << endl;
	gotoxy(27, 18); cout << "3. ��� ��� ����" << endl;
	gotoxy(27, 19); cout << "4. �޴� ��õ" << endl;
	gotoxy(27, 20); cout << "5. ��� ���" << endl;

	cursor(1);  gotoxy(30, 22); cout << ">> "; cin >> pointer;
	switch (pointer)
	{
	case 1:
	{
			  find_ingredients();

	} break;
	case 2:
	{
			  add();

	} break;
	case 3:
	{
			  all_view();
	} break;
	case 4: {
				random();
	}break;
	case 5:
	{
			  howto();
			  
			  
	}break;


	}



}
int main()
{
	main_1();
	
	return 0;
}
