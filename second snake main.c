#define _CRT_SECURE_NO_WARNINGS

#include "snake.h"//引入自定义头文件

int main(void) 
{
	srand(time(NULL));    //播种随机数种子。

	initSnake();          //初始化蛇
	initFood();           //初始化食物

	initUI();             //画蛇和食物

	system("pause");
	return EXIT_SUCCESS;
}

//定义初始化蛇函数
void initSnake(void)
{
	snake.size = 2;

	snake.body[0].X = WIDE / 2;     //蛇头初始化
	snake.body[0].Y = HIGH / 2;

	snake.body[1].X = WIDE / 2 - 1;   //蛇一节身体初始化
	snake.body[1].Y = HIGH / 2;

	return;
}

//初始化界面控件
void initUI(void)
{
	COORD coord = { 0 };                 //光标移动的位子
	
	//画蛇
	for (size_t i = 0;i < snake.size;i++)
	{
		coord.X = snake.body[i].X;
		coord.Y = snake.body[i].Y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		
		if (i == 0)
			putchar('@');
		else
			putchar('*');
	}
	
	//画食物
	coord.X = food.X;
	coord.Y = food.Y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    putchar('#');

	//将光标默认位置移动至不干扰游戏的任意位置。
	coord.X = 0;
	coord.Y = HIGH + 2;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

//食物的初始化函数
void initFood(void)
{
	food.X = rand() % WIDE;   //0-59
	food.Y = rand() % HIGH;   //0-59

	return;
}


