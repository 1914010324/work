#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<mmsystem.h>
#include<conio.h>
#include<time.h>
#pragma comment (lib,"winmm.lib")
//bool���͵Ķ���
typedef int bool;
#define true 1
#define false 0
int sleeptime=200;
int Time=0;
//��ʼʱ��
int begtime;
//����ʱ��
int entime;
int a[1002];
int g_hang;
int g_lie;
//�ߵĳ�ʼ����
int g_snakelen = 2;
//��Ϸ��ʼ����
int g_score = 0;
//���Ϊ20���ڵ�
#define SNAKELENGH  20
//ö�ٷ���
enum {to_east=2,to_west=-2,to_north=-1,to_south=1};
bool food = true;
//�߽ڵ������
int snakenode[SNAKELENGH][3];
char backgroud[20][48];
//�����ߵĳ�ʼ����
int snakedir=to_west;
//��������
char backgroud[20][48] =
{ "����������������������������������������������\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "��                                          ��\n",
  "����������������������������������������������\n" };
//��ʾ��ҳ
void fristpage()
{
	printf("\n\n\n\n");
	printf("\n\n\n\n");
	printf("\t\t\t����esc��ͣ��Ϸ��\n");
	printf("\t\t\t����F1���٣���F2���١�\n");
	printf("\t\t\t����ӭ����̰���ߵ����硷\n");
	printf("\t\t\t�����ո�ʼ��Ϸ��\n");
	printf("\t\t\t��w  a  s  d���Ʒ���\n");
}
//��������
void playmusic()
{
	//����
	PlaySound("D:\\�ֿ��� - ��ϧû���.wav", NULL, SND_FILENAME | SND_ASYNC);
}
//���ո�
void checkspace()
{
	char chinput;
	while (1)
	{
		chinput = _getch();
		//���ո�
		if (' ' == chinput)
		{
			break;
		}
	}
}
//ֹͣ��������
void stopmusic()
{
	PlaySound(NULL, 0, 0);
}
//�����Ļ
void deleteev()
{
	system("cls");
}
//������
void deletesnake()
{
	int i;
	for (i = 0; snakenode[i][0] != 0; i++)
	{
		//���ߵĽڵ��ÿո����
		strncpy(&backgroud[snakenode[i][0]][snakenode[i][1]], "  ", 2);
	}
}
//������ɫ
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//��Ļ������ʾ
void showgroud()
{
	//����������ʾ��ɫ
	color(2);
		for (int i = 0; i < 20; i++)
		{
			//��ʾ����
			printf(backgroud[i]);
		}
}
//����
void speedup()
{
	if (sleeptime >= 50)
	{
		//����
		sleeptime = sleeptime - 10;
		g_score = g_score + 2;
	}
}
//����
void speeddown()
{
	if (sleeptime < 350)
	{
		//����
		sleeptime = sleeptime + 30;
		g_score = g_score-2;
	}
}
//��ʾʱ��
void Gettime1()
{
	begtime = clock();
}
void Gettime2()
{
	entime = clock();
}
//��ʾ����
void scoresnake()
{
	//��ÿ�ʼʱ��
	Gettime1();
	COORD rd;
	rd.X = 54;
	rd.Y = 7;
	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//��ӡ
	printf("��ӭ����̰������Ϸ");
	rd.X = 57;
	rd.Y = 10;
	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//��ӡ
	printf("w.a.s.d���Ʒ���");
	rd.X = 55;
	rd.Y = 8;
	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//��ӡ
	printf("����");
	rd.X = 56;
	rd.Y = 9;
	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//��ӡ
	printf("%d",g_score);
	rd.X = 53;
	rd.Y = 6;
	//���ù��λ��
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), rd);
	//��ӡʱ��
	//��ý���ʱ��
	Gettime2();
	int Time = entime - begtime;
	entime = entime + Time;
	printf("Time :%dms\n", entime - begtime);

}
//�������ʳ��
void foodpro()
{
	srand((unsigned int)time(NULL));
	//�ж��Ƿ����²���ʳ��
	if (false == food)
	{
		return;
	}
	while (1)
	{
		bool Flag = true;
		//�����������
		 g_lie= rand() % 18+ 1;
		g_hang = rand() % 20 + 1;
		for (int i=0; snakenode[i][0] != 0; i++)
		{
			//�����ߵĽڵ�
			if (g_lie == snakenode[i][0] && g_hang == snakenode[i][1])
			{
				//���ñ��
				Flag = false;
				//��ߺ���Ч��
				break;
			}
		}
		if (true == Flag)
		{
			//�ж�ʳ���Ƿ񱻳�
			break;
		}
	}
	//��ʳ��
	strncpy(&backgroud[g_hang][g_lie*2], "��", 2);
	food = false;

}
//�߳���
void snakegrow()
{
	//�����ͷ�����ʳ���������
	if (g_hang==snakenode[0][0]  && 2*g_lie==snakenode[0][1] )
	{
		//�߳���
		if (to_north == snakenode[0][2])
			//����������˶�
		{
			snakenode[g_snakelen+1][0] = snakenode[g_snakelen][0]+1;
			snakenode[g_snakelen + 1][1] = snakenode[g_snakelen][1] ;
			snakenode[g_snakelen + 1][2] = snakenode[g_snakelen][2];
		}
		else if (to_south == snakenode[0][2])
			//����������˶�
		{
			snakenode[g_snakelen + 1][0] = snakenode[g_snakelen][0] -1;
			snakenode[g_snakelen + 1][1] = snakenode[g_snakelen][1];
			snakenode[g_snakelen + 1][2] = snakenode[g_snakelen][2];
		}
		//����������˶�
		else if (to_west == snakenode[0][2])
		{
			snakenode[g_snakelen + 1][0] = snakenode[g_snakelen][0];
			snakenode[g_snakelen + 1][1] = snakenode[g_snakelen][1]+2;
			snakenode[g_snakelen + 1][2] = snakenode[g_snakelen][2];
		}
		//����������˶�
		else if (to_east == snakenode[0][2])
		{
			snakenode[g_snakelen + 1][0] =snakenode[g_snakelen][0] ;
			snakenode[g_snakelen + 1][1] = snakenode[g_snakelen][1]-2;
			snakenode[g_snakelen + 1][2] = snakenode[g_snakelen][2];
		}
		//�߳��ȵ���
		g_snakelen++;
		//��������
		g_score++;
	//��ǻ�ԭ
		food = true;
	}
}
//�ж�������
bool snakedie()
{
	if (to_east == snakenode[0][2] || to_west == snakenode[0][2])
	{
		//�ж����Ƿ�ײ�ϱ߽���Լ�
		if (0== strncmp(&backgroud[snakenode[0][0] ][ snakenode[0][1]+snakenode[0][2]], "��", 2))
		{
			return false;
		}
			
	}
	else 
	{
		//�ж����Ƿ�ײ�ϱ߽���Լ�
		if (0 == strncmp(&backgroud[snakenode[0][0]+snakenode[0][2]][snakenode[0][1]], "��", 2))
		{
			return false;
		}
	}
	//��ǻ�ԭ
		return true;
}
//���淽��
void snakedrimove()
{
	//�������
	if (GetAsyncKeyState('W'))
	{
		//��ֹ�߻�ͷ
		if (to_south != snakenode[0][2])
		{
			snakedir = to_north;
		}
	}
	else if (GetAsyncKeyState('A'))
	{
		//��ֹ�߻�ͷ
		if (to_east != snakenode[0][2])
		{
			snakedir = to_west;
		}
	}
	else if (GetAsyncKeyState('S'))
	{
		//��ֹ�߻�ͷ
		if (to_north != snakenode[0][2])
		{
			snakedir = to_south;
		}
	}
	else if (GetAsyncKeyState('D'))
	{
		//��ֹ�߻�ͷ
		if (to_west != snakenode[0][2])
		{
			snakedir = to_east;
		}
	}
	//��F1����
	else if (GetAsyncKeyState(VK_F1))
	{
		speedup();
	}
	//��F2����
	else if (GetAsyncKeyState(VK_F2))
	{
		speeddown();
	}
	//��esc����ͣ
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		//������ͣ����
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
//����
void drawsnake()
{
	int i;
	//����
	for ( i = 0; snakenode[i][0] != 0; i++)
	{
		strncpy(& backgroud[snakenode[i][0]][snakenode[i][1]], "��", 2);
	}
}
//���λ�ò�����
void randsnake()
{
	int nX = -1;
	int nY = -1;
	srand((unsigned int)time(NULL));
	//�����������
	nX = rand() % 19 + 1;
	nY = rand() % 18 + 1;
	//�����ʼ��
	int sankenode[SNAKELENGH][3] = { 0 };
	//��������ڵ㸳ֵ
	snakenode[0][0] = nY;
	snakenode[0][1] = nX * 2;
	snakenode[0][2] = to_west;
	snakenode[1][0] = nY;
	snakenode[1][1] = nX * 2+2;
	snakenode[1][2] = to_west;
	snakenode[2][0] = nY;
	snakenode[2][1] = nX * 2+4;
	snakenode[2][2] = to_west;
	//����
	drawsnake();
}
//���ƶ�
void snakemove()
{
	int i= SNAKELENGH-1;
	//�Ѻ������ɾ��
	deletesnake();
	for (i; i >= 1; i--)
	{
		//�����ߵĽڵ�
		if (0 == snakenode[i][1])
		{
			continue;
		}
		//��ǰһ���ڵ��ֵ������ǰ�ڵ�
		snakenode[i][0] = snakenode[i - 1][0];
		snakenode[i][1] = snakenode[i - 1][1];
		snakenode[i][2] = snakenode[i - 1][2];
	}

		//������ͷ
		snakenode[0][2] = snakedir;
		//����������ҷ����˶�
		if (to_east == snakenode[0][2] || to_west == snakenode[0][2])
		{
			snakenode[0][1] += snakenode[0][2];
		}
		else
			//����������·����˶�
		{
			snakenode[0][0] += snakenode[0][2];
		}

		//����
	drawsnake();
}//ɾ���ڵ�
void deletesnake();
//����
void drawsnake();
//��ʾ��ҳ
void fristpage();
//��������
void playmusic();
//���ո�
void checkspace();
//ֹͣ��������
void stopmusic();
//�����Ļ
void deleteev();
//��Ļ������ʾ
void showgroud();
//���λ�ò�����
void randsnake(); 
//���ƶ�
void snakemove();
//���淽��
void snakedrimove();
//������
void deletesnake();
//�ж�������
bool snakedie();
//�������ʳ��
void foodpro();
//�߳���
void snakegrow();
//��ʾ����
void scoresnake();
//��ʾʱ��
void Gettime1();
void Gettime2();
//����
void speeddown();
//����
void speedup();
//������ɫ
void color(int c);
int main()
{
	//��ʾ��ҳ
	fristpage();
	printf("��ʼ��Ϸ");
	//��������
	playmusic();
	//���ո�
	checkspace();
	//ֹͣ����
	stopmusic();
	//ɾ����Ļ 
	deleteev();
	//���������
	randsnake();
	showgroud();
	//��Ϸ����
	while(1)
	{
		system("cls");
		//����ʳ��
		foodpro();
		//�߳���
		snakegrow();
		//���淽��
		snakedrimove();
		//�ж����Ƿ�����
		if (false == snakedie())
		{
			printf("snake die");
			break;
		}
		//�߶�
   		snakemove();
		//��ʾ����
		showgroud();
		//����
		//��ʾʱ��
		scoresnake();
		Sleep(sleeptime);
	}
	system("pause");
	return 0;
}