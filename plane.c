#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

//ȫ�ֱ���
int high, width;//��Ϸ�����С
int position_x, position_y;//���λ��
int enemy_x, enemy_y;//����λ��
int buttet_x, buttet_y;//�ӵ�λ��
int IsFire;//�жϿ���
int round,score;//�غ���



void menu()
{
	puts("*********************************");
	puts("******** ���� 1 ��ʼ��Ϸ ********");
	puts("**********  <�ɻ���ս>  *********");
	puts("*********************************");

}
void Startup()//��Ϸ��ֵ��ʼ��
{
	high = 28;
	width = 30;
	position_x = width / 2;
	position_y = 2 * high / 3;
	enemy_x = width / 2;
	enemy_y = 0;
	buttet_x = position_x;
	buttet_y = position_y - 1;
	IsFire = 0;
	score = 0;
	round = 0;
	
}
void gotoxy(int x ,int y)//��������
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void HideCursor()//���ع��
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void Pos_Player(int width, int high,char ch)//���λ�õĴ�ӡ
{
	for (int i = 0; i < high; i++)
		printf("\n");
	for (int j = 0; j < width; j++)	
		printf(" ");	
	printf("%c\n", ch);
	for (int i = 0; i < width - 2; i++)
		printf(" ");
	printf("*****\n");
	for (int i = 0; i < width - 1; i++)
		printf(" ");
	printf("* *");
}
void Pos_Enemy(int width, int high, char ch)//�л�λ�õĴ�ӡ
{
	for (int i = 0; i < high - 1; i++)
		printf("\n");
	for (int i = 0; i < width - 1; i++)
		printf(" ");
	printf("# #\n");
	for (int i = 0; i < width - 1; i++)
		printf(" ");
	printf("###\n");
	for (int i = 0; i < width; i++)
		printf(" ");
	printf("#");
}
void Pos_Buttet(int width, int high, char ch)//�ӵ�λ�õĴ�ӡ
{
	for (int i = 0; i <high; i++)
		printf("\n");	
	for (int i = 0; i < width; i++)
		printf(" ");
	printf("^");
	if (high == -1)//���ӵ���ʧ
	{
		system("cls");
		IsFire = 0;
		buttet_y = position_y;
		buttet_x = position_x;
	}

}
void Show()//��Ϸ������ʾ
{	
	gotoxy(0, 0);
	Pos_Player(position_x, position_y, '*');//���
	//��ʾ�غ���
	printf("\n\n\n\n\n\n�غ���:%d", round);

	gotoxy(0, 0);
	Pos_Enemy(enemy_x, enemy_y, '#');//�л�
	if (IsFire == 1)
	{
		gotoxy(0, 0);
		Pos_Buttet(buttet_x, buttet_y, '^');//�ӵ�
		buttet_y--;
	}
	
}
void UpdateWithoutput()//���������
{
	//�л�����
	static int speed = 0;
	while (speed < 150000000)
	{
		speed++;
	}
	enemy_y++;
	system("cls");
	speed = 0;
	//�л���ʧ�ж�
	if ((buttet_x >= enemy_x -1 && buttet_x <= enemy_x +1) && enemy_y == buttet_y + 1)
	{
		score++;
		IsFire = 0;
		//�л���������
		enemy_y = -5;
		enemy_x = rand() % width;
	}
	if (score % 3 == 0 && score != 0)
	{
		round++;
	}

}
void UpdateWithInput()//���������
{
	if (_kbhit())
	{
  			char input = _getch();
			if (input == ' ')
			{
				IsFire = 1;
				buttet_x = position_x;
				buttet_y = position_y;
			}
			else if (input == 'w')
				position_y--;
			else if (input == 's')
				position_y++;				
			else if (input == 'a')
				position_x--;
			else if (input == 'd')
				position_x++;
			system("cls");
			
	}
}
int IsLose()
{
	if (enemy_y > high)
		return 1;	
	else
		return 0;
}
int main()
{
	menu();
	int a = 0;
	printf("������:>");
	scanf("%d", &a);
	system("cls");
	Startup();
	while (a)
	{		
		Show();
		HideCursor();
		UpdateWithoutput();
		UpdateWithInput(); 
		//�ж��Ƿ����
		int result = IsLose();
		if (result == 1)
		{
			printf("\n��Ϸ����");
			printf("\n���Ļغ���:%d", round);
			printf("\n���ĵ÷�:%d", score);

			break;
			Sleep(10000);
			
		}
		
	}
	return 0;
}