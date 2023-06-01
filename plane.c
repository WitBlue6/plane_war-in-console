#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

//全局变量
int high, width;//游戏画面大小
int position_x, position_y;//玩家位置
int enemy_x, enemy_y;//敌人位置
int buttet_x, buttet_y;//子弹位置
int IsFire;//判断开火
int round,score;//回合数



void menu()
{
	puts("*********************************");
	puts("******** 输入 1 开始游戏 ********");
	puts("**********  <飞机大战>  *********");
	puts("*********************************");

}
void Startup()//游戏数值初始化
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
void gotoxy(int x ,int y)//清屏函数
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void HideCursor()//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void Pos_Player(int width, int high,char ch)//玩家位置的打印
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
void Pos_Enemy(int width, int high, char ch)//敌机位置的打印
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
void Pos_Buttet(int width, int high, char ch)//子弹位置的打印
{
	for (int i = 0; i <high; i++)
		printf("\n");	
	for (int i = 0; i < width; i++)
		printf(" ");
	printf("^");
	if (high == -1)//让子弹消失
	{
		system("cls");
		IsFire = 0;
		buttet_y = position_y;
		buttet_x = position_x;
	}

}
void Show()//游戏画面显示
{	
	gotoxy(0, 0);
	Pos_Player(position_x, position_y, '*');//玩家
	//显示回合数
	printf("\n\n\n\n\n\n回合数:%d", round);

	gotoxy(0, 0);
	Pos_Enemy(enemy_x, enemy_y, '#');//敌机
	if (IsFire == 1)
	{
		gotoxy(0, 0);
		Pos_Buttet(buttet_x, buttet_y, '^');//子弹
		buttet_y--;
	}
	
}
void UpdateWithoutput()//无输入更新
{
	//敌机下落
	static int speed = 0;
	while (speed < 150000000)
	{
		speed++;
	}
	enemy_y++;
	system("cls");
	speed = 0;
	//敌机消失判定
	if ((buttet_x >= enemy_x -1 && buttet_x <= enemy_x +1) && enemy_y == buttet_y + 1)
	{
		score++;
		IsFire = 0;
		//敌机重新生成
		enemy_y = -5;
		enemy_x = rand() % width;
	}
	if (score % 3 == 0 && score != 0)
	{
		round++;
	}

}
void UpdateWithInput()//有输入更新
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
	printf("请输入:>");
	scanf("%d", &a);
	system("cls");
	Startup();
	while (a)
	{		
		Show();
		HideCursor();
		UpdateWithoutput();
		UpdateWithInput(); 
		//判断是否结束
		int result = IsLose();
		if (result == 1)
		{
			printf("\n游戏结束");
			printf("\n您的回合数:%d", round);
			printf("\n您的得分:%d", score);

			break;
			Sleep(10000);
			
		}
		
	}
	return 0;
}