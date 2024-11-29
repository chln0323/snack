#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define WIDE 60          //宽度
#define HIGH 20          //高度

//一个身体的对象
struct BODY {
	int X;
	int Y;
};
//定义蛇对象
struct snake {
	struct BODY body[WIDE*HIGH];    //蛇身。 body[0]---蛇头
	int size;             //蛇的大小
};

int main(void)
{
	for (size_t i = 0;i < 20;i++)
	{
		for (size_t j = 0;j < 60;j++)
		{
			printf("*");
		}
		printf("\n");
	}
	
	system("pause");
	return EXIT_SUCCESS;
}
