#define _CRT_SECURE_NO_WARNINGS

#include "snake.h"        //引入自定义头文件


int main(void)
{
	srand(time(NULL));    //播种随机数种子。

	initSnake();          //初始化蛇
	initFood();           //初始化食物

	printf("snake 头:x=%d,y=%d\n", snake.body[0].X, snake.body[0].Y);
	printf("snake 身:x=%d,y=%d\n", snake.body[1].X, snake.body[0].Y);

	printf("food:x=%d,y=%d\n", food.X, food.Y);

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
	snake.body[1].X = HIGH / 2;

	return;

}
//食物的初始化函数
void initFood(void)
{
	food.X = rand() % WIDE;   //0-59
	food.Y = rand() % HIGH;   //0-59

	return;
}
