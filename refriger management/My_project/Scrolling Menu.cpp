#include <stdio.h>
#include <mysql.h>
#pragma comment(lib,"libmysql.lib")	
#include <iostream>
#include <string>
#include <windows.h>


using namespace std;

void find_ingredients(int select);


void find_select(){
	int select = 0;
	int pointer = 0;
	string freezer[2] = { "                      -------------------------------------\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |              냉동실          ■■ |\n                      |                              ■■ |\n                      |                              ■■ |\n                      |                              ■■ |                         \n"
		, "                      -------------------------------------\n                      |                              ■■ |\n                      |                              ■■ |\n                      |                              ■■ |\n                      |                              ■■ |\n                      |              냉장실          ■■ |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      -------------------------------------                         \n" };
	system("mode  con lines=30 cols=70");
	SetConsoleTitle("냉장고를 기억해 :: 재료 찾기");
	
	while (true){

		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << endl;
		//냉장고 모양
		/*	cout << "	-------------------------------------" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|              냉동실          ■■ |" << endl;
			cout << "	|                              ■■ |" << endl;
			cout << "	|                              ■■ |" << endl;
			cout << "	|                              ■■ |" << endl;
			cout << "	-------------------------------------" << endl;
			cout << "	|                              ■■ |" << endl;
			cout << "	|                              ■■ |" << endl;
			cout << "	|                              ■■ |" << endl;
			cout << "	|                              ■■ |" << endl;
			cout << "	|              냉장실          ■■ |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	-------------------------------------" << endl;
			cout << endl; cout << endl;
			*/ //냉장고 모양

		cout << "                        냉동실과 냉장실 중 선택하세요" << endl;
		for (int i = 0; i < 2; i++)
		{

			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << freezer[i];
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << freezer[i];
			}


		}
		int select = 0; //값 넘겨줄때
		while (true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 1;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 2)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer) {
				case 0: {
							select = 0;
							find_ingredients(select);
				} break;
				case 1:
				{


				} break;
				}//end of switch

			}
		}

		//Sleep(150);
	}
}
void find_ingredients(int select){
	system("cls");
	
	
	/*char *server = "localhost";
	char *user = "root";
	char *password = "1234"; //root계정 비밀번호
	char *database = "refrigerator"; 

	int port = 3306; //포트번호
	*/
//	if (select = 0){ //냉동실
		//system("cls");
		cout << "냉동실 재료 찾기" << endl;
		cout << "여기는 ..." << endl;
		MYSQL mysql;
		MYSQL_RES *res;
		MYSQL_ROW row;
		int fields;
		int i;
		char find;
		cout << "검색할 재료 이름" << endl;
		cin >> find;
		
		mysql_init(&mysql); //mysql 초기화
		
		mysql_real_connect(&mysql, "localhost", "root", "1234", "refrigerator", NULL,NULL, 0);
		// mysql_real_connect(&mysql, host, user, passwd, dbname, unix_socket, unit client_flag);

	//	mysql_query(&mysql, "use "); //test 란 데이터베이스 사용 //mysql_select_db() 도 같은 역활
		mysql_query(&mysql, "set names euckr");
		cout << mysql_query(&mysql, "SELECT * FROM freezer where id="+find)<<"			"<<endl; // table 이란 테이블의 모든 레코드 선택
		
		res = mysql_store_result(&mysql);  // 모든 출력 결과를 서버에서 한번에 다 받아옴(데이터 많을때는 자제하라)

		fields = mysql_num_fields(res); // 필드 갯수 구함

		while (row = mysql_fetch_row(res)) // 한 행을 구함
		{
			for (i = 0; i< fields; i++)  // 모든 필드 값을 출력
			{
				cout << row[i] << "     "<<endl;
			}
		}

		mysql_free_result(res);
		mysql_close(&mysql);
	//}//end of if
	
}

int main()
{
	SetConsoleTitle("냉장고를 기억해");
	system("mode  con lines=30 cols=70");
	string Menu[5] = { "▶재료 찾기◀", "▶재료 추가◀", "▶ 재료 사용◀",
	"▶모든 재료 보기◀","▶ 메뉴 추천◀"};
	int pointer = 0;	

	
	while(true)
	{
		system("cls");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//꾸미기
		cout << endl;
		cout << "                         ■ ■ ■     ■■" << endl;
		cout << "                         ■ ■ ■    ■■■" << endl;
		cout << "                         ■ ■ ■   ■■■■" << endl;
		cout << "                         ■■■■    ■■■" << endl;
		cout << "                            ■         ■" << endl;
		cout << "                            ■         ■" << endl;
		cout << "                            ■         ■" << endl;
		cout << "                            ■         ■" << endl;

		cout << endl;

		cout << "                           냉장고를 기억해" << endl;
		cout << "             --------------------------------------------" << endl;
		
		//메뉴부분 키보드로 선택 (색 변경)
		for (int i = 0; i < (sizeof(Menu)/sizeof(string)); ++i)
		{
			
			cout << "                           ";
			if (i == pointer)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << Menu[i] << endl;
			
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				
				cout << Menu[i] << endl;
			}
		}
		
		while(true)
		{
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = 2;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == 5)
				{
					pointer = 0;
				}
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				switch (pointer)
				{
					case 0:
					{
						find_select();
						
					} break;
					case 1:
					{
						cout << "\n\n\nThis is the options...";
						
					} break;
					case 2:
					{
						return 0;
					} break;
				}
				break;
			}
		}
		
		Sleep(150);
	}
	
	return 0;
}
