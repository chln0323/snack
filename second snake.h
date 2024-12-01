#define _SNAKE_H_


#include<stdio.h>
#include<string.h>
#include<#ifndef _SNAKE_H_
stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>


#define WIDE 60          //宽度
#define HIGH 20          //高度

//一个身体的对象
struct BODY {
	int X;
	int Y;
};

//定义蛇对象
struct SNAKE {
	struct BODY body[WIDE * HIGH];    //蛇身。 body[0]---蛇头
	int size;             //蛇的大小
}snake;                   //一个蛇对象

//定义食物对象
struct FOOD {
	int X;
	int Y;
}food;                    //一个食物对象

int score = 0;            //分数

//声明函数
void initSnake(void);
void initFood(void);
void initUI(void);



#endif
