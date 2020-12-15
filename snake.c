#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#include<time.h>
#pragma comment (lib,"winmm.lib")
//bool类型的定义
typedef int bool;
#define true 1
#define false 0
int sleeptime=200;
int Time=0;
//开始时间
int begtime;
//结束时间
int entime;
int a[1002];
int g_hang;
int g_lie;
//蛇的初始长度
int g_snakelen = 2;
//游戏初始分数
int g_score = 0;
//蛇最长为20个节点
#define SNAKELENGH  20
//枚举方向
enum {to_east=2,to_west=-2,to_north=-1,to_south=1};
bool food = true;
//蛇节点的数组
int snakenode[SNAKELENGH][3];
char backgroud[20][48];
//定义蛇的初始方向
int snakedir=to_west;
//背景数组
char backgroud[20][48] =
{ "■■■■■■■■■■■■■■■■■■■■■■■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■                                          ■\n",
  "■■■■■■■■■■■■■■■■■■■■■■■\n" };
//显示首页
void fristpage()
{
	printf("\n\n\n\n");
	printf("\n\n\n\n");
	printf("\t\t\t《按esc暂停游戏》\n");
	printf("\t\t\t《按F1加速，按F2减速》\n");
	printf("\t\t\t《欢迎进入贪吃蛇的世界》\n");
	printf("\t\t\t《按空格开始游戏》\n");
	printf("\t\t\t《w  a  s  d控制方向》\n");
}
//播放音乐
void playmusic()
{
	//音乐
	PlaySound("D:\\林俊杰 - 可惜没如果.wav", NULL, SND_FILENAME | SND_ASYNC);
}
//检测空格
void checkspace()
{
	char chinput;
	while (1)
	{
		chinput = _getch();
		//检测空格
		if (' ' == chinput)
		{
			break;
		}
	}
}
//停止播放音乐
void stopmusic()
{
	PlaySound(NULL, 0, 0);
}
//清空屏幕
void deleteev()
{
	system("cls");
}
//销毁蛇
void deletesnake()
{
	int i;
	for (i = 0; snakenode[i][0] != 0; i++)
	{
		//将蛇的节点用空格代替
		strncpy(&backgroud[snakenode[i][0]][snakenode[i][1]], "  ", 2);
	}
}
//文字颜色
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//屏幕背景显示
void showgroud()
{
	//调整文字显示颜色
	color(2);
		for (int i = 0; i < 20; i++)
		{
			//显示背景
			printf(backgroud[i]);
		}
}
//加速
void speedup()
{
	if (sleeptime >= 50)
	{
		//加速
		sleeptime = sleeptime - 10;
		g_score = g_score + 2;
	}
}
//减速
void speeddown()
{
	if (sleeptime < 350)
	{
		//减速
		sleeptime = sleeptime + 30;
		g_score = g_score-2;
	}
}
//显示时间
void Gettime1()
{
	begtime = clock();
}
void Gettime2()
{
	entime = clock();
}
//显示分数
void scoresnake()
{
	//获得开始时间
	Gettime1();
	COORD rd;
	rd.X = 54;
	rd.Y = 7;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf("欢迎来到贪吃蛇游戏");
	rd.X = 57;
	rd.Y = 10;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf("w.a.s.d控制方向");
	rd.X = 55;
	rd.Y = 8;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf("分数");
	rd.X = 56;
	rd.Y = 9;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印
	printf("%d",g_score);
	rd.X = 53;
	rd.Y = 6;
	//设置光标位置
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//打印时间
	//获得结束时间
	Gettime2();
	int Time = entime - begtime;
	entime = entime + Time;
	printf("Time :%dms\n", entime - begtime);

}
//随机产生食物
void foodpro()
{
	srand((unsigned int)time(NULL));
	//判断是否重新产生食物
	if (false == food)
	{
		return;
	}
	while (1)
	{
		bool Flag = true;
		//随机产生坐标
		 g_lie= rand() % 18+ 1;
		g_hang = rand() % 20 + 1;
		for (int i=0; snakenode[i][0] != 0; i++)
		{
			//遍历蛇的节点
			if (g_lie == snakenode[i][0] && g_hang == snakenode[i][1])
			{
				//设置标记
				Flag = false;
				//提高函数效率
				break;
			}
		}
		if (true == Flag)
		{
			//判断食物是否被吃
			break;
		}
	}
	//画食物
	strncpy(&backgroud[g_hang][g_lie*2], "★", 2);
	food = false;

}
//蛇长大
void snakegrow()
{
	//如果蛇头坐标和食物坐标相等
	if (g_hang==snakenode[0][0]  && 2*g_lie==snakenode[0][1] )
	{
		//蛇长大
		if (to_north == snakenode[0][2])
			//如果蛇向上运动
		{
			snakenode[g_snakelen+1][0] = snakenode[g_snakelen][0]+1;
			snakenode[g_snakelen + 1][1] = snakenode[g_snakelen][1] ;
			snakenode[g_snakelen + 1][2] = snakenode[g_snakelen][2];
		}
		else if (to_south == snakenode[0][2])
			//如果蛇向下运动
		{
			snakenode[g_snakelen + 1][0] = snakenode[g_snakelen][0] -1;
			snakenode[g_snakelen + 1][1] = snakenode[g_snakelen][1];
			snakenode[g_snakelen + 1][2] = snakenode[g_snakelen][2];
		}
		//如果蛇向左运动
		else if (to_west == snakenode[0][2])
		{
			snakenode[g_snakelen + 1][0] = snakenode[g_snakelen][0];
			snakenode[g_snakelen + 1][1] = snakenode[g_snakelen][1]+2;
			snakenode[g_snakelen + 1][2] = snakenode[g_snakelen][2];
		}
		//如果蛇向右运动
		else if (to_east == snakenode[0][2])
		{
			snakenode[g_snakelen + 1][0] =snakenode[g_snakelen][0] ;
			snakenode[g_snakelen + 1][1] = snakenode[g_snakelen][1]-2;
			snakenode[g_snakelen + 1][2] = snakenode[g_snakelen][2];
		}
		//蛇长度递增
		g_snakelen++;
		//分数递增
		g_score++;
	//标记还原
		food = true;
	}
}
//判断蛇死亡
bool snakedie()
{
	if (to_east == snakenode[0][2] || to_west == snakenode[0][2])
	{
		//判断蛇是否撞上边界或自己
		if (0== strncmp(&backgroud[snakenode[0][0] ][ snakenode[0][1]+snakenode[0][2]], "■", 2))
		{
			return false;
		}
			
	}
	else 
	{
		//判断蛇是否撞上边界或自己
		if (0 == strncmp(&backgroud[snakenode[0][0]+snakenode[0][2]][snakenode[0][1]], "■", 2))
		{
			return false;
		}
	}
	//标记还原
		return true;
}
//蛇随方向动
void snakedrimove()
{
	//按键检测
	if (GetAsyncKeyState('W'))
	{
		//防止蛇回头
		if (to_south != snakenode[0][2])
		{
			snakedir = to_north;
		}
	}
	else if (GetAsyncKeyState('A'))
	{
		//防止蛇回头
		if (to_east != snakenode[0][2])
		{
			snakedir = to_west;
		}
	}
	else if (GetAsyncKeyState('S'))
	{
		//防止蛇回头
		if (to_north != snakenode[0][2])
		{
			snakedir = to_south;
		}
	}
	else if (GetAsyncKeyState('D'))
	{
		//防止蛇回头
		if (to_west != snakenode[0][2])
		{
			snakedir = to_east;
		}
	}
	//按F1加速
	else if (GetAsyncKeyState(VK_F1))
	{
		speedup();
	}
	//按F2减速
	else if (GetAsyncKeyState(VK_F2))
	{
		speeddown();
	}
	//按esc键暂停
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		//进入暂停函数
		while (1)
		{
			Sleep(300);
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				break;
			}
		}
	}
}
//画蛇
void drawsnake()
{
	int i;
	//画蛇
	for ( i = 0; snakenode[i][0] != 0; i++)
	{
		strncpy(& backgroud[snakenode[i][0]][snakenode[i][1]], "■", 2);
	}
}
//随机位置产生蛇
void randsnake()
{
	int nX = -1;
	int nY = -1;
	srand((unsigned int)time(NULL));
	//随机产生坐标
	nX = rand() % 19 + 1;
	nY = rand() % 18 + 1;
	//数组初始化
	int sankenode[SNAKELENGH][3] = { 0 };
	//给蛇数组节点赋值
	snakenode[0][0] = nY;
	snakenode[0][1] = nX * 2;
	snakenode[0][2] = to_west;
	snakenode[1][0] = nY;
	snakenode[1][1] = nX * 2+2;
	snakenode[1][2] = to_west;
	snakenode[2][0] = nY;
	snakenode[2][1] = nX * 2+4;
	snakenode[2][2] = to_west;
	//画蛇
	drawsnake();
}
//蛇移动
void snakemove()
{
	int i= SNAKELENGH-1;
	//把后面的蛇删除
	deletesnake();
	for (i; i >= 1; i--)
	{
		//遍历蛇的节点
		if (0 == snakenode[i][1])
		{
			continue;
		}
		//把前一个节点的值赋给当前节点
		snakenode[i][0] = snakenode[i - 1][0];
		snakenode[i][1] = snakenode[i - 1][1];
		snakenode[i][2] = snakenode[i - 1][2];
	}

		//处理蛇头
		snakenode[0][2] = snakedir;
		//如果蛇向左右方向运动
		if (to_east == snakenode[0][2] || to_west == snakenode[0][2])
		{
			snakenode[0][1] += snakenode[0][2];
		}
		else
			//如果蛇向上下方向运动
		{
			snakenode[0][0] += snakenode[0][2];
		}

		//画蛇
	drawsnake();
}//删除节点
void deletesnake();
//画蛇
void drawsnake();
//显示首页
void fristpage();
//播放音乐
void playmusic();
//检测空格
void checkspace();
//停止播放音乐
void stopmusic();
//清空屏幕
void deleteev();
//屏幕背景显示
void showgroud();
//随机位置产生蛇
void randsnake(); 
//蛇移动
void snakemove();
//蛇随方向动
void snakedrimove();
//销毁蛇
void deletesnake();
//判断蛇死亡
bool snakedie();
//随机产生食物
void foodpro();
//蛇长大
void snakegrow();
//显示分数
void scoresnake();
//显示时间
void Gettime1();
void Gettime2();
//减速
void speeddown();
//加速
void speedup();
//文字颜色
void color(int c);
int main()
{
	//显示首页
	fristpage();
	printf("开始游戏");
	//播放音乐
	playmusic();
	//检测空格
	checkspace();
	//停止音乐
	stopmusic();
	//删除屏幕 
	deleteev();
	//随机产生蛇
	randsnake();
	showgroud();
	//游戏界面
	while(1)
	{
		system("cls");
		//产生食物
		foodpro();
		//蛇长大
		snakegrow();
		//蛇随方向动
		snakedrimove();
		//判断蛇是否死亡
		if (false == snakedie())
		{
			printf("snake die");
			break;
		}
		//蛇动
   		snakemove();
		//显示背景
		showgroud();
		//积分
		//显示时间
		scoresnake();
		Sleep(sleeptime);
	}
	system("pause");
	return 0;
}