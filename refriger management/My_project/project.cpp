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
void find_ingredients(); //재료 찾기
void select(); //냉동실 냉장실 선택
void add(); //재료 추가
void use();
void all_view(); //모든 재료 보기
void gotoxy(int x, int y);
void textcolor(int color_number);
void cursor(int n);
void howto(); //사용방법
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
	0 - 검정색 1 - 파랑색 2 - 초록색 3 - 옥색 4 - 빨간색 5 - 자주색 6 - 노랑색 7 - 흰색 8 - 회색
	9 - 연한 파랑색 A - 연한 초록색 B - 연한 옥색 C - 연한 빨간색 D - 연한 자주색 E - 연한 노랑색 F - 밝은 흰색
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
void cursor(int n) // 커서 보이기 & 숨기기
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
	gotoxy(27, 0); cout << "2504 김서윤" << endl;
	string choice;
	string query;
	while (true){
		textcolor(15);
		cout << "                            재료 찾을 곳" << endl;
		cout << "                    1. 냉동실            "; cout << "2. 냉장실   " << endl;
		cout << "                            >> "; cin >> choice;
		cout << endl;
		cout << "                       찾고 싶은 재료 : "; cin >> find;
		if (choice == "1" || choice == "냉동실"){
			query = "select * from freezer where f_name like '%"; query += find; query += "%';";
			string del = "delete from freezer where quantitiy =0";
			int query_stat = mysql_query(d.connection, ("select * from freezer where f_name like '%" + find + "%'").c_str());
		

			if (query_stat != 0){
				cout << "                                    오류 발생" << endl;
			}
			else{
				query = "select * from freezer where f_name = '"; query += find; query += "';";
				d.res = mysql_store_result(d.connection);

				d.sql_row = mysql_fetch_row(d.res);

				if (d.sql_row == NULL){
					cout << "                        찾는 재료가 없습니다" << endl << endl;
				}
				else{
					cout << "                               냉동실" << endl;
					cout << "        -------------------------------------------------------" << endl;
					printf("%16s %14s %14s %14s\n\n", "번호", "이름", "유통기한", "수량");
					while ((d.sql_row = mysql_fetch_row(d.res)) != NULL){

						printf("%15s %15s %15s %13s \n", d.sql_row[0], d.sql_row[1], d.sql_row[2], d.sql_row[3]);
					}
					string use;
					cout << endl;
					cout << "                    사용할 재료의 번호를 입력하세요. : "; cin >> use;
					string num;
					cout << "                     사용할 재료의 수량을 입력하세요 : "; cin >> num;
					string use_q;

					int chk = mysql_query(d.connection, ("update freezer set quantity=quantity-" + num + " where id='" + use + "'").c_str());
					if (chk == 0){
						int chk2 = mysql_query(d.connection, "delete from freezer where quantity = '0'");
						cout << "                재료를 사용하였습니다." << endl;
					}
					else{
						cout << "          오류가 발생하였습니다." << endl;
					}

				}
			}

		}
		else {
			query = "select * from refriger where r_name like '%"; query += find; query += "%';";
			string del = "delete from refriger where quantitiy =0";

			int query_stat = mysql_query(d.connection, ("select * from refriger where r_name like '%" + find + "%'").c_str());


			if (query_stat != 0){
				cout << "                                    오류 발생" << endl;
			}
			else{
				query = "select * from refriger where r_name = '"; query += find; query += "';";
				d.res = mysql_store_result(d.connection);

				d.sql_row = mysql_fetch_row(d.res);

				if (d.sql_row == NULL){
					cout << "                        찾는 재료가 없습니다" << endl << endl;
				}
				else{
					cout << "                               냉장실" << endl;
					cout << "        -------------------------------------------------------" << endl;
					printf("%16s %14s %14s %14s\n\n", "번호", "이름", "유통기한", "수량");
					while ((d.sql_row = mysql_fetch_row(d.res)) != NULL){

						printf("%15s %15s %15s %13s \n", d.sql_row[0], d.sql_row[1], d.sql_row[2], d.sql_row[3]);
					}//else
					string use;
					cout << endl;
					cout << "                    사용할 재료의 번호를 입력하세요. : "; cin >> use;
					string num;
					cout << "                     사용할 재료의 수량을 입력하세요 : "; cin >> num;
					string use_q;

					int chk = mysql_query(d.connection, ("update freezer set quantity=quantity-" + num + " where id='" + use + "'").c_str());
					if (chk == 0){
						int chk2 = mysql_query(d.connection, "delete from freezer where quantity = '0'");
						cout << "                     재료를 사용하였습니다." << endl;
					}
					else{
						cout << "          오류가 발생하였습니다." << endl;
					}//else

				}
			}
		}
	}
}
void all_view(){
	system("MODE 100,50");
	SetConsoleTitle("냉장고를 기억해 :: 모든 재료 보기");
	system("cls");
	db d;
	d.db_conn();
	string f_query, r_query;
	textcolor(8); cout << "                          2504 김서윤" << endl << endl;
	int query_stat = mysql_query(d.connection, "select * from freezer");
	//지난 날짜 삭제 쿼리
	int del = mysql_query(d.connection, ("select * from freezer where sell_by_date <= DATE(NOW()) - INTERVAL 1 DAY"));

	d.res = mysql_store_result(d.connection);


	textcolor(15);
	if (query_stat != 0){
		cout << "               냉동실에 재료가 없습니다." << endl;
	}
	else{
		cout << "                               냉동실" << endl;
		cout << "        -------------------------------------------------------" << endl;
		printf("%16s %14s %14s %14s\n\n", "번호", "이름", "유통기한", "수량");
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
		cout << "               냉장실에 재료가 없습니다." << endl;
	}
	else{
		printf("%16s %14s %14s %14s\n\n", "번호", "이름", "유통기한", "수량");
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
	SetConsoleTitle("냉장고를 기억해 :: 재료 추가");
	system("cls");
	int pointer = 0;
	db d;
	d.db_conn();
	mysql_set_character_set(d.connection, "euckr"); //한글
	string query;
	string choice;
	string f_name;
	string date;
	string quantity;
	string check;
	textcolor(8);
	cout << "                                                          2504 김서윤" << endl << endl;
	while (true){
		textcolor(15);
		 cout << "                             재료 추가할 곳" << endl;
		cout << "                      1.냉동실            "; cout << "2. 냉장실   " << endl;
		 cout << "                          >> "; cin >> choice;
		if (choice == "1" || choice =="냉동실"){
			 cout << "                            냉동실에 재료 추가"<<endl;
			 cout << "                --------------------------------------" << endl;
			 cout << "                 이름(공백 없이 입력) : "; cin>>f_name; 
			 cout << "                  유통기한(0000-00-00) : "; cin >> date; cout << endl;
			 cout << "                             수량 : "; cin >> quantity; cout << endl;
			///////////////////////////////////////////////////////////////////
			//같은 이름 존재 여부 쿼리 하기!!!!!!!!

			int chk_name = mysql_query(d.connection, ("select f_name from freezer where f_name = '" + f_name + "'").c_str());
			d.res = mysql_store_result(d.connection);
			d.sql_row = mysql_fetch_row(d.res);

			if (d.sql_row != 0){
				cout << endl;
				cout << "                        같은 이름의 재료가 존재합니다." << endl<<endl;

			}
			else{
				query = "insert into freezer(f_name, sell_by_date, quantity) values('"; query += f_name; query += "', '";
				query += date; query += "', '"; query += quantity; query += "');";


				if (mysql_query(d.connection, query.c_str())) {
					cout << "                          오류" << endl;
				}
				else{
					d.res = mysql_store_result(d.connection);
					cout << "                       추가가 완료되었습니다." << endl<<endl;

				}
			}
		}
		else if (choice == "2" || choice =="냉장실"){
			cout << "                            냉장실에 재료 추가" << endl;
			cout << "                --------------------------------------" << endl;
			cout << "                 이름(공백 없이 입력) : "; cin >> f_name;
			cout << "                  유통기한(0000-00-00) : "; cin >> date; cout << endl;
			cout << "                             수량 : "; cin >> quantity; cout << endl;
			///////////////////////////////////////////////////////////////////
			//같은 이름 존재 여부 쿼리 하기!!!!!!!!

			int chk_name = mysql_query(d.connection, ("select r_name from refriger where r_name = '" + f_name + "'").c_str());
			d.res = mysql_store_result(d.connection);
			d.sql_row = mysql_fetch_row(d.res);

			if (d.sql_row != 0){
				cout << endl;
				cout << "                        같은 이름의 재료가 존재합니다." << endl<<endl;

			}
			else{
				cout << chk_name << "else" << endl;
				query = "insert into refriger(r_name, sell_by_date, quantity) values('"; query += f_name; query += "', '";
				query += date; query += "', '"; query += quantity; query += "');";

				cout << f_name << endl;
				cout << date << endl;

				if (mysql_query(d.connection, query.c_str())) {
					cout << " 쿼리문." << endl;
					system("pause");
				}
				else{
					d.res = mysql_store_result(d.connection);
					cout << "안녕" << endl;

				}
			}
		}
		else{
			cout << endl;
			cout << "                         메뉴를 잘못 입력하셨습니다." << endl;
			cout << endl;
		}
	}
}
void random(){
	system("cls");
	cout << endl << endl << endl << endl;
	cout << "                        ■ ■ ■     ■■" << endl;
	cout << "                        ■ ■ ■    ■■■" << endl;
	cout << "                        ■ ■ ■   ■■■■" << endl;
	cout << "                        ■■■■    ■■■" << endl;
	cout << "                           ■         ■" << endl;
	cout << "                           ■         ■" << endl;
	cout << "                           ■         ■" << endl;
	cout << "                           ■         ■" << endl;
	cout << "--------------------------------------------------------------" << endl;
	cout << "                           추천 메뉴는?" << endl;
	
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
	SetConsoleTitle("냉장고를 기억해::사용 방법");
	system("mode con lines=30 cols=80");
	system("cls");
	textcolor(8);
	cout << endl << endl;
	cout << "                                  HOW TO USE" << endl;
	cout << "                        ------------------------------" << endl;
	textcolor(9);
	cout << "                             ☞냉장고를 부탁해☜" << endl;
	textcolor(15);
	cout << "                  냉장고 속의 음식들을 쉽게 관리할 수 있도록 만든 " << endl;
	cout << "                          누구에게나 필요하고 편리한 프로그램" << endl;
	cout << "           ┌────────────────────────┐" << endl;
	cout << "           │                  "; textcolor(9); cout << " ◈메뉴 소개◈                 "; textcolor(15); cout << "│" << endl;
	textcolor(15);
	cout << "           │              1. 재료 검색 & 사용               │" << endl;
	cout << "           │     사용자가 추가해놓은 냉장실, 냉동실 속의    │" << endl;
	cout << "           │             재료를 검색할 수 있는 메뉴         │" << endl;
	cout << "           │                                                │" << endl;
	cout << "           │                  2. 재료 추가                  │" << endl;
	cout << "           │      사용자가 냉장고에 추가하고싶은 음식을     │" << endl;
	cout << "           │             냉장고와 냉동실 속에 추가          │" << endl;
	cout << "           │                                                │" << endl;
	cout << "           │                3. 모든 재료 보기               │" << endl;
	cout << "           │           사용자가 등록한 모든 음식을          │" << endl;
	cout << "           │             목록으로 볼 수 있는 메뉴           │" << endl;
	cout << "           │                                                │" << endl;
	cout << "           │                   4. 메뉴 추천                 │" << endl;
	cout << "           │           사용자가 등록한 모든 음식을          │" << endl;
	cout << "           │             목록으로 볼 수 있는 메뉴           │" << endl;
	cout << "           └────────────────────────┘" << endl;
	cout << "                              아무 키나 누르세요." << endl;
	
	
	
}
void main_1(){
	SetConsoleTitle("냉장고를 기억해");
	system("mode  con lines=30 cols=70");
	system("color 0F");
	int pointer;
	textcolor(15);
	//꾸미기

	cout << endl << endl << endl << endl;
	cout << "                        ■ ■ ■     ■■" << endl;
	cout << "                        ■ ■ ■    ■■■" << endl;
	cout << "                        ■ ■ ■   ■■■■" << endl;
	cout << "                        ■■■■    ■■■" << endl;
	cout << "                           ■         ■" << endl;
	cout << "                           ■         ■" << endl;
	cout << "                           ■         ■" << endl;
	cout << "                           ■         ■" << endl;


	cout << endl;
	textcolor(15);
	cout << "             --------------------------------------------" << endl;
	textcolor(14);
	cout << "                           냉장고를 기억해" << endl;
	textcolor(15);
	cout << "             --------------------------------------------" << endl << endl;


	textcolor(8);
	cout << endl << endl << endl << endl << endl << endl << endl;
	gotoxy(25, 30); cout << "                          2504 김서윤";
	textcolor(15);
	gotoxy(27, 16); cout << "1. 재료 검색 & 사용" << endl;
	gotoxy(27, 17); cout << "2. 재료 추가" << endl;
	gotoxy(27, 18); cout << "3. 모든 재료 보기" << endl;
	gotoxy(27, 19); cout << "4. 메뉴 추천" << endl;
	gotoxy(27, 20); cout << "5. 사용 방법" << endl;

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
