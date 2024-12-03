#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <stdio.h>
#include <easyx.h>
#include <conio.h>
#include <time.h>

#define ROW 46
#define COL 64

enum Game
{
    SPACE, WALL, SNAKE, FOOD, HEAD
};

int mode = 0;
int score = 0;
ULONGLONG t1, t2;
int map[ROW][COL];
COORD snake[1024];
int SnakeSize;
char SnakeDir;

void start();
void chose();
void DrawMap();
void init();
void addfood();
void ChangeDir();
void move();

int main()
{
    initgraph(640, 480);
    start();
    outtextxy(260, 150, L"->");
    chose();
    init();
    while (1)
    {
        t2 = GetTickCount64();
        DrawMap();
        if (_kbhit())
        {
            ChangeDir();
            move();
            t2 = GetTickCount64();
            t1 = t2;
        }
        if (t2 - t1 > 50)
        {
            move();
            t1 = t2;
        }
    }
    (void)getchar();
    closegraph();
    return 0;
}

void init()
{
    srand((unsigned)time(NULL));
    setbkcolor(WHITE);
    memset(map, SPACE, sizeof(map));
    for (int i = 0; i < ROW; i++)
    {
        map[i][0] = map[i][COL - 1] = WALL;
    }
    for (int j = 1; j < COL - 1; j++)
    {
        map[0][j] = map[ROW - 1][j] = WALL;
    }
    map[3][5] = HEAD;
    map[3][4] = map[3][3] = SNAKE;
    SnakeSize = 3;
    SnakeDir = 'D';
    snake[0].X = 3;
    snake[0].Y = 5;
    snake[1].X = 3;
    snake[1].Y = 4;
    snake[2].X = 3;
    snake[2].Y = 3;
    addfood();
}

void start()
{
    setbkcolor(WHITE);
    cleardevice();
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    outtextxy(290, 80, L"功能选择:");
    outtextxy(280, 150, L"1.普通模式");
    outtextxy(280, 200, L"2.穿墙模式");
    outtextxy(280, 250, L"3.无敌模式");
    outtextxy(200, 280, L"数字键 1,2,3 选择模式，Enter键进入游戏");
    outtextxy(200, 300, L"字母键 W,S,A,D 方向键 上下左右 控制方向");
}

void chose()
{
    while (1)
    {
        switch (_getch())
        {
        case '1':
            start();
            outtextxy(260, 150, L"->");
            mode = 0;
            break;
        case '2':
            start();
            outtextxy(260, 200, L"->");
            mode = 1;
            break;
        case '3':
            start();
            outtextxy(260, 250, L"->");
            mode = 2;
            break;
        case 13:
            return;
        }
    }
}

void DrawMap()
{
    BeginBatchDraw();
    setbkcolor(WHITE);
    settextcolor(RGB(238, 0, 0));
    cleardevice();
    WCHAR arr[10];
    wsprintf(arr, L"总分：%d", score);
    outtextxy(0, 0, arr);
    for (int y = 0; y < ROW; y++)
    {
        for (int x = 0; x < COL; x++)
        {
            switch (map[y][x])
            {
            case SPACE:
                break;
            case WALL:
                setlinecolor(BLACK);
                setfillcolor(RGB(238, 233, 233));
                fillrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                break;
            case SNAKE:
                setlinecolor(RGB(0, 245, 255));
                setfillcolor(WHITE);
                fillrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                break;
            case HEAD:
                switch (rand() % 7)
                {
                case 0:
                    setfillcolor(RGB(255, 0, 0));
                    solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                    break;
                case 1:
                    setfillcolor(RGB(255, 165, 0));
                    solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                    break;
                case 2:
                    setfillcolor(RGB(255, 255, 0));
                    solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                    break;
                case 3:
                    setfillcolor(RGB(0, 255, 0));
                    solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                    break;
                case 4:
                    setfillcolor(RGB(0, 255, 255));
                    solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                    break;
                case 5:
                    setfillcolor(RGB(0, 0, 255));
                    solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                    break;
                case 6:
                    setfillcolor(RGB(160, 32, 240));
                    solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                    break;
                }
                break;
            case FOOD:
                setfillcolor(RGB(255, 0, 0));
                solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
                break;
            }
        }
    }
    EndBatchDraw();
}

void addfood()
{
    int row, col;
    do
    {
        row = rand() % (ROW - 1) + 1;
        col = rand() % (COL - 1) + 1;
    } while (map[row][col] != SPACE);
    map[row][col] = FOOD;
}

void ChangeDir()
{
    char ch = _getch();
    switch (ch)
    {
    case 'A':
    case 'a':
    case 75:
        if (SnakeDir != 'D') SnakeDir = 'A';
        break;
    case 'D':
    case 'd':
    case 77:
        if (SnakeDir != 'A') SnakeDir = 'D';
        break;
    case 'W':
    case 'w':
    case 72:
        if (SnakeDir != 'S') SnakeDir = 'W';
        break;
    case 'S':
    case 's':
    case 80:
        if (SnakeDir != 'W') SnakeDir = 'S';
        break;
    case 32:
        (void)_getch();
        break;
    }
}

void move()
{
    COORD next = { 0, 0 };
    switch (SnakeDir)
    {
    case 'A':
        next.X = snake[0].X;
        next.Y = snake[0].Y - 1;
        break;
    case 'W':
        next.X = snake[0].X - 1;
        next.Y = snake[0].Y;
        break;
    case 'D':
        next.X = snake[0].X;
        next.Y = snake[0].Y + 1;
        break;
    case 'S':
        next.X = snake[0].X + 1;
        next.Y = snake[0].Y;
        break;
    }
    switch (map[next.X][next.Y])
    {
    case SPACE:
        map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;
        for (int i = SnakeSize - 1; i > 0; i--)
        {
            snake[i] = snake[i - 1];
        }
        map[snake[0].X][snake[0].Y] = SNAKE;
        snake[0] = next;
        map[snake[0].X][snake[0].Y] = HEAD;
        break;
    case WALL:
        if (mode)
        {
            map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;
            for (int i = SnakeSize - 1; i > 0; i--)
            {
                snake[i] = snake[i - 1];
            }
            map[snake[0].X][snake[0].Y] = SNAKE;
            switch (SnakeDir)
            {
            case 'A': next.Y = COL - 2; break;
            case 'D': next.Y = 1; break;
            case 'W': next.X = ROW - 2; break;
            case 'S': next.X = 1; break;
            }
            snake[0] = next;
            map[snake[0].X][snake[0].Y] = HEAD;
        }
        else
        {
            MessageBox(GetHWnd(), L"游戏结束", L"SORRY", MB_OK);
            exit(0);
        }
        break;
    case SNAKE:
        if (mode == 2)
        {
            break;
        }
        else
        {
            MessageBox(GetHWnd(), L"游戏结束", L"SORRY", MB_OK);
            exit(0);
        }
        break;
    case FOOD:
        for (int i = SnakeSize; i > 0; i--)
        {
            snake[i] = snake[i - 1];
        }
        map[snake[0].X][snake[0].Y] = SNAKE;
        snake[0] = next;
        score++;
        SnakeSize++;
        map[snake[0].X][snake[0].Y] = HEAD;
        addfood();
        break;
    }
}
