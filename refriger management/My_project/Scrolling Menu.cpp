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
	string freezer[2] = { "                      -------------------------------------\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |              �õ���          ��� |\n                      |                              ��� |\n                      |                              ��� |\n                      |                              ��� |                         \n"
		, "                      -------------------------------------\n                      |                              ��� |\n                      |                              ��� |\n                      |                              ��� |\n                      |                              ��� |\n                      |              �����          ��� |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      |                                   |\n                      -------------------------------------                         \n" };
	system("mode  con lines=30 cols=70");
	SetConsoleTitle("����� ����� :: ��� ã��");
	
	while (true){

		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << endl;
		//����� ���
		/*	cout << "	-------------------------------------" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|                                   |" << endl;
			cout << "	|              �õ���          ��� |" << endl;
			cout << "	|                              ��� |" << endl;
			cout << "	|                              ��� |" << endl;
			cout << "	|                              ��� |" << endl;
			cout << "	-------------------------------------" << endl;
			cout << "	|                              ��� |" << endl;
			cout << "	|                              ��� |" << endl;
			cout << "	|                              ��� |" << endl;
			cout << "	|                              ��� |" << endl;
			cout << "	|              �����          ��� |" << endl;
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
			*/ //����� ���

		cout << "                        �õ��ǰ� ����� �� �����ϼ���" << endl;
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
		int select = 0; //�� �Ѱ��ٶ�
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
	char *password = "1234"; //root���� ��й�ȣ
	char *database = "refrigerator"; 

	int port = 3306; //��Ʈ��ȣ
	*/
//	if (select = 0){ //�õ���
		//system("cls");
		cout << "�õ��� ��� ã��" << endl;
		cout << "����� ..." << endl;
		MYSQL mysql;
		MYSQL_RES *res;
		MYSQL_ROW row;
		int fields;
		int i;
		char find;
		cout << "�˻��� ��� �̸�" << endl;
		cin >> find;
		
		mysql_init(&mysql); //mysql �ʱ�ȭ
		
		mysql_real_connect(&mysql, "localhost", "root", "1234", "refrigerator", NULL,NULL, 0);
		// mysql_real_connect(&mysql, host, user, passwd, dbname, unix_socket, unit client_flag);

	//	mysql_query(&mysql, "use "); //test �� �����ͺ��̽� ��� //mysql_select_db() �� ���� ��Ȱ
		mysql_query(&mysql, "set names euckr");
		cout << mysql_query(&mysql, "SELECT * FROM freezer where id="+find)<<"			"<<endl; // table �̶� ���̺��� ��� ���ڵ� ����
		
		res = mysql_store_result(&mysql);  // ��� ��� ����� �������� �ѹ��� �� �޾ƿ�(������ �������� �����϶�)

		fields = mysql_num_fields(res); // �ʵ� ���� ����

		while (row = mysql_fetch_row(res)) // �� ���� ����
		{
			for (i = 0; i< fields; i++)  // ��� �ʵ� ���� ���
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
	SetConsoleTitle("����� �����");
	system("mode  con lines=30 cols=70");
	string Menu[5] = { "����� ã�⢸", "����� �߰���", "�� ��� ��뢸",
	"����� ��� ���⢸","�� �޴� ��õ��"};
	int pointer = 0;	

	
	while(true)
	{
		system("cls");
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		//�ٹ̱�
		cout << endl;
		cout << "                         �� �� ��     ���" << endl;
		cout << "                         �� �� ��    ����" << endl;
		cout << "                         �� �� ��   �����" << endl;
		cout << "                         �����    ����" << endl;
		cout << "                            ��         ��" << endl;
		cout << "                            ��         ��" << endl;
		cout << "                            ��         ��" << endl;
		cout << "                            ��         ��" << endl;

		cout << endl;

		cout << "                           ����� �����" << endl;
		cout << "             --------------------------------------------" << endl;
		
		//�޴��κ� Ű����� ���� (�� ����)
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
